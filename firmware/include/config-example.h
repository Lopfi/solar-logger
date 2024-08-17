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

// Inverter
//---------------------------------------------------------
// Programming enable pin of RF module
constexpr const uint8_t PROG_PIN = 1;
// RX pin of ESP32 connect to TX of RF module
constexpr const uint8_t RX_PIN = 44;
// TX pin of ESP32 connect to RX of RF module
constexpr const uint8_t TX_PIN = 43;
// Identifier of your inverter (see label on inverter)
constexpr const uint32_t inverterID = 0x38004146;

// LED
//---------------------------------------------------------
// Number of leds in the strip
#define NUM_LEDS 1
// Data pin where the LED strip is connected to
#define DATA_PIN 2

