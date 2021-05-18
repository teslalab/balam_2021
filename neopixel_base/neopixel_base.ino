#include <Wire.h> //I2C
#include <Adafruit_NeoPixel.h>

#define PIXEL_COUNT 4
#define PIXEL_PIN_1 15
#define PIXEL_PIN_2 13

Adafruit_NeoPixel neopixel1(PIXEL_COUNT, PIXEL_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel neopixel2(PIXEL_COUNT, PIXEL_PIN_2, NEO_GRB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:
  Wire.begin(21, 22); //Pines I2C de nuestro ESP32
}

void loop() {

  //neopixel1 U0 - U3
  //neopixel2 U4 - U7
                        //indice, color
  for(int i = 0; i < PIXEL_COUNT; i++){
    neopixel1.setPixelColor(i, neopixel1.Color(25,0,0));
  }
  neopixel2.setPixelColor(0, neopixel2.Color(0,0,25));
  
  neopixel1.show();
  neopixel2.show();

  delay(1000);
  
  neopixel1.clear();
  neopixel2.clear();
  neopixel1.show();
  neopixel2.show();

  delay(1000);
  
}