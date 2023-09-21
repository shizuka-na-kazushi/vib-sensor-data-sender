#ifndef BLINKING_LED
#define BLINKING_LED

#include "toggleLed.h"
#include "theTimer.h"

class BlinkingLed : public TheTimerCallback, public LedIndicator
{
protected:
  int gpio;
  int interval;
  bool blinking;

  bool onOrOff;

public:
  BlinkingLed(int gpio, int interval);

  void setup(TheTimer *timer);

  /** LedIndicator interface */
  void setLight(bool onOrOff);

  /** TheTimerCallback interface */
  void onTimerFired(); 
};

#endif // BLINKING_LED
