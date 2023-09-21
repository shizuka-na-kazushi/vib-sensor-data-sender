#include "testbutton.h"

TestButton::TestButton(int gpio)
{
  this->gpio = gpio;
  this->state = false;
  this->pressing = false;
}

void TestButton::setup(TheTimer* timer)
{
  pinMode(this->gpio, INPUT_PULLUP);

  timer->setInterval(this, 35);
}

void TestButton::onTimerFired()
{
  int prevState = this->state;
  this->state = (0 < digitalRead(this->gpio)) ? true : false;

  if (this->state && !prevState)
  {
    this->fireOnPressed();
  }
  else if (!this->state && prevState)
  {
    this->fireOnReleased();
  }
}

void TestButton::fireOnPressed()
{
  if (!this->pressing)
  {
    this->pressing = true;
    for (int i = 0; i < this->handlerNumber; i++)
    {
      this->handlers[i]->onPressed();
    }
  }
}

void TestButton::fireOnReleased()
{
  if (this->pressing)
  {
    this->pressing = false;
    for (int i = 0; i < this->handlerNumber; i++)
    {
      this->handlers[i]->onReleased();
    }
  }
}

void TestButton::setHandler(ButtonHandler *handler)
{
  if (this->handlerNumber < TEST_BUTTON_CALLBACK_NUM_MAX)
  {
    this->handlers[this->handlerNumber] = handler;
    this->handlerNumber++;
  }
  else
  {
    Serial.print("setHandler is full. Max handlers are ");
    Serial.println(TEST_BUTTON_CALLBACK_NUM_MAX);
  }
}
