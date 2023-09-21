#include "vibController.h"

/**
 * VibFbRequest implementations
 */

void VibFbRequest::execute(FirebaseData &fbdo)
{
  String path = String(this->basePath) + String("/id-") + String(this->sensorId);

  time_t timeoffset;
  time(&timeoffset);

  FirebaseJson json;
  json.add("state", this->active);
  json.add("time", timeoffset);

  Firebase.set(fbdo, F(path.c_str()), json);
}

/**
 * VibController implementations
 */

VibController::VibController(int sensorId, FbHelper *fb, VibSensor* vibSensor, LedIndicator *led)
{
  activeReq.active = true;
  activeReq.sensorId = sensorId;
  inactiveReq.active = false;
  inactiveReq.sensorId = sensorId;
  this->fb = fb;
  this->led = led;
  this->vibSensor = vibSensor;
}

void VibController::setup() {
  if (!this->vibSensor) {
    Serial.println("Need VibSensor for the VibController class.");
    return;
  }

  this->vibSensor->setCallback(this);
}

void VibController::onStateChanged(bool vib)
{
  if (!this->fb)
  {
    Serial.println("VibController::onStateChanged() was failed, due to no FbHelper object.");
    return;
  }

  // request to store data to db
  this->fb->request(vib ? &this->activeReq : &this->inactiveReq);

  // indicator
  if (this->led)
  {
    this->led->setLight(vib);
  }
  return;
}
