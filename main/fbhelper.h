

#ifndef FB_HELPER
#define FB_HELPER

#include <FirebaseESP32.h>
#include "fbtokenhelper.h"
#include <json/FirebaseJson.h>
#include "theTimer.h"


#define FIREBASE_SERVER_ACCESS_MINIMUM_INTERVAL (500) // in millisec

#define MAX_FB_HELPER_QUEUE_SIZE (10)


class FbHelperRequest
{
public:
  virtual void execute(FirebaseData& fbdo) = 0;
};


class FbHelperQueue
{
protected:
  FbHelperRequest *queue[MAX_FB_HELPER_QUEUE_SIZE];
  int queueBottomIndex = 0;
  int queueCount = 0;

public:
  void request(FbHelperRequest *req);
  void processQueue(FirebaseData& fbdo);
};

class FbHelper : public FbHelperQueue, public TheTimerCallback
{
protected:
  FirebaseData fbdo;
  FirebaseAuth auth;
  FirebaseConfig config;
  int sendDataPrevMillis = 0;
  bool sendDataReady = false;
  int counterForSample = 0;

public:
  FbHelper();

  void setup(TheTimer* timer);
  virtual void onTimerFired();
};

#endif // !FB_HELPER
