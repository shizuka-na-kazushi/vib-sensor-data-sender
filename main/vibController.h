#ifndef __VIB_CONTROLLER_H__
#define __VIB_CONTROLLER_H__

#include "fbhelper.h"
#include "toggleLed.h"
#include "vibSensor.h"

#define VIB_SENSOR_BASE_PATH "/sensors"

class VibFbRequest : public FbHelperRequest
{
public:
  bool active = true;
  int sensorId = -1;
  char *basePath = VIB_SENSOR_BASE_PATH;

  virtual void execute(FirebaseData &fbdo);
};

class VibController : public VibSensorCallback
{
protected:
  VibFbRequest activeReq;
  VibFbRequest inactiveReq;

  FbHelper *fb;
  LedIndicator *led;
  VibSensor *vibSensor;

public:
  VibController(int sensorId, FbHelper* fb, VibSensor* vibSensor, LedIndicator* led);

  void setup();

  virtual void onStateChanged(bool vib);
};

#endif // !__VIB_CONTROLLER_H__