
#include "ntphelper.h"

void NtpHelper::setup() {
    // configTime(9 * 3600L, 0, "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");
    configTime(0, 0, "ntp.nict.jp", "time.google.com", "ntp.jst.mfeed.ad.jp");    // wanted GMT based time, instead of localtime.

    struct tm timeInfo;
    char s[25];
    getLocalTime(&timeInfo);
    sprintf(s, " %04d/%02d/%02d %02d:%02d:%02d",
            timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday,
            timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
    Serial.println(s); 
}

