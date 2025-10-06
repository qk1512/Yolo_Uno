#include "mqtt.h"

WiFiClient espClient;
PubSubClient client(espClient);

volatile int LedIndexState = 0;


void mqttInit(const char *ssid, const char *password, const char *server, int port)
{
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected!");
    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());

    client.setServer(server, port);
    client.setCallback(callback);
}

/* void callback(char *topic, byte *payload, unsigned int length)
{
    String msg;
    for (unsigned int i = 0; i < length; i++)
    {
        msg += (char)payload[i];
    }
    msg.trim();
    Serial.print("MQTT Received: ");
    Serial.println(msg);

    if (msg == "Left")
    {
        LedIndexState = 1;
    }
    else if (msg == "Right")
    {   
      
        LedIndexState = 2;
    }
    else if (msg == "Forward")
    {
        
        LedIndexState = 3;
    }
    else if (msg == "Back")
    {

        LedIndexState = 4;
    }
    else if (msg == "Stop")
    {

        LedIndexState = 5;
    }
    else if(msg == "Clear")
    {
        LedIndexState = 7;
    }
    else if(msg == "Animation")
    {
        LedIndexState = 6;
    }
} */

SemaphoreHandle_t stateMutex = nullptr;

static inline void setStateThreadSafe(int v)
{
    if (stateMutex && xSemaphoreTake(stateMutex, pdMS_TO_TICKS(5)) == pdTRUE)
    {
        LedIndexState = v;
        xSemaphoreGive(stateMutex);
    }
    else
    {
        LedIndexState = v; // fallback
    }
}

bool setStateFromString(const String &cmd)
{
    if (cmd.equalsIgnoreCase("Left"))
    {
        setStateThreadSafe(1);
        return true;
    }
    else if (cmd.equalsIgnoreCase("Right"))
    {
        setStateThreadSafe(2);
        return true;
    }
    else if (cmd.equalsIgnoreCase("Forward"))
    {
        setStateThreadSafe(3);
        return true;
    }
    else if (cmd.equalsIgnoreCase("Backward"))
    {
        setStateThreadSafe(4);
        return true;
    }
    else if (cmd.equalsIgnoreCase("Stop"))
    {
        setStateThreadSafe(5);
        return true;
    }
    else if (cmd.equalsIgnoreCase("Animation") || cmd.equalsIgnoreCase("RotateLeft") || cmd.equalsIgnoreCase("RotateRight"))
    {
        setStateThreadSafe(6);
        return true;
    }
    else if (cmd.equalsIgnoreCase("Clear"))
    {
        setStateThreadSafe(7);
        return true;
    }
    return false;
}
void callback(char *topic, byte *payload, unsigned int length)
{
    String msg;
    msg.reserve(length);
    for (unsigned int i = 0; i < length; ++i)
        msg += (char)payload[i];
    msg.trim();
    Serial.printf("[MQTT] %s\n", msg.c_str());
    (void)setStateFromString(msg); // bỏ qua invalid
}
void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Connecting to MQTT...");
        if (client.connect("ESP32S3_Client"))
        {
            Serial.println("connected!");
            client.subscribe("esp32/led");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            delay(2000);
        }
    }
}

void mqttTask(void *pvParameters)
{
    for (;;)
    {
        if (!client.connected())
        {
            reconnect();
        }
        client.loop();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
}