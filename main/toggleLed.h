#ifndef TOGGLE_LED
#define TOGGLE_LED

class LedIndicator {
public:
  virtual void setLight(bool onOrOff) = 0;
};

class ToggleLed : public LedIndicator
{
protected:
  int gpio;
  bool enable;

public:
  ToggleLed(int gpio, bool enable);

  void setup();
  virtual void setLight(bool onOrOff);
};

#endif // TOGGLE_LED
