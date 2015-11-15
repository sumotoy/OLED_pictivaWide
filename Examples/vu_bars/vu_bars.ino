/*
Using the hardware accellerated capabilities of SSD chip inside Pictiva
OLED you can easily create VU-BARS (in this case 32) to use in your projects
with just some small code, here's an example.
 */

#include <SPI.h>
#include <OLED_pictivaWide.h>

#define RST_PIN   8
#define DC_PIN    23
#define CS_PIN    10

uint8_t barBands = 32;
uint8_t startBarsX = 0;
uint8_t barWidth = 6;
uint8_t barSpacing = 3;
uint8_t mxBarVal = 47;//max 47
uint8_t barColor = 0xFF;
uint8_t barValues[32];//0..47

OLED_pictivaWide oled = OLED_pictivaWide(CS_PIN, DC_PIN, RST_PIN);

void setup() {
  /*
  Serial.begin(38400);
  long unsigned debug_start = millis ();
  while (!Serial && ((millis () - debug_start) <= 5000)) ;
  Serial.println("started");
  */
  reset_vals();
  oled.begin();
  draw_bars();


}


void loop() {
  reset_vals();
  delay(40);
  draw_bars();
}

void reset_vals(void) {
  for (uint8_t i = 0; i < barBands; i++) { //reset values
    barValues[i] = random(0,mxBarVal);
  }
}


void draw_bars(void) {
  for (uint8_t i = 0; i < barBands; i++) {
    if (i > 0) {
      oled.drawRect((startBarsX + barSpacing + barWidth) + (barWidth + barSpacing) * (i - 1), 0, barWidth, mxBarVal - barValues[i] - 1, 2, 0);//top
      oled.drawRect((startBarsX + barSpacing + barWidth) + (barWidth + barSpacing) * (i - 1), mxBarVal - barValues[i], barWidth, barValues[i], barColor, 0);//val
    } else {
      oled.drawRect(startBarsX, 0, barWidth, mxBarVal - barValues[i] - 1, 2, 0);//top
      oled.drawRect(startBarsX, mxBarVal - barValues[i], barWidth, barValues[i], barColor, 0);//val
    }
  }
}

