//WiFi
//---------------------------------------------------------
// WiFi AP SSID
#define WIFI_SSID "ssid"
// WiFi password
#define WIFI_PASSWORD "password" 

// InfluxDB
//---------------------------------------------------------
// InfluxDB  server url.
// E.g. http://192.168.1.48:8086, 
#define INFLUXDB_URL "influxdb-url"
// InfluxDB 2 server or cloud API authentication token
#define INFLUXDB_TOKEN "toked-id"
// InfluxDB 2 organization id
#define INFLUXDB_ORG "org"
// InfluxDB 2 bucket name
#define INFLUXDB_BUCKET "bucket"

//LC21S
//---------------------------------------------------------
// Enable pin
#define SET_PIN 1
// Pins for UART communication with LC21S
#define RXD2 44
#define TXD2 43

//LC12S Parameters
#define BAUD 0x04
#define MODULE_ID 0x2233
#define NETWORK_ID 0x1122
#define RF_TRANSMIT_POWER 0x00
#define RF_CHANNEL 0x64

//Inverter Parameters
#define BOX_ID 0x00, 0x00 //Box ID
#define INVERTER_ID 0x00, 0x00, 0x00, 0x00

#define INVERTER_ID "00000000";
#define BOX_ID_S "0000";

#define I_BOX_ID 2
#define I_INVERTER_ID 6
#define I_VDC 15
#define I_DC 17
#define I_VAC 19
#define I_AC 21

// LED
//---------------------------------------------------------
// Number of leds in the strip
#define NUM_LEDS 1
// Data pin where the LED strip is connected to
#define DATA_PIN 2