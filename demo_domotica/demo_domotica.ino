#include <Wire.h>
#include "Adafruit_SHT31.h"

Adafruit_SHT31 sensor = Adafruit_SHT31();

#include <Adafruit_NeoPixel.h>

#define PIXEL_COUNT 4
#define PIXEL_PIN_1 15
#define PIXEL_PIN_2 13

Adafruit_NeoPixel neopixel1(PIXEL_COUNT, PIXEL_PIN_1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel neopixel2(PIXEL_COUNT, PIXEL_PIN_2, NEO_GRB + NEO_KHZ800);

#include <TB6612_ESP32.h>

//MOTOR2
#define BIN1 25
#define BIN2 26
#define PWMB 14

const int offsetB = 1;

Motor motor = Motor(BIN1, BIN2, PWMB, offsetB, 0, 5000, 8, 2);

//PIR
int pin_pir = 17;
int val_pir = 0;

#include <EasyBuzzer.h>
int BUZZER_PIN = 27;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    Wire.begin(21, 22); //Pines I2C de nuestro ESP32
    if (sensor.begin(0x44))
    {
        Serial.println("Sensor TL05i encontrado");
    }
    else
    {
        Serial.println("Sensor TL05i NO encontrado");
        while (1)
        {
            delay(10);
        }
    }
    EasyBuzzer.setPin(BUZZER_PIN); //Initialize buzzer
    pinMode(pin_pir, INPUT);
}

void loop()
{
    // put your main code here, to run repeatedly:
    float temp = sensor.readTemperature();
    float hume = sensor.readHumidity();

    //
    val_pir = digitalRead(pin_pir);

    //isnan -> is not a number?
    if (isnan(temp))
    {
        Serial.println("Error al obtener temperatura");
    }
    else
    {
        if (temp > 65)
        {
            forward(motor, motor, 100);
        }
        else
        {
            brake(motor, motor);
        }
        Serial.print("Temperatura *C = ");
        Serial.println(temp);
    }

    //! isnan -> is not not a number? -> is a number?
    if (!isnan(hume))
    {
        Serial.print("Humedad % = ");
        Serial.println(hume);
    }
    else
    {
        Serial.println("Error al obtener humedad");
    }
    Serial.println();
    if (val_pir == HIGH)
    {
        for (int i = 0; i < PIXEL_COUNT; i++)
        {
            neopixel1.setPixelColor(i, neopixel1.Color(0, 0, 25));
            neopixel2.setPixelColor(i, neopixel2.Color(0, 0, 25));
        }
        neopixel1.show();
        neopixel2.show();
        EasyBuzzer.beep(500); // Frequency in hertz(HZ).
    }
    else
    {
        neopixel1.clear();
        neopixel2.clear();
        neopixel1.show();
        neopixel2.show();
        EasyBuzzer.stopBeep();
    }

    delay(1000);
}
