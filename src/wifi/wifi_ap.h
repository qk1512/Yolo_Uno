#ifndef MY_AP_H
#define MY_AP_H

#include <WiFi.h>
#include "esp_wifi.h"
#include "esp_netif.h"

class MyAP
{
public:
    MyAP(const char *ssid, const char *password,
         IPAddress localIP, IPAddress gateway, IPAddress subnet);

    bool beginAP();
    void printClients();

private:
    const char *_ssid;
    const char *_password;
    IPAddress _localIP;
    IPAddress _gateway;
    IPAddress _subnet;
};

#endif
