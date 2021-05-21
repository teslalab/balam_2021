
#include <Adafruit_NeoPixel.h>

#define PIXEL_COUNT 4
#define PIXEL_PIN_1 15
#define PIXEL_PIN_2 13

Adafruit_NeoPixel neopixel1(PIXEL_COUNT, PIXEL_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel neopixel2(PIXEL_COUNT, PIXEL_PIN_2, NEO_GRB + NEO_KHZ800);

#include <TB6612_ESP32.h>

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

const int velocidad = 50;
const int giro = 100;

#define TRIGGER_PIN 17
#define ECHO_PIN 16
long duration;
int distance;

void setup()
{
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    Serial.begin(115200);
}
void loop()
{

    int s0 = analogRead(36);
    int s1 = analogRead(34);
    int s2 = analogRead(39);
    int s3 = analogRead(35);

    (s0 < 1500) ? s0 = 1 : s0 = 0;
    (s1 < 1500) ? s1 = 1 : s1 = 0;
    (s2 < 1500) ? s2 = 1 : s2 = 0;
    (s3 < 1500) ? s3 = 1 : s3 = 0;

    if (s0 == 1 || s1 == 1 || s2 == 1 || s3 == 1)
    {
        forward(motor1, motor2, velocidad);
    }
    else
    {
        brake(motor1, motor2);
    }

    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration * 0.034 / 2;

    if (distance < 8)
    {
        for (int i = 0; i < PIXEL_COUNT; i++)
        {
            neopixel1.setPixelColor(i, neopixel1.Color(0, 0, 25));
            neopixel2.setPixelColor(i, neopixel2.Color(0, 0, 25));
        }
        neopixel1.show();
        neopixel2.show();

        back(motor1, motor2, velocidad);
        delay(100);
        forward(motor2, motor2, velocidad);
        delay(100);
    }
    else
    {
        neopixel1.clear();
        neopixel2.clear();
        neopixel1.show();
        neopixel2.show();
    }
    

    delay(50);
}