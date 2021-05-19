#include <Wire.h>
#include "Adafruit_SHT31.h"

Adafruit_SHT31 sensor = Adafruit_SHT31();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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
  // put your main code here, to run repeatedly:
  float temp = sensor.readTemperature();
  float hume = sensor.readHumidity();

  //isnan -> is not a number?
  if(isnan(temp)){
    Serial.println("Error al obtener temperatura");
  }else{
    Serial.print("Temperatura *C = ");
    Serial.println(temp);
  }

  //! isnan -> is not not a number? -> is a number?
  if(!isnan(hume)){
    Serial.print("Humedad % = ");
    Serial.println(hume);
  }else{
    Serial.println("Error al obtener humedad");
  }
  Serial.println();
  delay(1000);
  
}