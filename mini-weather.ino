#include <WEMOS_DHT12.h>

#include "config.h"
#include "wifi.h"
#include "io.h"

DHT12 dht12;

void setup() {
  Serial.begin(115200);
  server.begin();

  loadConfig();
  
  if (!client_mode()){
    ap_mode();
  }else{
    io_connect();
  }
}

void loop() {
  int humidity_data;
  int temperature_data;
  
  if(!mqtt.ping(3)) {
    if(!mqtt.connected())
      io_connect();
  }

  if(dht12.get()==0){
    humidity_data = (int)dht12.humidity;
    temperature_data = (int)dht12.cTemp;
    Serial.println(humidity_data);
    Serial.println(temperature_data);
  }

  if (! indoor_temp.publish(temperature_data))
    Serial.println("Failed to publish temperature");
  else
    Serial.println("Temperature published!");

  if (! indoor_humi.publish(humidity_data))
    Serial.println("Failed to publish humidity");
  else
    Serial.println("Humidity published!");
  
  delay(60000);
}
