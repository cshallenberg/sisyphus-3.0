#include <Adafruit_NeoPixel.h>

// This array lists each of the display/animation drawing functions
// (which appear later in this code)
void (*renderFunc[])(void) {
  mode_twinkleRandom, mode_greenEye, mode_roll, mode_colorWipe, mode_rose, mode_half, mode_colorwheel, 
  mode_primaries, mode_sparkle
};
#define N_MODES (sizeof(renderFunc) / sizeof(renderFunc[0]))
uint8_t mode = 0; // Index of current mode in table

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
const long interval = 300000; //change mode every 5 minutes  

uint8_t  frame = 0;    // Frame count, results displayed every 256 frames

#define LED_PIN1    2
#define LED_PIN2    14
#define LED_PIN3    8
#define LED_PIN4    7
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

#define WIN_STATE_PIN 23
int currentState = 0;
int previousState = 0; 

void setup() {
  Serial.begin(9600);
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
  pinMode(WIN_STATE_PIN, INPUT_PULLDOWN);
}

// LOOP FUNCTION -- RUNS OVER AND OVER FOREVER -----------------------------

void loop() {

  (*renderFunc[mode])();          // Render one frame in current mode
  strip1.show(); // and update the NeoPixels to show it
  strip2.show(); // and update the NeoPixels to show it
  strip3.show(); // and update the NeoPixels to show it
  strip4.show(); // and update the NeoPixels to show it
  strip5.show(); // and update the NeoPixels to show it
  strip6.show(); // and update the NeoPixels to show it

  check_win_state();

  currentMillis = millis();
   if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    mode = random(N_MODES);
    Serial.print("Mode = "); Serial.println(mode);
   }
}

// RENDERING FUNCTIONS FOR EACH DISPLAY/ANIMATION MODE ---------------------

// All NeoPixels off
void mode_off() {
  strip1.clear();
  strip2.clear();
  strip3.clear();
  strip4.clear();
  strip5.clear();
  strip6.clear();
}

void mode_primaries() {
  uint32_t c;
  for(uint8_t i=0; i<120; i++) {
    uint8_t j = i + (i > 4);     // Mind the gap
    j = ((millis() / 25) + j) % 12;
    if(j < 4)      c = 0xEB4034; // Bed
    else if(j < 8) c = 0x34EB98; // Green
    else           c = 0x9B343B; // Blue
    strip1.setPixelColor(i, c);
    strip2.setPixelColor(i, c);
    strip3.setPixelColor(i, c);
    strip4.setPixelColor(i, c);
    strip5.setPixelColor(i, c);
    strip6.setPixelColor(i, c);
  }
}

// HSV (hue-saturation-value) to RGB function used for the next two modes.
uint32_t hsv2rgb(int32_t h, uint8_t s, uint8_t v, boolean gc=false) {
  uint8_t n, r, g, b;

  // Hue circle = 0 to 1530 (NOT 1536!)
  h %= 1530;           // -1529 to +1529
  if(h < 0) h += 1530; //     0 to +1529
  n  = h % 255;        // Angle within sextant; 0 to 254 (NOT 255!)
  switch(h / 255) {    // Sextant number; 0 to 5
   case 0 : r = 255    ; g =   n    ; b =   0    ; break; // R to Y
   case 1 : r = 254 - n; g = 255    ; b =   0    ; break; // Y to G
   case 2 : r =   0    ; g = 255    ; b =   n    ; break; // G to C
   case 3 : r =   0    ; g = 254 - n; b = 255    ; break; // C to B
   case 4 : r =   n    ; g =   0    ; b = 255    ; break; // B to M
   default: r = 255    ; g =   0    ; b = 254 - n; break; // M to R
  }

  uint32_t v1 =   1 + v; // 1 to 256; allows >>8 instead of /255
  uint16_t s1 =   1 + s; // 1 to 256; same reason
  uint8_t  s2 = 255 - s; // 255 to 0

  r = ((((r * s1) >> 8) + s2) * v1) >> 8;
  g = ((((g * s1) >> 8) + s2) * v1) >> 8;
  b = ((((b * s1) >> 8) + s2) * v1) >> 8;
  return ((uint32_t)r << 16) | ((uint16_t)g << 8) | b;
}

