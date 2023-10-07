# BiliMeter-Sensor
Creating a Bili-meter with a TCS34725 sensor to measure the irradiance of neonatal phototherapy lights

## Abstract

abstract

## Introduction

The Bili-Meter is a spectroradiometer that measures the therapeutic irradiance (radiant power) of neonatal phototherapy lights. It measures the irradiance of the wavelengths from 425 to 475 nanometers (nm), 
the blue-green portion of the spectrum, which includes the principal action spectrum of bilirubin. The Bili-Meter measures irradiance in units of microwatts per square centimeter per nanometer (µWW/cm2/nm). [(hkcalibrations)](https://www.hkcalibrations.com.au/bili-meter)

In this project, I try to make a device to detect the irradiance using TCS34725 which is an RGB sensor, and I will only use the Blue raw data and compare it with the GE Ohmeda Biliblanket Light Meter 2.

![image](https://github.com/RonAaron61/BiliMeter-Sensor/assets/105662575/0cf46927-b5ff-4d00-95ea-7f3f90c4015d)

After I get the TCS34725 and Biliblanket data on the same lighting, I make the Linear and polynomial trend lines and use the formula to calculate the irradiance

## TCS 34725

TCS 34725 is an RGB sensor, it can detect the value of intensity of RGB and Clear light with IR blocking filter. 

![image](https://github.com/RonAaron61/BiliMeter-Sensor/assets/105662575/64333472-2baf-492a-b677-f4f5f3731b7a)
[(Source)](https://www.adafruit.com/product/1334)

You just need to connect the vin, gnd, sda, and scl pin to the microcontroller of your choice, but in this project, I use Arduino Uno for simplicity, but later may change it to a smaller microcontroller.

Because this sensor detect RGB color, I only read the Blue intensity

## schematic

(image)

Implementing on project board using ESP32

![BlueLightSensor](https://github.com/RonAaron61/BiliMeter-Sensor/assets/105662575/ab3395c2-1541-41be-89ff-bdfb406ae5d1)


## Result - 1

*Note that I use the sensor with 4x gain to get this data, so there's a limit of the maximum light intensity it can capture, for a wider range of light intensity use 1x gain, but for now I use the 4x gain

I got a couple of data, the first and second were a little off when compared to the BiliBlanket meter, especially at higher intensity. Now at the third data that I collected, I get a decent result (for now)

Example of data that I got: 

![image](https://github.com/RonAaron61/BiliMeter-Sensor/assets/105662575/b7bacd96-a9f0-4e5f-b4fa-b13422423050)

For now, I only get the 0.1 to 4 µW/cm2/nm1, after that I make the graph (x is the TCS34725 blue light raw data, and Y is the biliblanket result), then plot the linear and polynomial trend line

![image](https://github.com/RonAaron61/BiliMeter-Sensor/assets/105662575/b470bd7a-4ec4-47df-844a-e71430ce5838)

Linear: 0.001x + 0.126

Polynomial: -6E-08x2 + 0.0012x + 0.0338

Then Implementing it to Arduino code:

irr_L = 0.001*int(blue) + 0.126; (Linear)

irr_P = ((-6.0e-08)*pow(int(blue),2)) + (0.0012*(int(blue))) + 0.0338; (polynomial)

--

I tried a couple of times and got 4 different results with different light-intensity data:

float irr_L = (0.001*int(blue)) + 0.3559;
float irr_L = 0.0011*int(blue) + 0.1497;
float irr_L = 0.001*int(blue) + 0.126;  //So far best
float irr_L = 0.0012*int(blue) - 0.0381;
  
double irr_P =  ((-2.0e-7)*pow(int(blue),2)) + (0.0019*(int(blue))) - 0.0418;
double irr_P = ((-2.0e-7)*pow(int(blue),2)) + (0.0015*(int(blue))) + 0.03018;
double irr_P = ((-6.0e-08)*pow(int(blue),2)) + (0.0012*(int(blue))) + 0.0338; //so far best
double irr_P = ((5.0e-08)*pow(int(blue),2)) + (0.0009*(int(blue))) + 0.17;

## Code

For the code I use the example from TCS34725 library, then change it so I get the raw data and input the blue light value to the formula the show the result to oled display

```
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);  //4X gain - use TCS34725_GAIN_1X for 1x gain

void setup() {
  Serial.begin(9600);
  //Serial.println("Color View Test!");

  if (tcs.begin()) {
    //Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
}

void loop() {
  Serial.print("\n");

  uint16_t red, green, blue, clear;
  
  tcs.setInterrupt(false);  // turn on LED

  delay(60);  // takes 50ms to read

  tcs.getRawData(&red, &green, &blue, &clear);
  
  tcs.setInterrupt(true);  // turn off LED

  float irr_L = 0.001*int(blue) + 0.126;  //So far best

  double irr_P = ((-6.0e-08)*pow(int(blue),2)) + (0.0012*(int(blue))) + 0.0338;
  
  Serial.print("C: "); Serial.print(int(clear)); 
  //Serial.print("R: "); Serial.print(int(red)); 
  //Serial.print("G: "); Serial.print(int(green)); 
  Serial.print(", B: "); Serial.print(int(blue));
  Serial.print(", Irrediance L: "); Serial.print(irr_L);
  Serial.print(", Irrediance P: "); Serial.print(irr_P);
  Serial.println();

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(10, 0);
  display.print("Irr L: ");
  display.println(irr_L);
  
  display.setCursor(10, 10);
  display.print("Irr P: ");
  display.println(irr_P);
  
  display.setCursor(10,20);
  display.print("Blue: ");
  display.println(int(blue));
  display.display();      // Show initial text
  delay(100);
}
```

--

After a couple of experiments with different light sources (LED light, sunlight, etc.) and getting the equations. I still get different results, because sometimes even when the sensor read with the same value when compared with the BiliBlanket sensor it got a different result. So maybe it still needs some adjustment, and above the sensor can be placed some blue light pass filter

![image](https://github.com/RonAaron61/BiliMeter-Sensor/assets/105662575/38f69f7e-fe08-42d7-9f8c-e2f48820c9a5)

To only let the blue light pass to the sensor, because based on the sensor datasheet the blue sensor still passes some other visible light to the sensor.

