
#include <Adafruit_NeoPixel.h>
#include <EasyBuzzer.h>
#include <TB6612_ESP32.h>

#define PIXEL_PIN_1 13  // Digital IO pin connected to the NeoPixels.
#define PIXEL_PIN_2 15  // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 4 // Number of NeoPixels
#define BUZZER_PIN 27

//MOTOR1
#define AIN1 32
#define AIN2 33
#define PWMA 12

//MOTOR2
#define BIN1 25
#define BIN2 26
#define PWMB 14

const int offsetA = 1;
const int offsetB = -1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, 0, 5000, 8, 1);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, 0, 5000, 8, 2);

Adafruit_NeoPixel neopixelLEDs1(PIXEL_COUNT, PIXEL_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel neopixelLEDs2(PIXEL_COUNT, PIXEL_PIN_2, NEO_GRB + NEO_KHZ800);

void setup()
{
    Serial.begin(115200);
    Serial.println("Comenzando test");
    EasyBuzzer.setPin(BUZZER_PIN);  //Initialize buzzer
    pinMode(BUZZER_PIN, OUTPUT);
}

void loop()
{
    testNeoPixel();
    //testBuzzer();
    testMotores();
}

void testNeoPixel()
{
    neopixelLEDs1.clear();
    neopixelLEDs2.clear();
    for (int i = 0; i < PIXEL_COUNT; i++)
    {
        neopixelLEDs1.setPixelColor(i, neopixelLEDs1.Color(0, 0, 255));
        neopixelLEDs2.setPixelColor(i, neopixelLEDs2.Color(0, 0, 255));
    }
    neopixelLEDs1.show();
    neopixelLEDs2.show();
    delay(500);

    neopixelLEDs1.clear();
    neopixelLEDs2.clear();
    for (int i = 0; i < PIXEL_COUNT; i++)
    {
        neopixelLEDs1.setPixelColor(i, neopixelLEDs1.Color(0, 255, 0));
        neopixelLEDs2.setPixelColor(i, neopixelLEDs2.Color(0, 255, 0));
    }
    neopixelLEDs1.show();
    neopixelLEDs2.show();
    delay(500);

    neopixelLEDs1.clear();
    neopixelLEDs2.clear();
    for (int i = 0; i < PIXEL_COUNT; i++)
    {
        neopixelLEDs1.setPixelColor(i, neopixelLEDs1.Color(255, 0, 0));
        neopixelLEDs2.setPixelColor(i, neopixelLEDs2.Color(255, 0, 0));
    }
    neopixelLEDs1.show();
    neopixelLEDs2.show();
    delay(500);
}

void testBuzzer(){
    EasyBuzzer.beep(840);    // Frequency in hertz(HZ).
    delay(500);
    EasyBuzzer.stopBeep();
    delay(250);
    EasyBuzzer.beep(840);    // Frequency in hertz(HZ).
    delay(500);
    EasyBuzzer.stopBeep();
    delay(250);
}

void testMotores(){

    Serial.println("front");
    forward(motor1, motor2, 250);
    delay(1000);
    brake(motor1, motor2);

    Serial.println("back");
    back(motor1, motor2, -250);
    delay(1000);
    brake(motor1, motor2);


}