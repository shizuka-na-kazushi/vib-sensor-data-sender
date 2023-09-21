#ifndef VIB_SENSOR
#define VIB_SENSOR

#define VIB_DURATION_TICKS (30)
#define VIB_CALLBACK_MAX (4)

#define VIB_SENSOR_READ_INTERVAL  (100) // in millisec

#include "theTimer.h"

class VibSensorCallback
{
public:
  virtual void onStateChanged(bool vib) = 0;
};

class VibSensorAccumulator
{
protected:
  int gpio;
  int accumulatedValue;
  int ticks;

  VibSensorAccumulator(int gpio) : gpio(gpio), accumulatedValue(0), ticks(0) {}

  bool isAccumulated();
  int getAccumulatedValue();
};

class VibSensor : public VibSensorAccumulator, public TheTimerCallback
{
protected:
  bool state; // if state is true, vibrating. otherwise silence...
  VibSensorCallback *callbacks[VIB_CALLBACK_MAX];
  int vibCallbackNum = 0;

public:
  VibSensor(int gpio) : VibSensorAccumulator(gpio) {}

  void setup(TheTimer *timer);
  void setCallback(VibSensorCallback *callback);
  virtual void onTimerFired();

private:
  void notifyStateChange(bool state);
};

#endif // !VIB_SENSOR
