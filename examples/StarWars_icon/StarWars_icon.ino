/*
 StarWars full image 24bit converted and displayed fast!
 */

#include <SPI.h>
#include <OLED_pictivaWide.h>
#include "_icons/starwars.c"

#define RST_PIN   8
#define DC_PIN    23
#define CS_PIN    10


OLED_pictivaWide oled = OLED_pictivaWide(CS_PIN, DC_PIN, RST_PIN);

void setup() {
  oled.begin();
  oled.drawIcon(0, 0, &starwars);
}

void loop() {
  // put your main code here, to run repeatedly:

}