// Rotating color wheel, using 'raw' RGB values.
void mode_colorwheel() {
  uint32_t t = millis();
  for(uint8_t i=0; i<120; i++) {
    uint8_t j = i + (i > 4);
          strip1.setPixelColor(i,
      hsv2rgb(t + j * 1530 / 12, 255, 255, false));
          strip2.setPixelColor(i,
      hsv2rgb(t + j * 1530 / 12, 255, 255, false));
          strip3.setPixelColor(i,
      hsv2rgb(t + j * 1530 / 12, 255, 255, false));
          strip4.setPixelColor(i,
      hsv2rgb(t + j * 1530 / 12, 255, 255, false));
          strip5.setPixelColor(i,
      hsv2rgb(t + j * 1530 / 12, 255, 255, false));
          strip6.setPixelColor(i,
      hsv2rgb(t + j * 1530 / 12, 255, 255, false));
  }
}

// Cycle with half the pixels on, half off at any given time.
void mode_half() {
  uint32_t t = millis() / 4;
  for(uint8_t i=0; i<120; i++) {
    uint8_t j = t + i * 256 / 10;
    j = (j >> 7) * 255;
    strip1.setPixelColor(i, j * 0x010000);
    strip2.setPixelColor(i, j * 0x010000);
    strip3.setPixelColor(i, j * 0x010000);
    strip4.setPixelColor(i, j * 0x010000);
    strip5.setPixelColor(i, j * 0x010000);
    strip6.setPixelColor(i, j * 0x010000);  
  }
}

// Blue sparkles.  Randomly turns on ONE pixel at a time.
void mode_sparkle() {
  static uint8_t randomPixel = 0;
  if(!(frame & 0x7F)) {              // Every 128 frames...
    strip1.clear(); // Clear pixels
    strip2.clear(); // Clear pixels
    strip3.clear(); // Clear pixels
    strip4.clear(); // Clear pixels
    strip5.clear(); // Clear pixels
    strip6.clear(); // Clear pixels
    uint8_t r;
    do {
      r = random(120);                // Pick a new random pixel
    } while(r == randomPixel);       // but not the same as last time
    randomPixel = r;                 // Save new random pixel index
    strip1.setPixelColor(randomPixel, 81, 66, 245);
    strip2.setPixelColor(randomPixel, 81, 66, 245);
    strip3.setPixelColor(randomPixel, 81, 66, 245);
    strip4.setPixelColor(randomPixel, 81, 66, 245);
    strip5.setPixelColor(randomPixel, 81, 66, 245);
    strip6.setPixelColor(randomPixel, 81, 66, 245);
  }
}

// Simple on-or-off "marquee" animation w/ about 50% of pixels lit at once.
void mode_greenEye() {
  int number = random(4,18);
  uint32_t t = millis();
  for(uint8_t i=0; i<120; i++) {
    uint8_t j = i + (i > 4);
    uint8_t k = (t + j * 256 / number) & 0xFF;
    k = ((k >> 6) & 1) * 255;
    strip1.setPixelColor(i, k * 0x000100L);
    strip2.setPixelColor(i, k * 0x000100L);
    strip3.setPixelColor(i, k * 0x000100L);
    strip4.setPixelColor(i, k * 0x000100L);
    strip5.setPixelColor(i, k * 0x000100L);
    strip6.setPixelColor(i, k * 0x000100L);
  }
}

void mode_colorWipe()
{
  for (int i=0; i < 120; i++) {
    strip1.setPixelColor(i, 235,52,143); //rose
    strip2.setPixelColor(i, 0,0,0);
    strip3.setPixelColor(i, 235,52,143);
    strip4.setPixelColor(i, 0,0,0);
    strip5.setPixelColor(i, 235,52,143);
    strip6.setPixelColor(i, 0,0,0);
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
    delay(20);
  }
    for (int i=120; i > 0; i--) {
    strip1.setPixelColor(i, 0,0,0);  
    strip2.setPixelColor(i, 235,52,143);
    strip3.setPixelColor(i, 0,0,0);
    strip4.setPixelColor(i, 235,52,143);
    strip5.setPixelColor(i, 0,0,0);
    strip6.setPixelColor(i, 235,52,143);
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
    delay(20);
  }
    for (int i=0; i < 120; i++) {
    strip1.setPixelColor(i, 52,229,235); //aqua
    strip2.setPixelColor(i, 0,0,0);
    strip3.setPixelColor(i, 52,229,235);
    strip4.setPixelColor(i, 0,0,0);
    strip5.setPixelColor(i, 52,229,235);
    strip6.setPixelColor(i, 0,0,0);
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
    delay(20);
  }
    for (int i=120; i > 0; i--) {
    strip1.setPixelColor(i, 0,0,0);  
    strip2.setPixelColor(i, 52,229,235);
    strip3.setPixelColor(i, 0,0,0);
    strip4.setPixelColor(i, 52,229,235);
    strip5.setPixelColor(i, 0,0,0);
    strip6.setPixelColor(i, 52,229,235);
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
    delay(20);
  }
      for (int i=0; i < 120; i++) {
    strip1.setPixelColor(i, 61,52,235); //blue
    strip2.setPixelColor(i, 0,0,0);
    strip3.setPixelColor(i, 61,52,235);
    strip4.setPixelColor(i, 0,0,0);
    strip5.setPixelColor(i, 61,52,235);
    strip6.setPixelColor(i, 0,0,0);
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
    delay(20);
  }
    for (int i=120; i > 0; i--) {
    strip1.setPixelColor(i, 0,0,0);  
    strip2.setPixelColor(i, 61,52,235);
    strip3.setPixelColor(i, 0,0,0);
    strip4.setPixelColor(i, 61,52,235);
    strip5.setPixelColor(i, 0,0,0);
    strip6.setPixelColor(i, 61,52,235);
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
    delay(20);
  }
}

