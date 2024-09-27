#include <Arduino.h>
#include <WiFiMulti.h>
#include <InfluxDbClient.h>
#include <FastLED.h>
#include <NETSGPClient.h>

#include "config.h"

#define debugSerial Serial
#define clientSerial Serial1

NETSGPClient inverter(clientSerial, PROG_PIN); /// NETSGPClient instance

WiFiMulti wifiMulti;

CRGB leds[NUM_LEDS];

InfluxDBClient influx(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);

// Data point
Point sensor("inverter_data");

boolean newData = false;
int lastTx;
int lastRx;
int attemps = 0;

void setup() {

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.setBrightness(5);
  leds[0] = CRGB::Red;
  FastLED.show();

  debugSerial.begin(115200);
  clientSerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  delay(500);

  Serial.println("Starting...");

  // Connect WiFi
  Serial.println("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  leds[0] = CRGB::Yellow;
  FastLED.show();

  delay(1000);

  // Make sure the RF module is set to the correct settings
  if (!inverter.setDefaultRFSettings())
  {
      debugSerial.println("Could not set RF module to default settings");
      leds[0] = CRGB::Yellow;
      FastLED.show();
  }

  // Check server connection
  if (influx.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(influx.getServerUrl());
    leds[0] = CRGB::Blue;
    FastLED.show();
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(influx.getLastErrorMessage());
    leds[0] = CRGB::Red;
    FastLED.show();
  }

  delay(1000);

  lastTx = millis();
  lastRx = millis();

  sensor.clearTags();
  sensor.addTag("INVERTER_ID", String(inverterID));
  sensor.addTag("source", "solar-logger");
}

void writeToDB() {
    // Print what are we exactly writing
  Serial.print("Writing: ");
  Serial.println(influx.pointToLineProtocol(sensor));
  // If no Wifi signal, try to reconnect it
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("Wifi connection lost");
  }
  // Write point
  if (!influx.writePoint(sensor)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(influx.getLastErrorMessage());
  }
}

uint32_t lastSendMillis = 0;
void loop() {
  const uint32_t currentMillis = millis();
  if (currentMillis - lastSendMillis > 60000) {
    lastSendMillis = currentMillis;
    attemps++;
    debugSerial.println("");
    debugSerial.println("Sending request now");

    const NETSGPClient::InverterStatus status = inverter.getStatus(inverterID);
    if (status.valid) {
      leds[0] = CRGB::Green;
      FastLED.show();
      debugSerial.println("*********************************************");
      debugSerial.println("Received Inverter Status");
      debugSerial.print("Device: ");
      debugSerial.println(status.deviceID, HEX);
      debugSerial.println("Status: " + String(status.state));
      debugSerial.println("DC_Voltage: " + String(status.dcVoltage) + "V");
      debugSerial.println("DC_Current: " + String(status.dcCurrent) + "A");
      debugSerial.println("DC_Power: " + String(status.dcPower) + "W");
      debugSerial.println("AC_Voltage: " + String(status.acVoltage) + "V");
      debugSerial.println("AC_Current: " + String(status.acCurrent) + "A");
      debugSerial.println("AC_Power: " + String(status.acPower) + "W");
      debugSerial.println("Power gen total: " + String(status.totalGeneratedPower));
      debugSerial.println("Temperature: " + String(status.temperature));
      
      // Store measured value into point
      sensor.clearFields();
      sensor.addField("STATUS", status.state);
      sensor.addField("VDC", status.dcVoltage);
      sensor.addField("IDC", status.dcCurrent);
      sensor.addField("PDC", status.dcPower);
      sensor.addField("VAC", status.acVoltage);
      sensor.addField("IAC", status.acCurrent);
      sensor.addField("PAC", status.acPower);
      sensor.addField("TOTAL_GEN", status.totalGeneratedPower);
      sensor.addField("TEMP", status.temperature);

      // Write point to InfluxDB
      writeToDB();
      attemps = 0;

    } else if (attemps > 3) {
      Serial.println("No response from inverter");
      leds[0] = CRGB::Yellow;
      FastLED.show();

      // Store measured value into point
      sensor.clearFields();
      sensor.addField("STATUS", 0);
      sensor.addField("VDC", 0.0);
      sensor.addField("IDC", 0.0);
      sensor.addField("PDC", 0.0);
      sensor.addField("VAC", 0.0);
      sensor.addField("IAC", 0.0);
      sensor.addField("PAC", 0.0);
      sensor.addField("TOTAL_GEN", 0.0);
      sensor.addField("TEMP", 0);

      // Write point to InfluxDB
      writeToDB();
      attemps = 0;
    }
  }
}