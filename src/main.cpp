#include <WiFi.h>
#include <PubSubClient.h>
#include "./ledRGB/led_rgb.h"
#include "./mqtt/mqtt.h"
#include "./webUI/webUI.h"
// Thông tin WiFi router
const char *ssid = "RD-SEAI_2.4G";
const char *password = "";

// IP của PC (chạy Mosquitto broker)
const char *mqtt_server = "172.28.182.236";

WebServer server(80);
WebUI webui(server);

void ledTask(void *pvParameters)
{
  while (1)
  {
    if (runLeft)
    {
      turnLeft();
      turnOffLedRGB();
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    else if (runStop)
    {
      // gọi hiệu ứng Right ở đây
      // turnRight();
      turnOffLedRGB();
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }
  }
}

void webTask(void *pvParameters)
{
  while (1)
  {
    webui.handleClient();
    vTaskDelay(10 / portTICK_PERIOD_MS); // tránh chiếm CPU 100%
  }
}

void setup()
{
  Serial.begin(115200);
  initLedRGB();

  mqttInit(ssid, password, mqtt_server, 1883);
  webui.begin();


  xTaskCreatePinnedToCore(ledTask, "LED Task", 4096, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(webTask, "Web Task", 8192, NULL, 1, NULL, 1);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop(); // giữ kết nối, nhận tin nhắn
}


