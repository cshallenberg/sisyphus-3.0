#include <SPI.h>
#include <ADXL362.h>

int16_t XValue, YValue, ZValue, Temperature;

ADXL362 xl;

#define WIN_STATE_PIN 0

void setup() {
//  SPI.setMOSI(26); SPI.setMISO(1); SPI.setSCK(27); //change to second set of SPI pins
  Serial.begin(9600);
  xl.begin(0);                   // Setup SPI protocol, issue device soft reset Chip Select pin 0
  xl.beginMeasure();              // Switch ADXL362 to measure mode  
  
  Serial.println("Start Demo: Simple Read");

  pinMode(WIN_STATE_PIN, INPUT_PULLUP);
}

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
  check_win_state(); 
}

void check_win_state(){
  if (digitalRead(WIN_STATE_PIN)) {
    Serial.print("win state entered");
  }
}
