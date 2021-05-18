
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

void setup()
{
    Serial.begin(115200);
}

void loop()
{

    int s0 = analogRead(36);
    int s1 = analogRead(34);
    int s2 = analogRead(39);
    int s3 = analogRead(35);

    // Serial.print("Sensor0: ");
    // Serial.println(s0);
    // Serial.print("Sensor1: ");
    // Serial.println(s1);
    // Serial.print("Sensor2: ");
    // Serial.println(s2);
    // Serial.print("Sensor3: ");
    // Serial.println(s3);

    (s0 < 1500) ? s0 = 1 : s0 = 0;
    (s1 < 1500) ? s1 = 1 : s1 = 0;
    (s2 < 1500) ? s2 = 1 : s2 = 0;
    (s3 < 1500) ? s3 = 1 : s3 = 0;
    

    Serial.print(s3);
    Serial.print(s2);
    Serial.print(s1);
    Serial.println(s0);
    
    if (s0 == 0)
    {
        forward(motor2, motor2, giro);
    }
    else if (s3 == 0)
    {
        forward(motor1, motor1, giro);
    }else{

        forward(motor1, motor2, velocidad);
    }
    

    delay(50);
}