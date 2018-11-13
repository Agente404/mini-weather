#include <ArduinoJson.h>
#include "FS.h"

#define ioserver "io.adafruit.com";
#define ioport 1883;

char ssid;     
char wpwd;

char iouser;
char iokey;

bool loadConfig() {
  File configFile = SPIFFS.open("/config.json", "r");  
  if (!configFile) {
    Serial.println("Failed to open config file");
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return false;
  }

  std::unique_ptr<char[]> buf(new char[size]);

  configFile.readBytes(buf.get(), size);

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());

  if (!json.success()) {
    Serial.println("Failed to parse config file");
    return false;
  }

  ssid = json["ssid"];
  wpwd = json["password"];

  iouser = json["iouser"];
  iokey = json["iokey"];

  return true;
}

bool saveConfig() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  ssid = json["ssid"];
  wpwd = json["password"];

  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return false;
  }

  json.printTo(configFile);
  return true;
}
