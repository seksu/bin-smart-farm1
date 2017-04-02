// created by sek su
// email : smartfarm.mail@gmail.com
// pass  : Smartpass

#include <ESP8266WiFi.h>
#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>

////////////////////// CONFIG ///////////////////////
                                                   
const char* APNAME                = "Farm00";       
const char* APPASS                = "AdminFarm00";

const char* ssid                  = "OHMAMP";
const char* password              = "a029453745";

IPAddress ip_addr                 = {192,168,1,200};
IPAddress gateway                 = {192,168,1,1};
IPAddress subnet                  = {255,255,255,0};
                                                  
////////////////////////////////////////////////////


const char* SMTP_SERVER           = "smtp.gmail.com";
const int   SMTP_PORT             = 465;
const char* user_base64           = "c21hcnRmYXJtLm1haWxAZ21haWwuY29t";
const char* user_password_base64  = "U21hcnRwYXNz";
const char* from_email            = "MAIL FROM:<smartfarm.mail@gmail.com>";
const char* to_email              = "RCPT TO:<jarukit.suchat@gmail.com>";

WiFiServer server(8888);
WiFiClient client;

void setup()
{
  Serial.begin(115200);

  ///////////////////////////////// OLED

  Wire.begin();
  oled.init();                      // Initialze SSD1306 OLED display
  oled.clearDisplay();
  oled.setTextXY(0, 0);             // Set cursor position, start of line 0
  oled.putString("Connecting to ");
  oled.setTextXY(1, 0);
  oled.putString(ssid);
  oled.setTextXY(2, 0);
  Serial.println();
  Serial.print("Connecting to :");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
    oled.putString(".");
  }
  
  WiFi.config(ip_addr,gateway,subnet);
  
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  WiFi.softAP(APNAME, APPASS);
  server.begin();

  oled.clearDisplay();
  oled.setTextXY(0, 0);             // Set cursor position, start of line 0
  oled.putString("IP Address is :");
  oled.setTextXY(1, 0);             // Set cursor position, start of line 1
  String tmp = (String)WiFi.localIP();
  oled.putString(tmp);
  oled.setTextXY(2, 0);             // Set cursor position, start of line 2
  oled.putString("RSSI is :");
  oled.setFont(font8x8); 
  //////////////////////////////////


}
/*
void loop()
{
  checkRSSI();
  client = server.available();
  if(client){
    Serial.println("client connect");
    while(client.connected()){
      if(client.available()){
        Serial.println(client.readStringUntil('\n'));
      }
    }
  client.stop();
  Serial.println("client disconnect");    
  }

  /*
 if (sendEmail()) {
 Serial.println("Email sent");
 }
 else {
 Serial.println("Email failed");
 }
  delay(50*1000);
  */
//}

void loop() {
 WiFiClient client = server.available();
 if (!client) 
 return;
 Serial.println("New client");
 if(client.connected()){
 if(client.available())
 Serial.println(client.readStringUntil('\n'));
}
 client.stop();
 Serial.println("Client disconnect"); 
}

void checkRSSI() {
  oled.setTextXY(3, 0);
  String tmp = (String)WiFi.RSSI();
  //Serial.println(tmp);
  oled.putString(tmp);
  //delay(500);
}

byte sendEmail() {
  WiFiClientSecure client;
  if (client.connect(SMTP_SERVER, SMTP_PORT) == true) {
    Serial.println("connected");
  }
  else {
    Serial.println("connection failed");
    return 0;
  }
  if (!eRcv(client)) return 0;
  Serial.println("--- Sending EHLO"); client.println("EHLO 1.2.3.4"); 
  if (!eRcv(client)) return 0;
  Serial.println("--- Sending login"); client.println("AUTH LOGIN"); 
  if (!eRcv(client)) return 0;
  Serial.println("--- Sending User base64"); client.println(user_base64); 
  if (!eRcv(client)) return 0;
  Serial.println("--- Sending Password base64"); client.println(user_password_base64); 
  if (!eRcv(client)) return 0;
  Serial.println("--- Sending From"); client.println(from_email); 
  if (!eRcv(client)) return 0;
  Serial.println("--- Sending To"); client.println(to_email); 
  if (!eRcv(client)) return 0;
  Serial.println("--- Sending DATA"); client.println(F("DATA")); 
  if (!eRcv(client)) return 0;
  Serial.println("--- Sending QUIT");
  client.println("FROM: SmartFarm<seksit39@outlook.com>"); client.println("TO: Owner");
  client.println("SUBJECT: SmartFarm is Good");
  client.println("Your SmartFarm GateWay is still alive\n");
  client.println("Confirm by Sek Su \n"); client.println("."); if (!eRcv(client)) return 0;
  client.println("QUIT"); if (!eRcv(client)) return 0;
  client.stop(); Serial.println(F("disconnected")); return 1;
}

bool eRcv(WiFiClientSecure client) {
  byte respCode;
  byte thisByte;
  int loopCount = 0;
  while (!client.available()) {
    delay(1);
    loopCount++;
    // if nothing received for10 seconds, timeout
    if (loopCount > 10000) {
      client.stop();
      Serial.println("\r\nTimeout");
      return 0;
    }
  }
  respCode = client.peek();
  while (client.available()) {

    thisByte = client.read();
    Serial.write(thisByte);

  }
  if (respCode >= '4') {
    return 0;

  }
  return 1;
}
