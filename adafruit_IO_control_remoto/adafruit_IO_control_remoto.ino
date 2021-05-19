#include "AdafruitIO_WiFi.h"
#include <Wire.h>
#include <TB6612_ESP32.h>

#define IO_USERNAME  "##"
#define IO_KEY       "##"

#define WIFI_SSID       "##"
#define WIFI_PASS       "##"


AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);


AdafruitIO_Feed *adelante = io.feed("forward");
AdafruitIO_Feed *atras = io.feed("back");
AdafruitIO_Feed *izquierda = io.feed("left");
AdafruitIO_Feed *derecha = io.feed("right");


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

void setup() {

  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

  adelante->onMessage(handleForward);
  atras->onMessage(handleBack);
  izquierda->onMessage(handleLeft);
  derecha->onMessage(handleRight);
}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();


}

void handleForward(AdafruitIO_Data *data) {
  int x = data->toInt();
  Serial.print("Adelante: ");
  Serial.println(x);
  (x != 0) ? forward(motor1, motor2, 150) : brake(motor1, motor2);
}
void handleBack(AdafruitIO_Data *data) {
  int x = data->toInt();
  Serial.print("Atras: ");
  Serial.println(x);
  (x != 0) ? back(motor1, motor2, 150) : brake(motor1, motor2);
}
void handleLeft(AdafruitIO_Data *data) {
  int x = data->toInt();
  Serial.print("Izquierda: ");
  Serial.println(x);
  (x != 0) ? forward(motor1, motor1, 150) : brake(motor1, motor2);
}
void handleRight(AdafruitIO_Data *data) {
  int x = data->toInt();
  Serial.print("Derecha: ");
  Serial.println(x);
  (x != 0) ? forward(motor2, motor2, 150) : brake(motor1, motor2);
}
 
