/*
A basic test, it just write something by using a different font
*/
#include <SPI.h>
#include <OLED_pictivaWide.h>
#include "_fonts/arial_x3.c"//check the _font folder for more fonts!

#define RST_PIN   8
#define DC_PIN    23
#define CS_PIN    10

OLED_pictivaWide oled = OLED_pictivaWide(CS_PIN, DC_PIN, RST_PIN);;


void setup() {
  Serial.begin(38400);
  long unsigned debug_start = millis ();
  while (!Serial && ((millis () - debug_start) <= 5000)) ;
  Serial.println("started");
  oled.begin();
  oled.setFont(&arial_x3);//easy!
  oled.println("Hello World");
}


void loop() {

}




