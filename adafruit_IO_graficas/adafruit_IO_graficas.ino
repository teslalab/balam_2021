#include "AdafruitIO_WiFi.h"
#include <Wire.h>
#include <TB6612_ESP32.h>

#define IO_USERNAME  "##"
#define IO_KEY       "##"

#define WIFI_SSID       "##"
#define WIFI_PASS       "##"

#include "Adafruit_SHT31.h"
 
Adafruit_SHT31 sensor = Adafruit_SHT31();
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);


AdafruitIO_Feed *tempIO = io.feed("temp");
AdafruitIO_Feed *humeIO = io.feed("hume");


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


  if(sensor.begin(0x44)){
    Serial.println("Sensor encontrado");
  }else{
    Serial.println("Sensor NO encontrado");
    while(1){
      delay(10);
    }
  }
}

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  
  float temp = sensor.readTemperature();
  float hume = sensor.readHumidity();

  //isnan -> is not a number?
  if(isnan(temp)){
    Serial.println("Error al obtener temperatura");
  }else{
    Serial.print("Temperatura *C = ");
    Serial.println(temp);
    tempIO->save(temp);
  }

  //! isnan -> is not not a number? -> is a number?
  if(!isnan(hume)){
    Serial.print("Humedad % = ");
    Serial.println(hume);
    humeIO->save(hume);
  }else{
    Serial.println("Error al obtener humedad");
  }
  Serial.println();
  delay(1000);
}
 
