/*
A basic test, it just write something!
*/
#include <SPI.h>
#include <OLED_pictivaWide.h>


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
  oled.println("Hello World");
  //by default the library uses arial_x2
  //check other_fonts example for learn how to use different fonts!
}


void loop() {

}




