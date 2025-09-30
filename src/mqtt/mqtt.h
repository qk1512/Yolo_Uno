#ifndef MQTT_H
#define MQTT_H

#include <WiFi.h>
#include <PubSubClient.h>
#include "mdns.h"
#include "global.h"

// Các biến toàn cục
extern WiFiClient espClient;
extern PubSubClient client;

// Hàm
void mqttInit(const char *ssid, const char *password, const char *server, int port);
void callback(char *topic, byte *payload, unsigned int length);
void reconnect();
void mqttTask(void *pvParameters);

extern bool setStateFromString(const String &cmd);


#endif
