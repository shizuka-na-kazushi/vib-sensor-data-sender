
#ifndef __TEST_BUTTON_CONTROLLER_H__
#define __TEST_BUTTON_CONTROLLER_H__

#include "testbutton.h"
#include "toggleLed.h"
#include "fbhelper.h"

#define FB_DB_PATH_FOR_TEST_BUTTON "/test-data/1"

class TestButtonController : public TestButton,
                             public ButtonHandler,
                             public FbHelperRequest
{

protected:
  FbHelper *fb;
  LedIndicator *led;

  int sampleCount = 0;

public:
  TestButtonController(int gpio, FbHelper *fb, LedIndicator *led) : 
    TestButton(gpio), 
    fb(fb), 
    led(led)
  {
  }

  void setup(TheTimer *timer);

  /** ButtonHandler interface **/
  virtual void onPressed();
  virtual void onReleased();
  /** */
  virtual void execute(FirebaseData& fbdo);
};

#endif // !__TEST_BUTTON_CONTROLLER_H__