void mode_rose() {
    int r = 230, g = 18, b = 18;
      //  Flicker, based on our initial RGB values
  for(int i=0; i<120; i++) {
    int flicker = random(0,55);
    int r1 = r-flicker;
    int g1 = g-flicker;
    int b1 = b-flicker;
    if(g1<0) g1=0;
    if(r1<0) r1=0;
    if(b1<0) b1=0;
    strip1.setPixelColor(i,r1,g1, b1);
    strip2.setPixelColor(i,r1,g1, b1);
    strip3.setPixelColor(i,r1,g1, b1);
    strip4.setPixelColor(i,r1,g1, b1);
    strip5.setPixelColor(i,r1,g1, b1);
    strip6.setPixelColor(i,r1,g1, b1);
  }
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();

  delay(random(10,113));
}

void mode_roll() {
  int r = random(255); int g = random(255); int b = random(255);
  for(int i=0; i<120; i++) {
  strip1.setPixelColor(i,r, g, b);
  strip2.clear();
  strip3.clear();
  strip4.clear();
  strip5.clear();
  strip6.clear();
  }
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
    delay(50);
  
    for(int i=0; i<120; i++) {
  strip1.clear();
  strip2.setPixelColor(i,r, g, b);
  strip3.clear();
  strip4.clear();
  strip5.clear();
  strip6.clear();
  }
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
    delay(50);

    for(int i=0; i<120; i++) {
  strip1.clear();
  strip2.clear();
  strip3.setPixelColor(i,r, g, b);
  strip4.clear();
  strip5.clear();
  strip6.clear();
  }
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
    delay(50);
    
    for(int i=0; i<120; i++) {
  strip1.clear();
  strip2.clear();
  strip3.clear();
  strip4.setPixelColor(i,r, g, b);
  strip5.clear();
  strip6.clear();
  }
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
    delay(50);
    
    for(int i=0; i<120; i++) {
  strip1.clear();
  strip2.clear();
  strip3.clear();
  strip4.clear();
  strip5.setPixelColor(i,r, g, b);
  strip6.clear();
  }
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
    delay(50);

    for(int i=0; i<120; i++) {
  strip1.clear();
  strip2.clear();
  strip3.clear();
  strip4.clear();
  strip5.clear();
  strip6.setPixelColor(i,r, g, b);
  }
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
    delay(50);
}

void mode_twinkleRandom() {
  int btime = random(20,100);
  int number = random(10,50);  
  strip1.clear();
  strip2.clear();
  strip3.clear();
  strip4.clear();
  strip5.clear();
  strip6.clear();
  for (int i=0; i<number; i++) {
     strip1.setPixelColor(random(120),random(0,255),random(0,255),random(0,255));
     strip2.setPixelColor(random(120),random(0,255),random(0,255),random(0,255));
     strip3.setPixelColor(random(120),random(0,255),random(0,255),random(0,255));
     strip4.setPixelColor(random(120),random(0,255),random(0,255),random(0,255));
     strip5.setPixelColor(random(120),random(0,255),random(0,255),random(0,255));
     strip6.setPixelColor(random(120),random(0,255),random(0,255),random(0,255));
  strip1.show();
  strip2.show();
  strip3.show();
  strip4.show();
  strip5.show();
  strip6.show();
     delay(btime);
   } 
  delay(btime);
}

void check_win_state(){
  if (digitalRead(WIN_STATE_PIN)) {
    currentState = 1;
  } else {
    currentState = 0;
  }
  if (currentState != previousState) {
    if (currentState == 1) { 
    previousState = currentState;  
    Serial.println("win state entered");
    mode = random(N_MODES);
    Serial.print("Mode = "); Serial.println(mode);
    } else {
    previousState = currentState;   
    mode = random(N_MODES);
    Serial.print("Mode = "); Serial.println(mode);
    previousMillis = currentMillis;  
    }
   }
  }
