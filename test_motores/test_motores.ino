
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

void setup()
{
}

void loop()
{
  forward(motor1, motor2, 100);
  delay(1000);
  brake(motor1, motor2);
  
  back(motor1, motor2, 100);
  delay(1000);
  brake(motor1, motor2);
}