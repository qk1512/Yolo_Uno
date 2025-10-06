/* #include "wifi_ap.h"

MyAP::MyAP(const char *ssid, const char *password,
           IPAddress localIP, IPAddress gateway, IPAddress subnet)
    : _ssid(ssid), _password(password),
      _localIP(localIP), _gateway(gateway), _subnet(subnet) {}

bool MyAP::beginAP()
{
    if (!WiFi.softAPConfig(_localIP, _gateway, _subnet))
    {
        Serial.println("⚠️ AP Config Failed!");
        return false;
    }
    if (WiFi.softAP(_ssid, _password))
    {
        Serial.println("✅ AP Started");
        Serial.print("ESP32S3 IP: ");
        Serial.println(WiFi.softAPIP());
        return true;
    }
    else
    {
        Serial.println("⚠️ Failed to start AP");
        return false;
    }
}

void MyAP::printClients()
{
    int n = WiFi.softAPgetStationNum();
    if (n > 0)
    {
        wifi_sta_list_t wifi_sta_list = {};
        esp_netif_sta_list_t netif_sta_list = {};

        if (esp_wifi_ap_get_sta_list(&wifi_sta_list) == ESP_OK)
        {
            if (esp_netif_get_sta_list(&wifi_sta_list, &netif_sta_list) == ESP_OK)
            {
                for (int i = 0; i < netif_sta_list.num; i++)
                {
                    const esp_netif_sta_info_t &station = netif_sta_list.sta[i];

                    Serial.print("Client ");
                    Serial.print(i + 1);
                    Serial.print(" MAC: ");
                    for (int j = 0; j < 6; j++)
                    {
                        Serial.printf("%02X", station.mac[j]);
                        if (j < 5)
                            Serial.print(":");
                    }

                    Serial.print("  IP: ");
                    IPAddress clientIP(station.ip.addr);
                    Serial.println(clientIP);
                }
            }
            else
            {
                Serial.println("⚠️ esp_netif_get_sta_list failed");
            }
        }
        else
        {
            Serial.println("⚠️ esp_wifi_ap_get_sta_list failed");
        }
    }
    else
    {
        Serial.println("No clients connected.");
    }
}
 */