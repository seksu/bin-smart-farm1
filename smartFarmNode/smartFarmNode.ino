#include <ESP8266WiFi.h>


//////////////////// config ////////////////////////

const char ssid[]     = "Farm00";
const char password[] = "AdminFarm00";

char server_ip[]      = "192.168.1.200";
const uint16_t port   = 8888;  

const uint16_t nodeId = 1;

///////////////////////////////////////////////////

byte mac[]            = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
WiFiClient client;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected with Router");
  /*
  if (client.connect(server_ip, port))
  {
    Serial.println("client connected server");
    client.print("Hello I'm Client from ");
    client.println(WiFi.localIP());
    client.println();
  }
  */
  Serial.print("Local ip is : ");
  Serial.println(WiFi.localIP());
  Serial.print("Port is:"); Serial.println(port);
  Serial.print("MAC Address is :"); WiFi.macAddress(mac);
  Serial.print("MAC: "); Serial.print(mac[5], HEX);
  Serial.print(":"); Serial.print(mac[4], HEX);
  Serial.print(":"); Serial.print(mac[3], HEX);
  Serial.print(":"); Serial.print(mac[2], HEX);
  Serial.print(":"); Serial.print(mac[1], HEX);
  Serial.print(":"); Serial.println(mac[0], HEX);

  Serial.print("gatewayIP is : ");
  Serial.println(WiFi.gatewayIP());
}

void loop()
{
  if(client.connect(server_ip, port)){
    client.println("You are cute."); 
    Serial.println("Send");
    // Client.stop();
    delay(1000);
  }
}
