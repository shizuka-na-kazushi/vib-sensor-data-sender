
#include "wifihelper.h"

/**
 * WiFiHelper implementation
 * */

WiFiHelper::WiFiHelper(const char *ssid, const char *pass, LedIndicator *led)
{
  this->ssid = ssid;
  this->pass = pass;
  this->connected = false;
  this->led = led;
}

void WiFiHelper::setup(TheTimer *timer)
{
  int n = WiFi.scanNetworks();
  WiFi.mode(WIFI_STA);
  WiFi.begin(this->ssid, this->pass);

  if (this->led)
  {
    this->led->setLight(false);
  }

  while (true)
  {
    switch (WiFi.status())
    {
    case WL_NO_SSID_AVAIL:
      Serial.println("[WiFi] SSID not found");
      break;
    case WL_CONNECT_FAILED:
      Serial.print("[WiFi] Failed - WiFi not connected! Reason: ");
      return;
      break;
    case WL_CONNECTION_LOST:
      Serial.println("[WiFi] Connection was lost");
      break;
    case WL_SCAN_COMPLETED:
      Serial.println("[WiFi] Scan is completed");
      break;
    case WL_DISCONNECTED:
      Serial.println("[WiFi] WiFi is disconnected");
      break;
    case WL_CONNECTED:
      Serial.println("[WiFi] WiFi is connected!");
      Serial.print("[WiFi] IP address: ");
      Serial.println(WiFi.localIP());
      this->connected = true;
      if (this->led)
      {
        this->led->setLight(true);
      }
      if (!timer)
      {
        Serial.println("[Error] WiFi helper need theTimer object. it's not available.");
      }
      else
      {
        timer->setInterval(this, 500);
      }
      return;
      break;
    default:
      Serial.print("[WiFi] WiFi Status: ");
      Serial.println(WiFi.status());
      break;
    }

    delay(200);
  }
}

bool WiFiHelper::isConnected()
{
  return this->connected;
}

void WiFiHelper::onTimerFired()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    this->connected = true;
    if (this->led)
    {
      this->led->setLight(true);
    }
  }
  else
  {
    this->connected = false;
    Serial.print("[WiFi] WiFi is disconnected. status: ");
    Serial.println(WiFi.status());
    if (this->led)
    {
      this->led->setLight(false);
    }
  }
}
