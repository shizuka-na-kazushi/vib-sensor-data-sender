#ifndef TEST_BUTTON
#define TEST_BUTTON

#define TEST_BUTTON_CALLBACK_NUM_MAX (5)
#define TEST_BUTTON_TEST_DURATION_COUNT (10)

#include "theTimer.h"

class ButtonHandler
{
public:
  virtual void onPressed() = 0;
  virtual void onReleased() = 0;
};

class TestButton : public TheTimerCallback
{
protected:
  int gpio;
  bool state;
  bool pressing;

  /** callbak handling **/
  ButtonHandler *handlers[TEST_BUTTON_CALLBACK_NUM_MAX];
  int handlerNumber = 0;

public:
  TestButton(int gpio);

  void setup(TheTimer *timer);
  virtual void onTimerFired();
  void setHandler(ButtonHandler *handler);

protected:
  void fireOnPressed();
  void fireOnReleased();
};

#endif // TEST_BUTTON
