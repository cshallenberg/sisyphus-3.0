
#include <SPI.h>
#include <ADXL362.h>

#include <OctoWS2811.h>

int16_t temp;
int16_t XValue, YValue, ZValue, Temperature;

ADXL362 xl;

const int ledsPerStrip = 120; 

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

uint8_t  frame = 0;    // Frame count, results displayed every 256 frames

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);

void setup() {
  SPI.setMOSI(26); SPI.setMISO(1); SPI.setSCK(27); //change to second set of SPI pins
  Serial.begin(9600);
  xl.begin(0);                   // Setup SPI protocol, issue device soft reset Chip Select pin 0
  xl.beginMeasure();              // Switch ADXL362 to measure mode  
  
  Serial.println("Start Demo: Simple Read");
  
  leds.begin();
  leds.show();
}

#define RED    0xFF0000
#define GREEN  0x00FF00
#define BLUE   0x0000FF
#define YELLOW 0xFFFF00
#define PINK   0xFF1088
#define ORANGE 0xE05800

void loop() {
  xl.readXYZTData(XValue, YValue, ZValue, Temperature);  
  Serial.print("XVALUE=");
  Serial.print(XValue);   
  Serial.print("\tYVALUE=");
  Serial.print(YValue);  
  Serial.print("\tZVALUE=");
  Serial.print(ZValue);  
  Serial.print("\tTEMPERATURE=");
  Serial.println(Temperature);   
  delay(100);                // Arbitrary delay to make serial monitor easier to observe
  
  int microsec = 2000000 / leds.numPixels();  // change them all in 2 seconds

  // uncomment for voltage controlled speed
  // millisec = analogRead(A9) / 40;
 
  colorWipe(RED, microsec);
  colorWipe(GREEN, microsec);
  colorWipe(BLUE, microsec);
  colorWipe(YELLOW, microsec);
  colorWipe(PINK, microsec);
  colorWipe(ORANGE, microsec);
}

void colorWipe(int color, int wait)
{
  for (int i=0; i < leds.numPixels(); i++) {
    leds.setPixel(i, color);
    leds.show();
    delayMicroseconds(wait);
  }
}
