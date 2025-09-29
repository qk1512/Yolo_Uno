#include <Arduino.h>
#include "./wifi/wifi_ap.h"
#include "./webUI/webUI.h"
#include <WebServer.h>

// WiFi config
const char *ssid = "ESP32S3_AP";
const char *password = "12345678";

IPAddress local_IP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

// Objects
MyAP myAP(ssid, password, local_IP, gateway, subnet);
WebServer server(80);
WebUI webui(server);

void setup()
{
  Serial.begin(115200);
  myAP.beginAP();
  webui.begin();
}

void loop()
{
  webui.handleClient();
}
