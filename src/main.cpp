#include <Arduino.h>
#include <WiFiMulti.h>
#include <InfluxDbClient.h>

#include "config.h"

WiFiMulti wifiMulti;

InfluxDBClient client(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);

// Data point
Point sensor("inverter_data");  

const byte numChars = 32;
byte rxData[numChars];   // an array to store the received data
boolean newData = false;
int lastTx;
int lastRx;

void data_grab() {
  byte message[] = {0x43, 0xC0, BOX_ID, 0x00, 0x00, INVERTER_ID, 0x00, 0x00, 0x00, 0x00};
  int length = sizeof(message);

  byte sum[] = { 0x00 };
  for (byte i = 0; i < length; i++) {
    sum[0] += message[i];
  }
  byte final[length + 1];
  memcpy(final, message, length);
  memcpy(&final[length], sum, sizeof(sum));

  for (byte i = 0; i <= length + 1; i++) {
    Serial2.write(final[i]);
    delayMicroseconds(2639); // 2639
  }
}

void setup() {

  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2, false);

  Serial.println("Starting...");

  pinMode(SET_PIN, OUTPUT);
  digitalWrite(SET_PIN, HIGH);

  // Connect WiFi
  Serial.println("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  wifiMulti.addAP(WIFI_SSID, WIFI_PASSWORD);
  while (wifiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();

  // Check server connection
  if (client.validateConnection()) {
    Serial.print("Connected to InfluxDB: ");
    Serial.println(client.getServerUrl());
  } else {
    Serial.print("InfluxDB connection failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  delay(1000);

  lastTx = millis();
  lastRx = millis();
}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    int startMarker = 0x43;
    int endMarker = 0x9F; // 0x2f
    int rc;
 
    while (Serial2.available() > 0 && !newData) {
      rc = Serial2.read();

      if (rc == startMarker)
        recvInProgress = true;
      if (recvInProgress == true) {
        rxData[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
            ndx = numChars - 1;
        }
        if (rc == endMarker) {
          recvInProgress = false;
          ndx = 0;
          newData = true;
        }
      }
  }
}

float getValue(int index) {
  return int((rxData[index] << 8) | rxData[index + 1]) / 100.0;
}

void showNewData() {
  if (!newData) return;
  
  Serial.print("Got response: ");
  for (int i = 0; i < sizeof(rxData); i++)
  {
    Serial.print(rxData[i], HEX);
    Serial.print(" ");
  }

  String box_id = String(int((rxData[I_BOX_ID] << 8) | rxData[I_BOX_ID + 1]), HEX);
  String inverter_id = String(int((rxData[I_INVERTER_ID] << 24) | (rxData[I_INVERTER_ID + 1] << 16) | (rxData[I_INVERTER_ID + 2] << 8) | rxData[I_INVERTER_ID + 3]), HEX);
  float vdc = getValue(I_VDC);
  float idc = getValue(I_DC);
  float vac = getValue(I_VAC);
  float iac = getValue(I_AC);
  
  Serial.println();
  Serial.print("Box ID: ");
  Serial.print(box_id);
  Serial.print(" Inverter ID: ");
  Serial.print(inverter_id);
  Serial.print(" Voltage DC: ");
  Serial.print(vdc);
  Serial.print(" Current DC: ");
  Serial.print(idc);
  Serial.print(" Voltage AC: ");
  Serial.print(vac);
  Serial.print(" Current AC: ");
  Serial.print(iac);
  Serial.println();
  lastRx = millis();

  // Store measured value into point
  sensor.clearFields();
  
  // Add constant tags - only once
  sensor.addTag("BOX_ID", box_id);
  sensor.addTag("INVERTER_ID", inverter_id);

  sensor.addField("VDC", vdc);
  sensor.addField("IDC", idc);
  sensor.addField("VAC", vac);
  sensor.addField("IAC", iac);
  // Print what are we exactly writing
  Serial.print("Writing: ");
  Serial.println(client.pointToLineProtocol(sensor));
  // If no Wifi signal, try to reconnect it
  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("Wifi connection lost");
  }
  // Write point
  if (!client.writePoint(sensor)) {
    Serial.print("InfluxDB write failed: ");
    Serial.println(client.getLastErrorMessage());
  }

  newData = false;
}

void loop() {
  if (lastTx + 5000 < millis() && lastRx + 60000 < millis()) { //60000
    data_grab();
    lastTx = millis();
  }
  recvWithStartEndMarkers();
  showNewData();
}