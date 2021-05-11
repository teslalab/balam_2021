
#include <EasyBuzzer.h>
int BUZZER_PIN = 27;

void setup()
{

    Serial.begin(115200);
    EasyBuzzer.setPin(BUZZER_PIN); //Initialize buzzer
}

void loop()
{
    //freq max 10k

    EasyBuzzer.beep(500); // Frequency in hertz(HZ).
    delay(500);
    EasyBuzzer.beep(1500); // Frequency in hertz(HZ).
    delay(500);
    EasyBuzzer.beep(200); // Frequency in hertz(HZ).
    delay(500);
    EasyBuzzer.stopBeep();
    delay(500);
}