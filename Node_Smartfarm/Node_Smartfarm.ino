#include <ESP8266WiFi.h>

// ssid : SmartFarmRouter
// pass : SmartFarm00

//////////////////// config ////////////////////////

const char ssid[]             = "OHMAMP";
const char password[]         = "a029453745";

//const char server_ip[]      = "192.168.1.2";
//const uint16_t port         = 8000;

const int nodeId              = 1;

///////////////////////////////////////////////////

IPAddress ipaddr              = {192, 168,   1,  4};
IPAddress gateway             = {192, 168,   1,  1};
IPAddress subnet              = {255, 255, 255,  0};

String strInput               = "";
#define MAXRAND 5
#define LED_BUILTIN D0
WiFiServer server(8000);
WiFiClient client;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println();
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {        // wait for connect to AP
    delay(200);
    Serial.print(".");
  }
  //WiFi.config(ipaddr, gateway, subnet);
  
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  digitalWrite(LED_BUILTIN,HIGH);
}
void loop() {
  client = server.available();
  if (client) {
    Serial.println("Have client");
    for(int i=0 ; i<100 ; i++){
      if(client.available()) {
        strInput = client.readStringUntil('\n');
        Serial.println(strInput);
        if(strInput == "require"){
          client.println(sensorRead());
          return;
        }
      }
      delay(50);
    }
    client.stop();
    digitalWrite(LED_BUILTIN,LOW);
    delay(100);
    digitalWrite(LED_BUILTIN,HIGH); 
  }
}

String sensorRead(){
  String temp = "19 Oct 2016 22:35:50,18,5,62,31.00,47.00,30.00";  
  return temp;
}
