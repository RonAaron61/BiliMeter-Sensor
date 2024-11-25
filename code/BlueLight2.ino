#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <driver/adc.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_1X);

bool Pause = 0;

void setup() {
  Serial.begin(9600);

  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);

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
  //  float red, green, blue;
  
  //  tcs.setInterrupt(false);  // turn on LED
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
  //Serial.println(adc1_get_raw((adc1_channel_t)4));
  
  if ((adc1_get_raw((adc1_channel_t)4)) > 1000){
    Pause = !Pause;
    delay(500);
  }
  
  if (!Pause) {
    uint16_t red, green, blue, clear;
    float red2, green2, blue2;
  
    tcs.setInterrupt(false);  // turn on LED

    delay(60);  // takes 50ms to read

    tcs.getRawData(&red, &green, &blue, &clear);
    tcs.getRGB(&red2, &green2, &blue2);
  
    tcs.setInterrupt(true);  // turn off LED
    //float irr_L = (0.001*int(blue)) + 0.3559;
    //float irr_L = 0.0011*int(blue) + 0.1497;
    //float irr_L = 0.001*int(blue) + 0.126;  //So far best
    //float irr_L = 0.0012*int(blue) - 0.0381;
    float irr_L = 0.0101*int(blue) + 0.2461; // 25/11/2024
  
    //float irr_L = 0.0041*int(blue) + 0.0842; //Gain 1X

    //double irr_P =  ((-2.0e-7)*pow(int(blue),2)) + (0.0019*(int(blue))) - 0.0418;
    //double irr_P = ((-2.0e-7)*pow(int(blue),2)) + (0.0015*(int(blue))) + 0.03018;
    //double irr_P = ((-6.0e-08)*pow(int(blue),2)) + (0.0012*(int(blue))) + 0.0338; //so far best
    //double irr_P = ((5.0e-08)*pow(int(blue),2)) + (0.0009*(int(blue))) + 0.17;
    double irr_P = ((5.0e-8)*pow(int(blue),2)) + (0.0099*(int(blue))) + 0.3683; // 25/11/2024
  
    //Serial.print("C: "); Serial.print(int(clear)); 
    //Serial.print("R: "); Serial.print(int(red)); 
    //Serial.print("G: "); Serial.print(int(green)); 
    //Serial.print(", B: "); Serial.print(int(blue));
    //Serial.print(", Irrediance L: "); Serial.print(irr_L);
    //Serial.print(", Irrediance P: "); Serial.print(irr_P);
    //Serial.println();

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
  
    display.setCursor(0, 0);
    display.print("Irr L: ");
    display.println(irr_L);
  
    display.setCursor(0, 10);
    display.print("Irr P: ");
    display.println(irr_P);

    display.setCursor(0, 20);
    display.print("Ave : ");
    display.println((irr_P + irr_L)/2);
  
    display.setTextSize(1);
    display.setCursor(0,30);
    display.print("Blue1: ");
    display.setTextSize(2);
    display.println(int(blue));

    display.setTextSize(1);
    display.setCursor(0,45);
    display.print("Blue2: ");
    display.setTextSize(2);
    display.print(int(blue2));
    display.display();      // Show initial text
    delay(40);
  }
  else{
    display.display();      // Show initial text
    display.setTextSize(1);
    display.setCursor(80,55);
    display.print("Pause");
  }
}
