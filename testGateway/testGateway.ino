#include <ESP8266WiFi.h>

////////////////////// CONFIG ///////////////////////

const char* APNAME                = "Farm00";
const char* APPASS                = "AdminFarm00";

const char* ssid                  = "OHMAMP";
const char* password              = "a029453745";

const int farmId                  = 1;
const int zoneId                  = 1;

IPAddress ip_addr                 = {192, 168, 1, 200};
IPAddress gateway                 = {192, 168, 1, 1};
IPAddress subnet                  = {255, 255, 255, 0};

////////////////////////////////////////////////////

WiFiServer server(8888);
WiFiClient client;

void setup() {

  Serial.begin(115200);
  //Serial.println();
  //Serial.print("Connecting to :");
  //Serial.println(ssid);

  //  WiFi.begin(ssid, password);
  //  while (WiFi.status() != WL_CONNECTED) {
  //    delay(200);
  //    Serial.print(".");
  //  }
  //  WiFi.config(ip_addr, gateway, subnet);
  //
  //  Serial.println("WiFi connected");
  //  Serial.print("IP address: ");
  //  Serial.println(WiFi.localIP());

  WiFi.softAP(APNAME, APPASS);
  server.begin();

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //////////////////////////////////

  WiFiClient client;

}

void loop() {

  client = server.available();
  if (client) {
    while (client.connected()) {
      while (Serial.available()) {
        String data = Serial.readStringUntil('\n');
        client.println(data);
        Serial.println(data);
      }
      while (client.available()) {
        String data = client.readStringUntil('\n');
        Serial.println(data);
      }
//      if(server.hasClient()){
//        Serial.println("client disconnect");
//        return;
//      }
    }
      client.stop();
      Serial.println("client disconnect");
  }

}
