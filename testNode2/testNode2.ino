#include <ESP8266WiFi.h>


//////////////////// config ////////////////////////

const char ssid[]           = "SmartFarmRouter";
const char password[]       = "SmartFarm00";

const char server_ip[]      = "192.168.1.2";
const uint16_t port         = 8000;

const int nodeId            = 3;

///////////////////////////////////////////////////

String strInput = "";
#define MAXRAND 5

WiFiClient client;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {        // wait for connect to AP
    delay(200);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  digitalWrite(LED_BUILTIN,HIGH);
}
void loop() {
  long tempRand = random(1,MAXRAND);
  Serial.print("RAND : ");
  Serial.println(tempRand);
  delay(1000 * tempRand);

  while (!client.connect(server_ip, port))
  Serial.print(".");

  String temp = "&nodeId=";
  temp += nodeId;
  temp += "&data1=";
  temp += 1;
  temp += "&data2=";
  temp += 2;
  temp += "&data3=";
  temp += 3;  
  client.println(temp);
  Serial.println("Sended");

  for(int i=0,max=15 ; i<=max ; i++){
    if(client.available()){
      strInput = client.readStringUntil('\n');
      Serial.println(strInput.charAt(8)-48);
      if(strInput.charAt(8)-48 == nodeId){
        Serial.println("NodeId is right");
        break;
      }
      else
        return;
    }
    if(i == max)
      return;
    delay(200);
  }
  client.stop();
  digitalWrite(LED_BUILTIN,LOW);
  delay(500);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(20000);

}
