#include "mqtt.h"

WiFiClient espClient;
PubSubClient client(espClient);

volatile bool runLeft = false;
volatile bool runStop = false;

IPAddress resolveHost(const char *hostname)
{
    esp_ip4_addr_t addr;
    if (mdns_query_a(hostname, 2000, &addr) == ESP_OK)
    {
        return IPAddress(addr.addr);
    }
    return IPAddress(0, 0, 0, 0);
}

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

void callback(char *topic, byte *payload, unsigned int length)
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
        runLeft = true;
        runStop = false;
    }
    else if (msg == "Stop")
    {
        runLeft = false;
        runStop = true;
    }
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
