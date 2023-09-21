#include "blinkingLed.h"

BlinkingLed::BlinkingLed(int gpio, int interval)
{
  this->gpio = gpio;
  this->interval = interval;
  this->blinking = false;
  this->onOrOff = false;
}

void BlinkingLed::setup(TheTimer *timer)
{
  pinMode(this->gpio, OUTPUT);
  if (timer)
  {
    timer->setInterval(this, this->interval);
  }
  else
  {
    Serial.println("BlinkingLed::setup can not set timer. may be a Bug!");
  }
}

void BlinkingLed::setLight(bool onOrOff)
{
  if (onOrOff == this->blinking) {
    return;
  } 

  this->blinking = onOrOff;
  this->onOrOff = !onOrOff;
  digitalWrite(this->gpio, onOrOff ? HIGH : LOW);
}

void BlinkingLed::onTimerFired()
{
  if (!this->blinking)
  {
    return; /* Nothing to do */
  }
  else if (!this->onOrOff)
  {
    digitalWrite(this->gpio, HIGH);
    this->onOrOff = true;
  }
  else if (this->onOrOff)
  {
    digitalWrite(this->gpio, LOW);
    this->onOrOff = false;
  }
}
