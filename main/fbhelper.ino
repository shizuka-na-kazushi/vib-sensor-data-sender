
#include "config.h"
#include "fbhelper.h"

/**
 *
 * FbHelperQueue implementations
 *
 */

void FbHelperQueue::request(FbHelperRequest *req)
{
  if (MAX_FB_HELPER_QUEUE_SIZE <= this->queueCount)
  {
    Serial.print("FbHelperQueue::sendRequest() failed. Due to max queue limit");
    Serial.println(MAX_FB_HELPER_QUEUE_SIZE);
    return;
  }

  Serial.print("[FBQUEUE] Queue IN - QueueBottom=");
  Serial.print(this->queueBottomIndex);
  Serial.print(";  QueueCount=");
  Serial.println(this->queueCount);

  int index = (this->queueBottomIndex + this->queueCount) % MAX_FB_HELPER_QUEUE_SIZE;
  this->queue[index] = req;
  this->queueCount++;
}

void FbHelperQueue::processQueue(FirebaseData &fbdo)
{
  if (this->queueCount <= 0)
  {
    return;
  }

  Serial.print("[FBQUEUE] Queu OUT - QueueBottom=");
  Serial.print(this->queueBottomIndex);
  Serial.print(";  QueueCount=");
  Serial.print(this->queueCount);
  Serial.print("; going to execute ...");

  int ret = this->queueBottomIndex;
  this->queue[ret]->execute(fbdo);
  ret++;

  this->queueBottomIndex = (ret + MAX_FB_HELPER_QUEUE_SIZE) % MAX_FB_HELPER_QUEUE_SIZE;
  this->queueCount--;

  Serial.println(" done.");
}

/**
 *
 * FbHelper implementations
 *
 */

FbHelper::FbHelper()
{
  this->config.api_key = FIREBASE_API_KEY;
  this->config.database_url = FIREBASE_DATABASE_URL;
  this->config.token_status_callback = tokenStatusCallback;

  this->auth.user.email = FIREBASE_USER_EMAIL;
  this->auth.user.password = FIREBASE_USER_PASSWORD;
}

void FbHelper::setup(TheTimer* timer)
{
  // Since Firebase v4.4.x, BearSSL engine was used, the SSL buffer need to be set.
  // Large data transmission may require larger RX buffer, otherwise connection issue or data read time out can be occurred.
  this->fbdo.setBSSLBufferSize(4096 /* Rx buffer size in bytes from 512 - 16384 */, 1024 /* Tx buffer size in bytes from 512 - 16384 */);

  Serial.println("going to Firebase.begin");
  Firebase.begin(&this->config, &this->auth);
  Serial.println("Firebase.begin returned!");

  // Comment or pass false value when WiFi reconnection will control by your code or third party library e.g. WiFiManager
  // Firebase.reconnectNetwork(true);

  timer->setInterval(this, FIREBASE_SERVER_ACCESS_MINIMUM_INTERVAL);
}

void FbHelper::onTimerFired()
{
  if (Firebase.ready())
  {
    processQueue(this->fbdo);
  }
}
