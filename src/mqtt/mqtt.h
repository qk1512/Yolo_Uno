#ifndef MQTT_H
#define MQTT_H

#include <WiFi.h>
#include <PubSubClient.h>
#include "mdns.h"

// Các biến toàn cục
extern WiFiClient espClient;
extern PubSubClient client;

extern volatile bool runLeft;
extern volatile bool runStop;

// Hàm
void mqttInit(const char *ssid, const char *password, const char *server, int port);
void callback(char *topic, byte *payload, unsigned int length);
void reconnect();

#endif
