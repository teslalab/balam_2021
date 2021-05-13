void setup()
{
    Serial.begin(115200);
    Serial.println("Comenzando test");
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
    

    delay(10);
}