#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define IO_SERVER "io.adafruit.com"
#define IO_PORT 1883
#define IO_USER "oskrpnk" //(const char*)iouser
#define IO_KEY "7e8f475838e24dce8e82008523b642b0" //(const char*)iokey

Adafruit_MQTT_Client mqtt(&client, IO_SERVER, IO_PORT, IO_USER, IO_KEY);

Adafruit_MQTT_Publish indoor_temp = Adafruit_MQTT_Publish(&mqtt, iouser + "oskrpnk/feeds/indoor-temp");
Adafruit_MQTT_Publish indoor_humi = Adafruit_MQTT_Publish(&mqtt, iouser + "oskrpnk/feeds/indoor-humi");

bool io_connect() {

  Serial.println("\nConnecting to Adafruit IO ");

  int8_t ret;
  int timeout = 10;

  while ((ret = mqtt.connect()) != 0 && timeout >= 0) {
    
    timeout = timeout - 1;
    delay(1000);    
    Serial.print("."); 
    
    switch (ret) {
      case 1: Serial.println("Wrong protocol"); break;
      case 2: Serial.println("ID rejected"); break;
      case 3: Serial.println("Server unavail"); break;
      case 4: Serial.println("Bad user/pass"); break;
      case 5: Serial.println("Not authed"); break;
      case 6: Serial.println("Failed to subscribe"); break;
      default: Serial.println("Connection failed"); break;
    }

    if(ret >= 0){
      mqtt.disconnect();
      return false;
    }
  }
  
  Serial.println();

  Serial.println("Adafruit IO Connected!");

  return true;
}
