
// Libreria para usar las propiedades de conexión WiFi
#include <Wire.h>         //Conexión de dispositivos I2C
#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN_1 15  // Digital IO pin connected to the NeoPixels.
#define PIXEL_PIN_2 13  // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 4 // Number of NeoPixels

Adafruit_NeoPixel neopixelLEDs1(PIXEL_COUNT, PIXEL_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel neopixelLEDs2(PIXEL_COUNT, PIXEL_PIN_2, NEO_GRB + NEO_KHZ800);

//Variables
int color = 0;
int flag = 0;

void setup()
{
    Serial.begin(115200);
    Wire.begin(21, 22); // Pines I2C del ESP32
}

void loop()
{
    if (color == 255)
    {
        flag = 1;
    }else if (color == 0){
        flag = 0;
    }

    (flag == 0) ? color += 5: color -= 5;
    
    
    neopixelLEDs2.clear();
    neopixelLEDs1.clear();
    for (int i = 0; i < PIXEL_COUNT; i++)
    {
        neopixelLEDs1.setPixelColor(i, neopixelLEDs1.Color(color, 0, 0));
        neopixelLEDs2.setPixelColor(i, neopixelLEDs2.Color(0, color, 0));
    }
    neopixelLEDs1.show();
    neopixelLEDs2.show();
    delay(20);
}
