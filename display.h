#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display;

void displayInit(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void displayTime(){
  display.clearDisplay();
  display.drawLine(0, 10, display.width(), 10, WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,1);  
  display.println("00:00");

  display.display();
}



