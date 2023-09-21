#include <FirebaseESP32.h>
#include "config.h"
#include "testbutton.h"
#include "blinkingLed.h"
#include "toggleLed.h"
#include "wifihelper.h"
#include "fbhelper.h"
#include "theTimer.h"
#include "vibSensor.h"
#include "vibController.h"
#include "testbuttonController.h"
#include "ntphelper.h"

const int LED_GPIO = 14;

const int LED_INDICATOR_1_GPIO = 13;
const int LED_INDICATOR_2_GPIO = 12;

const int BUTTON_GPIO = 39;
const int VIB_SENSOR_1_GPIO = 36;
const int VIB_SENSOR_2_GPIO = 34;


TheTimer theTimer;

/**
 * Components
*/
VibSensor vibSensor1(VIB_SENSOR_1_GPIO);
VibSensor vibSensor2(VIB_SENSOR_2_GPIO);

ToggleLed indicator1(LED_INDICATOR_1_GPIO, false);
ToggleLed indicator2(LED_INDICATOR_2_GPIO, false);

BlinkingLed blkLed(LED_GPIO, 500);
BlinkingLed quickBlkLed(LED_GPIO, 25);


/**
 * Helpers
*/
WiFiHelper wifiHelper(WIFI_SSID, WIFI_PASS, &blkLed);
FbHelper fbHelper;
NtpHelper ntpHelper;


/** 
 * Controllers
*/
TestButtonController testBtnController(BUTTON_GPIO, &fbHelper, &quickBlkLed);
VibController vibController1(101, &fbHelper, &vibSensor1, &indicator1);
VibController vibController2(102, &fbHelper, &vibSensor2, &indicator2);


void setup()
{
  Serial.begin(115200);
  Serial.println("Hello, world! Welcome to main.ino");

  theTimer.setup();

  Serial.println("[setup] going to setup vibration sensors.");
  vibSensor1.setup(&theTimer);
  vibSensor2.setup(&theTimer);

  Serial.println("[setup] going to setup LED indicators.");
  blkLed.setup(&theTimer);
  quickBlkLed.setup(&theTimer);
  indicator1.setup();
  indicator2.setup();

  Serial.println("[setup] going to setup WiFi helper.");
  wifiHelper.setup(&theTimer);

  Serial.println("[setup] going to setup fbHelper.");
  fbHelper.setup(&theTimer);

  Serial.println("[setup] going to setup controllers.");
  testBtnController.setup(&theTimer);
  vibController1.setup();
  vibController2.setup();

  Serial.println("[setup] going to setup NTP helper.");
  ntpHelper.setup();
}

void loop()
{
  theTimer.loop();
}
