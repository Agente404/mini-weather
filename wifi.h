#include <ESP8266WiFi.h>

#define SSID "NEWTONFORMACION" //(const char*)ssid
#define PWD "NEWTONFORMACI" //(const char*)wpwd

WiFiServer server(80);
WiFiClient client;

bool ap_mode(){
  WiFi.mode(WIFI_AP);
  WiFi.disconnect();
  WiFi.softAP("MiniW", "miniweatherstation");

  Serial.print("Access Point, IP address: ");
  Serial.println(WiFi.softAPIP()); 

  return true;
}

bool client_mode(){
  int timeout = 10;

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(SSID, PWD);
  
  while (WiFi.status() != WL_CONNECTED && timeout >= 0)
  {
    timeout = timeout - 1;
    delay(1000);    
    Serial.print(".");   
  }
  
  Serial.println();
  
  if (WiFi.status() != WL_CONNECTED){
    Serial.print("Unable to connect");
    return false;
  }
    
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());  
  return true;
}

