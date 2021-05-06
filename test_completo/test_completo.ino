
#include <Adafruit_NeoPixel.h>
#include <EasyBuzzer.h>
#include <TB6612_ESP32.h>
#include "Adafruit_SHT31.h"

#define PIXEL_PIN_1 15 // Digital IO pin connected to the NeoPixels.
#define PIXEL_PIN_2 13 // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 4  // Number of NeoPixels

//BUZZER
#define BUZZER_PIN 27

//ULTRASONICO
#define TRIGGER_PIN 17
#define ECHO_PIN 16
long duration; // variable for the duration of sound wave travel
int distance;  // variable for the distance measurement

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

Adafruit_SHT31 sht31 = Adafruit_SHT31();

void setup()
{
    Serial.begin(115200);
    Serial.println("Comenzando test");
    EasyBuzzer.setPin(BUZZER_PIN); //Initialize buzzer
    pinMode(BUZZER_PIN, OUTPUT);

    pinMode(TRIGGER_PIN, OUTPUT); // Sets the TRIGGER_PIN as an OUTPUT
    pinMode(ECHO_PIN, INPUT);     // Sets the ECHO_PIN as an INPUT

    Serial.begin(115200);
    if (!sht31.begin(0x44))
    {
        Serial.println("Couldn't find SHT31");
        while (1)
            delay(1);
    }
}

void loop()
{
    //Testing neopixels
    testNeoPixel();
    neopixelLEDs1.clear();
    neopixelLEDs1.show();
    delay(250);

    //Testing buzzer
    neopixelLEDs1.setPixelColor(0, neopixelLEDs1.Color(64, 0, 64));
    neopixelLEDs1.show();
    testBuzzer();
    neopixelLEDs1.clear();
    neopixelLEDs1.show();

    //Testing motors
    neopixelLEDs1.setPixelColor(1, neopixelLEDs1.Color(64, 0, 64));
    neopixelLEDs1.show();
    testMotores();
    neopixelLEDs1.clear();

    //Testing CNYs
    neopixelLEDs1.setPixelColor(2, neopixelLEDs1.Color(64, 0, 64));
    neopixelLEDs1.show();
    testCNY();
    neopixelLEDs1.clear();

    //Testing Ultrasonic
    neopixelLEDs1.setPixelColor(3, neopixelLEDs1.Color(64, 0, 64));
    neopixelLEDs1.show();
    testUltrasonico();
    neopixelLEDs1.clear();

    //Testing Ultrasonic
    neopixelLEDs1.setPixelColor(0, neopixelLEDs1.Color(64, 0, 64));
    neopixelLEDs1.setPixelColor(1, neopixelLEDs1.Color(64, 0, 64));
    neopixelLEDs1.setPixelColor(2, neopixelLEDs1.Color(64, 0, 64));
    neopixelLEDs1.setPixelColor(3, neopixelLEDs1.Color(64, 0, 64));
    neopixelLEDs1.show();
    testSHT31();
    neopixelLEDs1.clear();
}

void testNeoPixel()
{
    Serial.println("Test de Neopixel...");
    neopixelLEDs1.clear();
    neopixelLEDs2.clear();
    for (int i = 0; i < PIXEL_COUNT; i++)
    {
        neopixelLEDs1.setPixelColor(i, neopixelLEDs1.Color(0, 0, 50));
        neopixelLEDs2.setPixelColor(i, neopixelLEDs2.Color(0, 0, 50));
    }
    neopixelLEDs1.show();
    neopixelLEDs2.show();
    delay(500);

    neopixelLEDs1.clear();
    neopixelLEDs2.clear();
    for (int i = 0; i < PIXEL_COUNT; i++)
    {
        neopixelLEDs1.setPixelColor(i, neopixelLEDs1.Color(0, 50, 0));
        neopixelLEDs2.setPixelColor(i, neopixelLEDs2.Color(0, 50, 0));
    }
    neopixelLEDs1.show();
    neopixelLEDs2.show();
    delay(500);

    neopixelLEDs1.clear();
    neopixelLEDs2.clear();
    for (int i = 0; i < PIXEL_COUNT; i++)
    {
        neopixelLEDs1.setPixelColor(i, neopixelLEDs1.Color(50, 0, 0));
        neopixelLEDs2.setPixelColor(i, neopixelLEDs2.Color(50, 0, 0));
    }
    neopixelLEDs1.show();
    neopixelLEDs2.show();
    delay(500);
    neopixelLEDs1.clear();
    neopixelLEDs2.clear();
    neopixelLEDs1.show();
    neopixelLEDs2.show();
}

