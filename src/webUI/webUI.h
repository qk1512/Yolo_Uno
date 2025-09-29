#ifndef WEB_UI_H
#define WEB_UI_H

#include <WebServer.h>
#include "esp_wifi.h"
#include "esp_netif.h"

class WebUI
{
public:
    WebUI(WebServer &server);
    void begin();
    void handleClient();

private:
    WebServer &_server;
    String getClientTable();
    void handleRoot();
};

#endif
