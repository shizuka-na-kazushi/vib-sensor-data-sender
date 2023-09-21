#ifndef WIFI_HELPER
#define WIFI_HELPER
#include <WiFi.h>

#include "theTimer.h"
#include "toggleLed.h"

class WiFiHelper : public TheTimerCallback
{
protected:
  const char *ssid;
  const char *pass;
  bool connected;
  IPAddress ipaddr;
  LedIndicator *led;

public:
  WiFiHelper(const char *ssid, const char *pass, LedIndicator* led);

  bool isConnected();

  void setup(TheTimer *timer);
  virtual void onTimerFired();
};

#endif // !WIFI_HELPER
