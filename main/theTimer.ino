#include "theTimer.h"

/**
 *
 * TheTimerContext implementation
 */

void TheTimerContext::init()
{
  this->millisec = 0;
  this->duration = 0;
  this->cyclic = false;
  this->callback = NULL;
}

void TheTimerContext::setCallback(TheTimerCallback *callback, int duration, bool cyclic)
{
  this->millisec = millis();
  this->duration = duration;
  this->callback = callback;
  this->cyclic = cyclic;
}

void TheTimerContext::checkTimer(int now)
{
  if (!this->callback)
    return;

  if ((this->millisec + this->duration) <= now)
  {
    this->callback->onTimerFired();
    if (this->cyclic)
    {
      this->millisec = millis();
    }
    else
    {
      this->callback = NULL;
    }
  }
}

/***
 *
 * TheTimer implementation
 *
 */

void TheTimer::setup()
{
  this->intervalTimerNum = 0;
  this->timeoutTimerNum = 0;
  for (int i = 0; i < MAX_THE_TIMER_NUMBER; i++)
  {
    this->intervalTimers[i].init();
  }
  for (int i = 0; i < MAX_THE_TIMER_NUMBER; i++)
  {
    this->timeoutTimers[i].init();
  }
}

int TheTimer::setInterval(TheTimerCallback *callback, int millisec)
{
  Serial.print("[TIMER] setInterval address: ");
  Serial.println((int)callback);
  if (MAX_THE_TIMER_NUMBER <= this->intervalTimerNum)
  {
    Serial.print("[TIMER] setInterval is no longer set! maximum number of timer is ");
    Serial.println(MAX_THE_TIMER_NUMBER);
  }
  else
  {
    int ret = this->intervalTimerNum;
    this->intervalTimers[this->intervalTimerNum++].setCallback(callback, millisec, true);
    return ret;
  }
  return -1;
}

int TheTimer::setTimeout(TheTimerCallback *callback, int millisec)
{
  if (MAX_THE_TIMER_NUMBER <= this->timeoutTimerNum)
  {
    Serial.print("[TIMER] setTimer is no longer set! maximum number of timer is ");
    Serial.println(MAX_THE_TIMER_NUMBER);
  }
  else
  {
    int ret = this->timeoutTimerNum;
    this->timeoutTimers[this->timeoutTimerNum++].setCallback(callback, millisec, false);
    return ret;
  }
  return -1;
}

void TheTimer::loop()
{
  for (int i = 0; i < this->intervalTimerNum; i++)
  {
    this->intervalTimers[i].checkTimer(millis());
  }
  for (int i = 0; i < this->timeoutTimerNum; i++)
  {
    this->timeoutTimers[i].checkTimer(millis());
  }
}
