// WiFi AP SSID
#define WIFI_SSID "Am Wlangert"
// WiFi password
#define WIFI_PASSWORD "21926240994776465803"
// InfluxDB  server url. Don't use localhost, always server name or ip address.
// E.g. http://192.168.1.48:8086 (In InfluxDB 2 UI -> Load Data -> Client Libraries), 
#define INFLUXDB_URL "http://homeassistant:8086"
// InfluxDB 2 server or cloud API authentication token (Use: InfluxDB UI -> Load Data -> Tokens -> <select token>)
#define INFLUXDB_TOKEN "2Ubk-pA5PKrktBVWMbM7k_4AB4yOMGu7C7fIyyeO2YYYVCUgwp49-wKKRRaoYDBYcTySv19iGvryOO2qCfvcxA=="
// InfluxDB 2 organization id (Use: InfluxDB UI -> Settings -> Profile -> <name under tile> )
#define INFLUXDB_ORG "petti"
// InfluxDB 2 bucket name (Use: InfluxDB UI -> Load Data -> Buckets)
#define INFLUXDB_BUCKET "solar"

//LC21S
//---------------------------------------------------------
#define SET_PIN 1

#define RXD2 44
#define TXD2 43

// Parameters
#define BAUD 0x04
#define MODULE_ID 0x2233
#define NETWORK_ID 0x1122
#define RF_TRANSMIT_POWER 0x00
#define RF_CHANNEL 0x64

//Inverter Parameters
#define BOX_ID 0x54, 0x89 //Box ID
#define INVERTER_ID 0x38, 0x00, 0x41, 0x46

#define INVERTER_ID_S "38004146"
#define BOX_ID_S "5489"

// indices for the return data
#define I_BOX_ID 2
#define I_INVERTER_ID 6
#define I_VDC 15
#define I_DC 17
#define I_VAC 19
#define I_AC 21

// LED
#define NUM_LEDS 1
#define DATA_PIN 2