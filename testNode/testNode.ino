#include <ESP8266WiFi.h>


//////////////////// config ////////////////////////

const char ssid[]     = "Farm00";
const char password[] = "AdminFarm00";

char server_ip[]      = "192.168.4.1";
const uint16_t port   = 8888;

const uint16_t nodeId = 1;

///////////////////////////////////////////////////

#define MAXRAND 5

WiFiClient client;

void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println();
//  WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED) {        // wait for connect to AP
//    delay(200);
//    Serial.print(".");
//  }
//  Serial.println();
//  Serial.println("ready for fun");
  // wait for connect to GateWay
}
void loop() {
start :
  long tempRand = random(1,MAXRAND);
  Serial.print("RAND : ");
  Serial.println(tempRand);
  delay(1000 * tempRand);

  WiFi.begin(ssid, password);
  for (int i = 0 ; i <= 80 ; i++) {
    if (i == 80)
      goto start;
    if (WiFi.status() == WL_CONNECTED)
      break;
    Serial.print(".");
    delay(200);
  }
  Serial.println();

  while (!client.connect(server_ip, port));
  //Serial.print(".");

  while (client.available()) {
    String data = client.readStringUntil('\n');
    Serial.println(data);
  }
  String temp = "Hello from node : ";
  temp += nodeId;
  temp += "\n";
  client.print(temp);
  Serial.println("Sended");
  while (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    Serial.println(data);
    client.println(data);
  }
  client.stop();
  WiFi.disconnect();
  delay(5000);

}
