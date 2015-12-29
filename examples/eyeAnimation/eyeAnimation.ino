/*
This sample uses basic simple drawIcon to draw an animation!
CAUTION! Uses a lot of memory! Not all CPU can handle this, 
you can limit ram usage by getting rid of some include and shorten consequently the animation array!
*/
#include <SPI.h>
#include <OLED_pictivaWide.h>
#include "_icons/eye0.c"
#include "_icons/eye1.c"
#include "_icons/eye2.c"
#include "_icons/eye3.c"
#include "_icons/eye4.c"
#include "_icons/eye5.c"
#include "_icons/eye6.c"
#include "_icons/eye7.c"
#include "_icons/eye8.c"
#include "_icons/eye9.c"
#include "_icons/eye10.c"
#include "_icons/eye11.c"
#include "_icons/eye12.c"
#include "_icons/eye13.c"
#include "_icons/eye14.c"
#include "_icons/eye15.c"
#include "_icons/eye16.c"
#include "_icons/eye17.c"
#include "_icons/eye93.c"

const tIcon animation[19] = {
  eye0, eye1, eye2, eye3, eye4, eye5, eye6, eye7,
  eye8, eye9, eye10, eye11, eye12, eye13, eye14, eye15, eye16,
  eye17, eye93
};

#define RST_PIN   8
#define DC_PIN    23
#define CS_PIN    10

OLED_pictivaWide oled = OLED_pictivaWide(CS_PIN, DC_PIN, RST_PIN);

void setup() {
  //  Serial.begin(38400);
  //  long unsigned debug_start = millis ();
  //  while (!Serial && ((millis () - debug_start) <= 5000)) ;
  //  Serial.println("started");
  oled.begin();
}


void loop() {
  for (int i = 0; i < 19; i++) {
    oled.clearScreen();
    oled.drawIcon(30, 0, &animation[i]);
    oled.drawIcon(50, 0, &animation[i]);
    delay(50);
  }
}

