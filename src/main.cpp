/* #include <Arduino.h>
#include "./wifi/wifi_ap.h"
#include "./webUI/webUI.h"
#include "./ledRGB/led_rgb.h"
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

QueueHandle_t commandQueue;

void ledTask(void *pvParameters)
{
  char buffer[10];
  while (1)
  {
    // Chờ lệnh mới
    if (xQueueReceive(commandQueue, buffer, portMAX_DELAY) == pdPASS)
    {
      if (strcmp(buffer, "Left") == 0)
      {
        runTurn("Left");
      }
      else if (strcmp(buffer, "Right") == 0)
      {
        runTurn("Right");
      }
      else
      {
        Serial.printf("⚠️ Unknown command: %s\n", buffer);
      }
    }
  }
}

void mqttTask(void *pvParameters)
{
  while (1)
  {
    if (Serial.available())
    {
      String cmd = Serial.readStringUntil('\n');
      cmd.trim();

      char buffer[10];
      cmd.toCharArray(buffer, sizeof(buffer));

      // Gửi lệnh vào queue
      if (xQueueSend(commandQueue, buffer, portMAX_DELAY) != pdPASS)
      {
        Serial.println("⚠️ Queue full, command dropped!");
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void setup()
{ 
  Serial.begin(115200);
  //myAP.beginAP();
  //webui.begin();
  initLedRGB();
  commandQueue = xQueueCreate(5, sizeof(char[10]));

  // Task MQTT (giả lập lệnh từ Serial cho dễ test)
  xTaskCreatePinnedToCore(mqttTask, "MQTT Task", 4096, NULL, 1, NULL, 1);

  // Task LED
  xTaskCreatePinnedToCore(ledTask, "LED Task", 4096, NULL, 1, NULL, 0);
  //turnOnLedRGB(3);
}

void loop()
{
  //webui.handleClient();
  
}
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include "./ledRGB/led_rgb.h"

    // Thông tin WiFi router
    const char *ssid = "QUANG KHANH_2.4G";
const char *password = "15122002";

// IP của PC (chạy Mosquitto broker)
const char *mqtt_server = "192.168.1.6";

WiFiClient espClient;
PubSubClient client(espClient);

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
    // chạy hiệu ứng quay trái
    runTurn("Left");
  }
  else if (msg == "Right")
  {
    // chạy hiệu ứng quay phải
    runTurn("Right");
  }
  else if (msg == "Off")
  {
    turnOffLedRGB();
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

void setup()
{
  Serial.begin(115200);
  initLedRGB();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");


  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop(); // giữ kết nối, nhận tin nhắn
}
