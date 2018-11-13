#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define IO_SERVER "io.adafruit.com"
#define IO_PORT 1883
#define IO_USER "oskrpnk" //(const char*)iouser
#define IO_KEY "7e8f475838e24dce8e82008523b642b0" //(const char*)iokey

Adafruit_MQTT_Client mqtt(&client, IO_SERVER, IO_PORT, IO_USER, IO_KEY);

Adafruit_MQTT_Publish indoor_temp = Adafruit_MQTT_Publish(&mqtt, iouser + "oskrpnk/feeds/indoor-temp");
Adafruit_MQTT_Publish indoor_humi = Adafruit_MQTT_Publish(&mqtt, iouser + "oskrpnk/feeds/indoor-humi");
void io_connect() {

  Serial.print("Connecting to Adafruit IO... ");

  int8_t ret;

  while ((ret = mqtt.connect()) != 0) {

    switch (ret) {
      case 1: Serial.println("Wrong protocol"); break;
      case 2: Serial.println("ID rejected"); break;
      case 3: Serial.println("Server unavail"); break;
      case 4: Serial.println("Bad user/pass"); break;
      case 5: Serial.println("Not authed"); break;
      case 6: Serial.println("Failed to subscribe"); break;
      default: Serial.println("Connection failed"); break;
    }

    if(ret >= 0)
      mqtt.disconnect();

    Serial.println("Retrying connection...");
    delay(5000);

  }

  Serial.println("Adafruit IO Connected!");
}
