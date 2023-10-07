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

## Result - 1

I got a couple of data, the first and second were a little off when compared to the BiliBlanket meter, especially at higher intensity. Now at the third data that I collected, I get a decent result (for now)

Example of data that I got: 

![image](https://github.com/RonAaron61/BiliMeter-Sensor/assets/105662575/b7bacd96-a9f0-4e5f-b4fa-b13422423050)

For now, I only get the 0.1 to 4 µW/cm2/nm1, after that I make the graph (x is the TCS34725 blue light raw data, and Y is the biliblanket result), then plot the linear and polynomial trend line

![image](https://github.com/RonAaron61/BiliMeter-Sensor/assets/105662575/b470bd7a-4ec4-47df-844a-e71430ce5838)

Linear: 0.001x + 0.126

Polynomial: -6E-08x2 + 0.0012x + 0.0338

Then Implementing it to arduino code:

irr_L = 0.001*int(blue) + 0.126; (Linear)

irr_P = ((-6.0e-08)*pow(int(blue),2)) + (0.0012*(int(blue))) + 0.0338; (polynomial)

## Code

For the code I use the example from TCS34725 library, then change it so I get the raw data and input the blue light value to the formula

--

After a couple of experiments with different light sources (LED light, sunlight, etc.) and getting the equations. I still get different results, because sometimes even when the sensor read with the same value when compared with the BiliBlanket sensor it got a different result. So maybe it still needs some adjustment, and above the sensor can be placed some blue light pass filter

![image](https://github.com/RonAaron61/BiliMeter-Sensor/assets/105662575/38f69f7e-fe08-42d7-9f8c-e2f48820c9a5)

To only let the blue light pass to the sensor, because based on the sensor datasheet the blue sensor still passes some other visible light to the sensor.

