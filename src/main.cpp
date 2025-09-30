#include <WiFi.h>
#include <PubSubClient.h>
#include "./ledRGB/led_rgb.h"
#include "./mqtt/mqtt.h"
// Thông tin WiFi router
const char *ssid = "QUANG KHANH_2.4G";
const char *password = "15122002";

// IP của PC (chạy Mosquitto broker)
const char *mqtt_server = "192.168.1.143";


void checkSerialBackup()
{
  if (!client.connected() && Serial.available())
  {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd == "Left")
      LedIndexState = 1;
    else if (cmd == "Right")
      LedIndexState = 2;
    else if (cmd == "Forward")
      LedIndexState = 3;
    else if (cmd == "Back")
      LedIndexState = 4;
    else if (cmd == "Stop")
      LedIndexState = 5;
    else if (cmd == "Animation")
      LedIndexState = 6;
    else if (cmd == "Clear")
      LedIndexState = 7;

    Serial.printf("Serial Backup: %s -> State=%d\n", cmd.c_str(), LedIndexState);
  }
}

void UsbSerialTask(void *pv)
{
  // đảm bảo Serial đã sẵn sàng (tùy chọn)
  unsigned long t0 = millis();
  while (!Serial && millis() - t0 < 3000)
  {
    vTaskDelay(pdMS_TO_TICKS(10));
  }

  Serial.println("[USB] UsbSerialTask started");

  String line;
  line.reserve(64);
  for (;;)
  {
    while (Serial.available() > 0)
    {
      int ch = Serial.read();
      if (ch < 0)
        break;

      if (ch == '\n' || ch == '\r')
      {
        if (line.length() > 0)
        {
          String cmd = line;
          cmd.trim();
          if (cmd.length())
          {
            bool ok = setStateFromString(cmd);
            if (ok)
              Serial.printf("[USB] OK: %s\n", cmd.c_str());
            else
              Serial.printf("[USB] Invalid: %s\n", cmd.c_str());
          }
          line = "";
        }
      }
      else
      {
        if (line.length() < 60)
          line += (char)ch;
      }
    }
    vTaskDelay(pdMS_TO_TICKS(5)); // nhường CPU
  }
}

void setup()
{
  Serial.begin(115200);
  initLedRGB();

  mqttInit(ssid, password, mqtt_server, 1883);

  stateMutex = xSemaphoreCreateMutex();
  xTaskCreatePinnedToCore(UsbSerialTask, "UsbSerialTask", 4096, NULL, 2, NULL, 0);
  xTaskCreatePinnedToCore(ledTask, "LED Task", 4096, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(mqttTask, "MQTT Task", 8192, NULL, 2, NULL, 1);
}

void loop()
{
  
}