void testBuzzer()
{
    Serial.println("Test de Buzzer...");
    EasyBuzzer.beep(500); // Frequency in hertz(HZ).
    delay(500);
    EasyBuzzer.stopBeep();
}

void testMotores()
{
    Serial.println("Test de Motores...");
    Serial.println("front");
    forward(motor1, motor2, 250);
    delay(1000);
    brake(motor1, motor2);

    Serial.println("back");
    back(motor1, motor2, -250);
    delay(1000);
    brake(motor1, motor2);
}

void testCNY()
{
    Serial.println("Test CNY...");
    int cont = 0;
    int sensor0 = 0;
    int sensor1 = 0;
    int sensor2 = 0;
    int sensor3 = 0;

    while (cont < 800)
    {
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

        if (sensor0 < 1000)
        {
            neopixelLEDs2.setPixelColor(0, neopixelLEDs2.Color(64, 64, 0));
            neopixelLEDs2.show();
        }
        if (sensor1 < 1000)
        {
            neopixelLEDs2.setPixelColor(1, neopixelLEDs2.Color(64, 64, 0));
            neopixelLEDs2.show();
        }
        if (sensor2 < 1000)
        {
            neopixelLEDs2.setPixelColor(2, neopixelLEDs2.Color(64, 64, 0));
            neopixelLEDs2.show();
        }
        if (sensor3 < 1000)
        {
            neopixelLEDs2.setPixelColor(3, neopixelLEDs2.Color(64, 64, 0));
            neopixelLEDs2.show();
        }

        neopixelLEDs2.clear();
        neopixelLEDs2.show();
        cont++;
        delay(10);
    }
}

void testUltrasonico()
{
    Serial.println("Test Ultrasonico...");
    int cont = 0;
    while (cont < 200)
    {
        // Clears the TRIGGER_PIN condition
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

        int beep = map(distance, 2, 400, 100, 800);
        EasyBuzzer.beep(beep);
        delay(20);
        cont++;
    }
    EasyBuzzer.stopBeep();
}

void testSHT31()
{
    //para temperatura enciende color rojo
    //para humedad enciende color azul
    float t = sht31.readTemperature();
    float h = sht31.readHumidity();

    float t_map = 0;
    float h_map = 0;

    int cont = 0;

    neopixelLEDs2.clear();
    neopixelLEDs2.show();

    while (cont < 400)
    {
        if (!isnan(t))
        {
            t_map = map(t, 10, 40, 20, 100);
            Serial.print("Temp *C = ");
            Serial.println(t);
            neopixelLEDs2.clear();
            for (int i = 0; i < PIXEL_COUNT; i++)
            {
                neopixelLEDs2.setPixelColor(i, neopixelLEDs2.Color(t_map, 0, 0));
            }
            neopixelLEDs2.show();
            neopixelLEDs2.clear();
            neopixelLEDs2.show();
        }
        else
        {
            Serial.println("Failed to read temperature");
        }
        cont++;
        delay(10);
    }

    neopixelLEDs2.clear();
    neopixelLEDs2.show();
    cont = 0;

    while (cont < 400)
    {
        if (!isnan(h))
        {
            h_map = map(h, 10, 40, 20, 100);
            Serial.print("Hum. % = ");
            Serial.println(h);
            neopixelLEDs2.clear();
            for (int i = 0; i < PIXEL_COUNT; i++)
            {
                neopixelLEDs2.setPixelColor(i, neopixelLEDs2.Color(0, 0, h_map));
            }
            neopixelLEDs2.show();
            neopixelLEDs2.clear();
            neopixelLEDs2.show();
        }
        else
        {
            Serial.println("Failed to read humidity");
        }
        cont++;
    }
}