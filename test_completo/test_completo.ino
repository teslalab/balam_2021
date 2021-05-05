
#include <Adafruit_NeoPixel.h>
#include <EasyBuzzer.h>
#include <TB6612_ESP32.h>

#define PIXEL_PIN_1 13 // Digital IO pin connected to the NeoPixels.
#define PIXEL_PIN_2 15 // Digital IO pin connected to the NeoPixels.
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

void setup()
{
    Serial.begin(115200);
    Serial.println("Comenzando test");
    EasyBuzzer.setPin(BUZZER_PIN); //Initialize buzzer
    pinMode(BUZZER_PIN, OUTPUT);

    pinMode(TRIGGER_PIN, OUTPUT); // Sets the TRIGGER_PIN as an OUTPUT
    pinMode(ECHO_PIN, INPUT);  // Sets the ECHO_PIN as an INPUT
}

void loop()
{
    testNeoPixel();
    testBuzzer();
    testMotores();
}

void testNeoPixel()
{
    Serial.println("Test de Neopixel...");
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

void testBuzzer()
{
    Serial.println("Test de Buzzer...");
    EasyBuzzer.beep(840); // Frequency in hertz(HZ).
    delay(1000);
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
    while (cont < 400)
    {
        Serial.print("Sensor0: ");
        Serial.println(analogRead(36));
        Serial.print("Sensor1: ");
        Serial.println(analogRead(34));
        Serial.print("Sensor2: ");
        Serial.println(analogRead(39));
        Serial.print("Sensor3: ");
        Serial.println(analogRead(35));

        cont++;
        delay(10);
    }
}

void testUltrasonico()
{
    Serial.println("Test Ultrasonico...");
    int cont = 0;
    while (cont < 400)
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

        cont++;
        delay(10);
    }
}