// WiFi AP SSID
#define WIFI_SSID "ssid"
// WiFi password
#define WIFI_PASSWORD "password"
// InfluxDB  server url. Don't use localhost, always server name or ip address.
// E.g. http://192.168.1.48:8086 (In InfluxDB 2 UI -> Load Data -> Client Libraries), 
#define INFLUXDB_URL "influxdb-url"
// InfluxDB 2 server or cloud API authentication token (Use: InfluxDB UI -> Load Data -> Tokens -> <select token>)
#define INFLUXDB_TOKEN "toked-id"
// InfluxDB 2 organization id (Use: InfluxDB UI -> Settings -> Profile -> <name under tile> )
#define INFLUXDB_ORG "org"
// InfluxDB 2 bucket name (Use: InfluxDB UI -> Load Data -> Buckets)
#define INFLUXDB_BUCKET "bucket"
// InfluxDB v1 database name 
//#define INFLUXDB_DB_NAME "database"

#define DEVICE "ESP32"

#define SET_PIN 5

#define RXD2 16
#define TXD2 17

//LC12S Parameters
#define BAUD 0x04
#define MODULE_ID 0x2233
#define NETWORK_ID 0x1122
#define RF_TRANSMIT_POWER 0x00
#define RF_CHANNEL 0x64

//Inverter Parameters
#define BOX_ID 0x13, 0x84
#define INVERTER_ID 0x38, 0x00, 0x41, 0x46

#define I_BOX_ID 2
#define I_INVERTER_ID 6
#define I_VDC 15
#define I_DC 17
#define I_VAC 19
#define I_AC 21