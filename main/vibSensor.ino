#include "vibSensor.h"

/**
 *
 * VibSensorAccumulator implementation
 *
 */

bool VibSensorAccumulator::isAccumulated()
{
  if (this->ticks < VIB_DURATION_TICKS)
  {
    this->accumulatedValue += digitalRead(this->gpio);
    this->ticks++;
    return false;
  }
  else
  {
    this->ticks = 0;
    return true;
  }
}

int VibSensorAccumulator::getAccumulatedValue()
{
  int val = this->accumulatedValue;
  this->accumulatedValue = 0;
  return val;
}

/**
 *
 * VibSensor implementation
 *
 */

void VibSensor::setup(TheTimer *timer)
{
  pinMode(this->gpio, INPUT_PULLUP);

  timer->setInterval(this, VIB_SENSOR_READ_INTERVAL);
}

void VibSensor::setCallback(VibSensorCallback *callback)
{
  if (VIB_CALLBACK_MAX <= this->vibCallbackNum)
  {
    Serial.print("[SENSOR] VibSensor::setCallback() failed, due to reaching max callbacks: ");
    Serial.println(VIB_CALLBACK_MAX);
  }
  else
  {
    this->callbacks[this->vibCallbackNum++] = callback;
  }
}

void VibSensor::onTimerFired()
{
  if (isAccumulated())
  {
    int val = getAccumulatedValue();

    bool newState = (val < VIB_DURATION_TICKS / 3) ? false : true;
    if ((this->state && !newState) || (!this->state && newState))
    {
      notifyStateChange(newState);
    }
    this->state = newState;
  }
}

void VibSensor::notifyStateChange(bool state)
{
  Serial.print("[SENSOR][gpio:");
  Serial.print(this->gpio);
  Serial.print("] notifyStateChange with ");
  Serial.println(state);

  for (int i = 0; i < this->vibCallbackNum; i++)
  {
    this->callbacks[i]->onStateChanged(state);
  }
}

