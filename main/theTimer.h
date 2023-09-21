#ifndef THE_TIMER
#define THE_TIMER

#define MAX_THE_TIMER_NUMBER (10)

class TheTimerCallback
{
public:
  virtual void onTimerFired() = 0;
};

class TheTimerContext
{
public:
  int millisec = 0;
  int duration = 0;
  bool cyclic = false;
  TheTimerCallback *callback = NULL;

  void init();
  void setCallback(TheTimerCallback *callback, int duration, bool cyclic);
  void checkTimer(int now);
};

class TheTimer
{
protected:
  TheTimerContext intervalTimers[MAX_THE_TIMER_NUMBER];
  TheTimerContext timeoutTimers[MAX_THE_TIMER_NUMBER];

  int intervalTimerNum = 0;
  int timeoutTimerNum = 0;

public:
  TheTimer()
  {
  }

public:
  void setup();
  void loop();

  int setInterval(TheTimerCallback *callback, int millisec);
  int setTimeout(TheTimerCallback *callback, int millisec);
};

#endif // !THE_TIMER