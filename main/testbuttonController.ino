
#include "testbuttonController.h"

void TestButtonController::setup(TheTimer *timer) {
  TestButton::setup(timer);
  setHandler(this);
}

void TestButtonController::onPressed(){
  this->led->setLight(true);
  this->fb->request(this);
}

void TestButtonController::onReleased(){
  /* NOP */
}

void TestButtonController::execute(FirebaseData &fbdo)
{
  time_t timeoffset;
  time(&timeoffset);

  FirebaseJson json;
  json.add("logMessage", "Hello, world!");
  json.add("sampleCount", ++this->sampleCount);
  json.add("time", timeoffset);

  Firebase.set(fbdo, F(FB_DB_PATH_FOR_TEST_BUTTON), json);

  /** finally stop LED blinking! */
  this->led->setLight(false);
}
