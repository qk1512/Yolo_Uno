#include "WebUI.h"
#include <WiFi.h>
#include "PubSubClient.h"


WebUI::WebUI(WebServer &server) : _server(server) {}

void WebUI::begin()
{
    _server.on("/", [this]()
               { handleRoot(); });
    _server.begin();
    Serial.println("🌐 Web server started, open http://192.168.4.1/");

    _server.on("/setMQTT", [this]()
               {
    if (_server.hasArg("mqtt")) {
        String newServer = _server.arg("mqtt");
        Serial.println("🔄 New MQTT server: " + newServer);

        extern PubSubClient client;

        // 1) Ngắt kết nối cũ
        if (client.connected()) {
            client.disconnect();
            Serial.println("MQTT disconnected from old server");
        }

        // 2) Cập nhật server mới
        client.setServer(newServer.c_str(), 1883);

        // 3) Kết nối lại ngay
        if (client.connect("ESP32S3_Client")) {
            client.subscribe("esp32/led");
            Serial.println("✅ Connected to new MQTT server: " + newServer);
            _server.send(200, "text/html", "<h3>Connected to " + newServer + "</h3><a href='/'>Back</a>");
        } else {
            Serial.println("❌ Failed to connect new server");
            _server.send(200, "text/html", "<h3>Failed to connect " + newServer + "</h3><a href='/'>Back</a>");
        }
    } });
}

void WebUI::handleClient()
{
    _server.handleClient();
}

void WebUI::handleRoot()
{
    _server.send(200, "text/html", getClientTable());
}

String WebUI::getClientTable()
{
    String html = "<!DOCTYPE html><html><head><meta charset='utf-8'>";
    html += "<style>table{border-collapse:collapse;width:60%;margin:auto;} ";
    html += "th,td{border:1px solid #333;padding:8px;text-align:center;} ";
    html += "body{font-family:Arial;text-align:center;} ";
    html += "h2{color:#0066cc;}</style></head><body>";
    html += "<h2>Connected Clients</h2>";
    html += "<table><tr><th>#</th><th>MAC</th><th>IP</th></tr>";

    wifi_sta_list_t wifi_sta_list = {};
    esp_netif_sta_list_t netif_sta_list = {};

    if (esp_wifi_ap_get_sta_list(&wifi_sta_list) == ESP_OK)
    {
        if (esp_netif_get_sta_list(&wifi_sta_list, &netif_sta_list) == ESP_OK)
        {
            for (int i = 0; i < netif_sta_list.num; i++)
            {
                const esp_netif_sta_info_t &station = netif_sta_list.sta[i];

                char macStr[18];
                sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X",
                        station.mac[0], station.mac[1], station.mac[2],
                        station.mac[3], station.mac[4], station.mac[5]);

                IPAddress clientIP(station.ip.addr);

                html += "<tr><td>" + String(i + 1) + "</td><td>" + String(macStr) +
                        "</td><td>" + clientIP.toString() + "</td></tr>";
            }
        }
    }

    html += "</table>";
    html += "<p>Refresh page to update list</p>";
    html += "</body></html>";

    html += "<h2>MQTT Config</h2>";
    html += "<form action='/setMQTT' method='GET'>";
    html += "MQTT Server: <input type='text' name='mqtt' placeholder='IP or hostname'>";
    html += "<input type='submit' value='Save'>";
    html += "</form>";

    return html;
}
