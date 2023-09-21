#include "toggleLed.h"

ToggleLed::ToggleLed(int gpio, bool enable)
{
  this->gpio = gpio;
  this->enable = enable;
}

void ToggleLed::setup()
{
  pinMode(this->gpio, OUTPUT);
  if (this->enable) {
    digitalWrite(this->gpio, HIGH);
  } else {
    digitalWrite(this->gpio, LOW);
  }
}

void ToggleLed::setLight(bool onOrOff)
{
  if (onOrOff && !this->enable) {
    this->enable = true;
    digitalWrite(this->gpio, HIGH);
  } else if (!onOrOff && this->enable) {
    this->enable = false;
    digitalWrite(this->gpio, LOW);
  }
}
