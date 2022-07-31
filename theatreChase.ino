

#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN1    2
#define LED_PIN2    14
#define LED_PIN3    7
#define LED_PIN4    8
#define LED_PIN5    6
#define LED_PIN6    21

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 120

Adafruit_NeoPixel strip1(LED_COUNT, LED_PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED_COUNT, LED_PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip3(LED_COUNT, LED_PIN3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip4(LED_COUNT, LED_PIN4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip5(LED_COUNT, LED_PIN5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip6(LED_COUNT, LED_PIN6, NEO_GRB + NEO_KHZ800);


// setup() function -- runs once at startup --------------------------------

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
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
}

void loop() {


  // Do a theater marquee effect in various colors...
  theaterChase(strip1.Color(127, 127, 127), 50); // White, half brightness
  theaterChase(strip1.Color(  252,   3, 232), 50); // magenta, half brightness
  theaterChase(strip1.Color(3, 252, 169), 50); // aqua, half brightness
  theaterChase(strip1.Color(211,   3,   252), 50); // pink, half brightness
  theaterChase(strip6.Color(  3,   65, 252), 50); // blue, half brightness

}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip1.clear();         //   Set all pixels in RAM to 0 (off)
      strip2.clear();
      strip3.clear();
      strip4.clear();
      strip5.clear();
      strip6.clear();
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip4.numPixels(); c += 3) {
        strip1.setPixelColor(c, color); // Set pixel 'c' to value 'color'
        strip2.setPixelColor(c, color); // Set pixel 'c' to value 'color'
        strip3.setPixelColor(c, color); // Set pixel 'c' to value 'color'
        strip4.setPixelColor(c, color); // Set pixel 'c' to value 'color'
        strip5.setPixelColor(c, color); // Set pixel 'c' to value 'color'
        strip6.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip1.show(); // Update strip with new contents
      strip2.show(); // Update strip with new contents
      strip3.show(); // Update strip with new contents
      strip4.show(); // Update strip with new contents
      strip5.show(); // Update strip with new contents
      strip6.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}
