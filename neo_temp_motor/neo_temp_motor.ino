
#include <Adafruit_NeoPixel.h>
#include <TB6612_ESP32.h>
#include "Adafruit_SHT31.h"
#include <EasyBuzzer.h>

#define PIXEL_PIN_1 15 // Digital IO pin connected to the NeoPixels.
#define PIXEL_PIN_2 13 // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 4  // Number of NeoPixels
//BUZZER
#define BUZZER_PIN 27

//MOTOR1
#define AIN1 32
#define AIN2 33
#define PWMA 12

//MOTOR2
#define BIN1 25
#define BIN2 26
#define PWMB 14

//ULTRASONICO
#define TRIGGER_PIN 17
#define ECHO_PIN 16
long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement

const int offsetA = 1;
const int offsetB = -1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, 0, 5000, 8, 1);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, 0, 5000, 8, 2);
Adafruit_NeoPixel neopixelLEDs1(PIXEL_COUNT, PIXEL_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel neopixelLEDs2(PIXEL_COUNT, PIXEL_PIN_2, NEO_GRB + NEO_KHZ800);

Adafruit_SHT31 sht31 = Adafruit_SHT31();

void setup()
{
    Serial.begin(115200);
    Serial.println("Comenzando test");

    EasyBuzzer.setPin(BUZZER_PIN); //Initialize buzzer
    pinMode(BUZZER_PIN, OUTPUT);

    if (!sht31.begin(0x44))
    {
        Serial.println("Couldn't find SHT31");
    }
    pinMode(TRIGGER_PIN, OUTPUT); // Sets the TRIGGER_PIN as an OUTPUT
    pinMode(ECHO_PIN, INPUT);     // Sets the ECHO_PIN as an INPUT


    // Serial.println("Test de Buzzer...");
    // EasyBuzzer.beep(500); // Frequency in hertz(HZ).
    // delay(250);
    // EasyBuzzer.stopBeep();
    // delay(250);
}

void loop()
{

    float t = sht31.readTemperature();
    float h = sht31.readHumidity();

    if (!isnan(t))
    {
        Serial.print("Temp *C = ");
        Serial.println(t);
    }
    else
    {
        Serial.println("Failed to read temperature");
    }

    if (!isnan(h))
    {
        Serial.print("Hum. % = ");
        Serial.println(h);
    }
    else
    {
        Serial.println("Failed to read humidity");
    }
    Serial.println();
    if (t < 15)
    {
        brake(motor1, motor2);
    }
    else
    {
        Serial.println("Test de Motores...");
        Serial.println("front");
        forward(motor1, motor2, 250);
        delay(100);
    } // Clears the TRIGGER_PIN condition
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    // Sets the TRIGGER_PIN HIGH (ACTIVE) for 10 microseconds
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
    // Reads the ECHO_PIN, returns the sound wave travel time in microseconds
    duration = pulseIn(ECHO_PIN, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // Displays the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    int sensor0 = 0;
    int sensor1 = 0;
    int sensor2 = 0;
    int sensor3 = 0;

    sensor0 = analogRead(36);
    Serial.print("Sensor0: ");
    Serial.println(sensor0);

    sensor1 = analogRead(34);
    Serial.print("Sensor1: ");
    Serial.println(sensor1);

    sensor2 = analogRead(39);
    Serial.print("Sensor2: ");
    Serial.println(sensor2);

    sensor3 = analogRead(35);
    Serial.print("Sensor3: ");
    Serial.println(sensor3);

    if (sensor0 < 1000 && sensor1 < 1000 && sensor2 < 1000 && sensor3 < 1000)
    {
        neopixelLEDs2.clear();
        neopixelLEDs1.clear();
        for (int i = 0; i < PIXEL_COUNT; i++)
        {
            neopixelLEDs1.setPixelColor(i, neopixelLEDs1.Color(0, 0, 50));
            neopixelLEDs2.setPixelColor(i, neopixelLEDs2.Color(0, 0, 50));
        }
        neopixelLEDs1.show();
        neopixelLEDs2.show();
        delay(1000);
    }
    if (distance < 5)
    {
        neopixelLEDs2.clear();
        neopixelLEDs1.clear();
        for (int i = 0; i < PIXEL_COUNT; i++)
        {
            neopixelLEDs1.setPixelColor(i, neopixelLEDs1.Color(0, 50, 50));
            neopixelLEDs2.setPixelColor(i, neopixelLEDs2.Color(0, 50, 50));
        }
        neopixelLEDs1.show();
        neopixelLEDs2.show();
    }else if(distance < 20){
        neopixelLEDs2.clear();
        neopixelLEDs1.clear();
        for (int i = 0; i < PIXEL_COUNT; i++)
        {
            neopixelLEDs1.setPixelColor(i, neopixelLEDs1.Color(100, 50, 50));
            neopixelLEDs2.setPixelColor(i, neopixelLEDs2.Color(100, 50, 50));
        }
        neopixelLEDs1.show();
        neopixelLEDs2.show();
        
    }

    // Serial.println("Test de Buzzer...");
    // EasyBuzzer.beep(500); // Frequency in hertz(HZ).
    // delay(250);
    // EasyBuzzer.stopBeep();
    // delay(250);
}
