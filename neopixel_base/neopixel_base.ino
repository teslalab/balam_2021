
// Libreria para usar las propiedades de conexión WiFi
#include <WiFi.h>
#include <PubSubClient.h> //Libreria para publicación y recepción de datos.
#include <Wire.h>         //Conexión de dispositivos I2C

#include <WiFiUdp.h>

#include <Adafruit_NeoPixel.h>

//Credenciales para poder conectarnos a la red-WiFi sustituya dentro de las comillas
const char *ssid = "galileo";          // Nombre del SSID
const char *password = ""; // Contraseña

// Credenciales para GALioT
#define USERNAME "aquality"
#define PASSWORD "$Air333"

const char *clientID = "ioht_colorpicker";
const char *user = "aquality";
const char *passwd = "$Air333";

//Nombre del Servidor MQTT
const char *mqtt_server = "galiot.galileo.edu";

// network variables
WiFiClient espClient;
PubSubClient mqtt_client(espClient);

#define PIXEL_PIN_1 13  // Digital IO pin connected to the NeoPixels.
#define PIXEL_PIN_2 15  // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 4 // Number of NeoPixels

Adafruit_NeoPixel neopixelLEDs1(PIXEL_COUNT, PIXEL_PIN_1, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel neopixelLEDs2(PIXEL_COUNT, PIXEL_PIN_2, NEO_GRB + NEO_KHZ800);

//Variables
int red = 0;
int blue = 0;
int green = 0;
char msg_r[50];

void setup()
{
    Serial.begin(115200);

    //Setup para BME680
    Wire.begin(21, 22); // Pines I2C del ESP32
    Serial.println("Conectando a WiFi");
    setupWiFi();
    //Setup para MQTT
    Serial.println("Activando MQTT");
    setupMQTT();
}

void loop()
{
    if (!mqtt_client.connected())
    {
        reconnect();
    }
    mqtt_client.subscribe("/ioht/colorpicker");
    mqtt_client.loop();

    delay(20);
}

void setupWiFi()
{
    //Inicializamos WiFi
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    //Fin de la inicialización WiFi
}

void setupMQTT()
{
    delay(10);
    // Iniciamos la conexion WiFi con la Red que colocamos
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    mqtt_client.setServer(mqtt_server, 1883);
    mqtt_client.setCallback(callback);
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++)
    {
        msg_r[i] = (char)payload[i];
    }
    msg_r[length] = 0;
    Serial.print("'");
    Serial.print(msg_r);
    Serial.println("'");
    colorConverter(msg_r);
}
void reconnect()
{
    // Loop until we're reconnected
    while (!mqtt_client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect

        if (mqtt_client.connect(clientID, user, passwd))
        {
            Serial.println("Client connected in reconnection"); //Testing
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(mqtt_client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void colorConverter(String hexValue)
{
    int number = (int)strtol(&hexValue[0], NULL, 16);
    int r = number >> 16 & 0xFF;
    int g = number >> 8 & 0xFF;
    int b = number & 0xFF;

    Serial.print("red is ");
    Serial.println(r);
    Serial.print("green is ");
    Serial.println(g);
    Serial.print("blue is ");
    Serial.println(b);

    neopixelLEDs1.clear(); // Colocamos todos los pixels en 'off'
    neopixelLEDs2.clear(); // Colocamos todos los pixels en 'off'

    for (int i = 0; i < PIXEL_COUNT; i++)
    {
        neopixelLEDs1.setPixelColor(i, neopixelLEDs1.Color(r, g, b));
        neopixelLEDs2.setPixelColor(i, neopixelLEDs2.Color(r, g, b));
    }
    neopixelLEDs1.show(); // Mandamos el update del color al hardware.
    neopixelLEDs2.show(); // Mandamos el update del color al hardware.
}