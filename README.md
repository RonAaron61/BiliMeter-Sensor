# BiliMeter-Sensor
Creating a Bili-meter with a TCS34725 sensor to measure the irradiance of neonatal phototherapy lights

## Abstract

abstract

## Introduction

The Bili-Meter is a spectroradiometer that measures the therapeutic irradiance (radiant power) of neonatal phototherapy lights. It measures the irradiance of the wavelengths from 425 to 475 nanometers (nm), 
the blue-green portion of the spectrum, which includes the principal action spectrum of bilirubin. The Bili-Meter measures irradiance in units of microwatts per square centimeter per nanometer (pW/cm2/nm). [(hkcalibrations)](https://www.hkcalibrations.com.au/bili-meter)

In this project, I try to make a device to detect the irradiance using TCS34725 which is an RGB sensor, and I will only use the Blue raw data and compare it with the GE Ohmeda Biliblanket Light Meter.

![image](https://github.com/RonAaron61/BiliMeter-Sensor/assets/105662575/0cf46927-b5ff-4d00-95ea-7f3f90c4015d)

After I get the TCS34725 and Biliblanket data on the same lighting, I make the Linear and polynomial trend lines and use the formula to calculate the irradiance

## TCS 34725

TCS 34725 is an RGB sensor, it can detect the value of intensity of RGB and Clear light with IR blocking filter. 

![image](https://github.com/RonAaron61/BiliMeter-Sensor/assets/105662575/64333472-2baf-492a-b677-f4f5f3731b7a)
[(Source)](https://www.adafruit.com/product/1334)

You just need to connect the vin, gnd, sda, and scl pin to the microcontroller of your choice, but in this project, I use Arduino Uno for simplicity.

