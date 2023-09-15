#include <Wire.h>
#include "Adafruit_TCS34725.h"

// our RGB -> eye-recognized gamma color
byte gammatable[256];

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
  //Serial.println("Color View Test!");

  if (tcs.begin()) {
    //Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

void loop() {
//  float red, green, blue;
//  
//  tcs.setInterrupt(false);  // turn on LED
//
//  delay(60);  // takes 50ms to read
//
//  tcs.getRGB(&red, &green, &blue);
//  
//  tcs.setInterrupt(true);  // turn off LED
//
//  Serial.print("R:\t"); Serial.print(int(red)); 
//  Serial.print("\tG:\t"); Serial.print(int(green)); 
//  Serial.print("\tB:\t"); Serial.print(int(blue));

//  Serial.print("\t");
//  Serial.print((int)red, HEX); Serial.print((int)green, HEX); Serial.print((int)blue, HEX);
  Serial.print("\n");

  uint16_t red, green, blue, clear;
  
  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRawData(&red, &green, &blue, &clear);
  
  tcs.setInterrupt(true);  // turn off LED
  //float irr_L = (0.001*int(blue)) + 0.3559;
  //float irr_L = 0.0011*int(blue) + 0.1497;
  float irr_L = 0.001*int(blue) + 0.126;

  //double irr_P =  ((-2.0e-7)*pow(int(blue),2)) + (0.0019*(int(blue))) - 0.0418;
  //double irr_P = ((-2.0e-7)*pow(int(blue),2)) + (0.0015*(int(blue))) + 0.03018;
  double irr_P = ((-6.0e-08)*pow(int(blue),2)) + (0.0012*(int(blue))) + 0.0338;

  Serial.print("C: "); Serial.print(int(clear)); 
  //Serial.print("R: "); Serial.print(int(red)); 
  //Serial.print("G: "); Serial.print(int(green)); 
  Serial.print(", B: "); Serial.print(int(blue));
  Serial.print(", Irrediance L: "); Serial.print(irr_L);
  Serial.print(", Irrediance P: "); Serial.print(irr_P);
  Serial.println();
}
