#include <Adafruit_NeoPixel.h>

uint8_t  frame = 0;    // Frame count, results displayed every 256 frames

#define LED_PIN1    2
#define LED_PIN2    14
#define LED_PIN3    7
#define LED_PIN4    8
#define LED_PIN5    6
#define LED_PIN6    21

// How many NeoPixels are attached to each pin
#define LED_COUNT 120

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip1(LED_COUNT, LED_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT, LED_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3(LED_COUNT, LED_PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4(LED_COUNT, LED_PIN4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5(LED_COUNT, LED_PIN5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6(LED_COUNT, LED_PIN6, NEO_GRB + NEO_KHZ800);

// SETUP FUNCTION -- RUNS ONCE AT PROGRAM START ----------------------------

void setup() {
  strip1.begin();
  strip1.setBrightness(255); // NeoPixels at full brightness
  strip2.begin();
  strip2.setBrightness(255); 
  strip3.begin();
  strip3.setBrightness(255); 
  strip4.begin();
  strip4.setBrightness(255); 
  strip5.begin();
  strip5.setBrightness(255); 
  strip6.begin();
  strip6.setBrightness(255); 

}

// LOOP FUNCTION -- RUNS OVER AND OVER FOREVER -----------------------------

void loop() {

  mode_sparkle();
  strip1.show(); // and update the NeoPixels to show it
  strip2.show(); // and update the NeoPixels to show it
  strip3.show(); // and update the NeoPixels to show it
  strip4.show(); // and update the NeoPixels to show it
  strip5.show(); // and update the NeoPixels to show it
  strip6.show(); // and update the NeoPixels to show it

}

// Blue sparkles.  Randomly turns on ONE pixel at a time.  This demonstrates
// minimal power use while still doing something "catchy."  And because it's
// a primary color, power use is even minimal-er (see 'primaries' above).
void mode_sparkle() {
  static uint8_t randomPixel1 = 0;
  if(!(frame & 0x7F)) {              // Every 128 frames...
    strip1.clear(); // Clear pixels
    uint8_t r1;
    do {
      r1 = random(strip1.numPixels());                // Pick a new random pixel
    } while(r1 == randomPixel1);       // but not the same as last time
    randomPixel1 = r1;                 // Save new random pixel index
    strip1.setPixelColor(randomPixel1, 0x0000FF);
  }
    static uint8_t randomPixel2 = 0;
  if(!(frame & 0x7F)) {              // Every 128 frames...
    strip2.clear(); // Clear pixels
    uint8_t r2;
    do {
      r2 = random(strip2.numPixels());                // Pick a new random pixel
    } while(r2 == randomPixel2);       // but not the same as last time
    randomPixel2 = r2;                 // Save new random pixel index
    strip2.setPixelColor(randomPixel2, 0x0000FF);
  }
      static uint8_t randomPixel3 = 0;
  if(!(frame & 0x7F)) {              // Every 128 frames...
    strip3.clear(); // Clear pixels
    uint8_t r3;
    do {
      r3 = random(strip3.numPixels());                // Pick a new random pixel
    } while(r3 == randomPixel3);       // but not the same as last time
    randomPixel3 = r3;                 // Save new random pixel index
    strip3.setPixelColor(randomPixel3, 0x0000FF);
  }
      static uint8_t randomPixel4 = 0;
  if(!(frame & 0x7F)) {              // Every 128 frames...
    strip4.clear(); // Clear pixels
    uint8_t r4;
    do {
      r4 = random(strip4.numPixels());                // Pick a new random pixel
    } while(r4 == randomPixel4);       // but not the same as last time
    randomPixel4 = r4;                 // Save new random pixel index
    strip4.setPixelColor(randomPixel4, 0x0000FF);
  }
      static uint8_t randomPixel5 = 0;
  if(!(frame & 0x7F)) {              // Every 128 frames...
    strip5.clear(); // Clear pixels
    uint8_t r5;
    do {
      r5 = random(strip5.numPixels());                // Pick a new random pixel
    } while(r5 == randomPixel5);       // but not the same as last time
    randomPixel5 = r5;                 // Save new random pixel index
    strip5.setPixelColor(randomPixel5, 0x0000FF);
  }
      static uint8_t randomPixel6 = 0;
  if(!(frame & 0x7F)) {              // Every 128 frames...
    strip6.clear(); // Clear pixels
    uint8_t r6;
    do {
      r6 = random(strip6.numPixels());                // Pick a new random pixel
    } while(r6 == randomPixel6);       // but not the same as last time
    randomPixel6 = r6;                 // Save new random pixel index
    strip6.setPixelColor(randomPixel6, 0x0000FF);
  }
}
