void setup()
{
    Serial.begin(115200);
    Serial.println("Comenzando test");
}

void loop()
{
    Serial.print("Sensor0: ");
    Serial.println(analogRead(36));
    Serial.print("Sensor1: ");
    Serial.println(analogRead(34));
    Serial.print("Sensor2: ");
    Serial.println(analogRead(39));
    Serial.print("Sensor3: ");
    Serial.println(analogRead(35));

    delay(10);
}