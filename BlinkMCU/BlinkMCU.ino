#include <ESP8266WiFi.h>
#define LED_BUILTIN D0
#define LED2        D4
//////////////////// config ////////////////////////

const char ssid[]           = "OHMAMP";
const char password[]       = "a029453745";

///////////////////////////////////////////////////

WiFiClient client;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED2,HIGH);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  Serial.println();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
  Serial.println();
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
}
void loop() {
    digitalWrite(LED2,HIGH);
    delay(100);
    digitalWrite(LED2,LOW);
    delay(100);
}
