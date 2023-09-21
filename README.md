
# Vibration sensor data sender

This is program running on ESP32 chip with Arduino development environment.

The purpose of this program is to detect vibration of laundry machine or drying machine and send it to Firebase realtime database. 

The system is a part of [Cloud based coin laundry operation viewer](https://laundry-watcher.web.app/?github-1). Its React based web app, ``Laundry-watcher`` is also open source on [Github repository](https://github.com/shizuka-na-kazushi/laundry-watcher).

This is used in [Hydrangea Hakone](https://hydrangea-hakone.com), my own rental apartment which has community coin laundry room as part of the facility. All residents can access web app to check if machine is ocupied or not.

# Software and functionalities

## WiFi client
Using ESP32 WiFi module, once the system starts, it atempts to connect to specific WiFi AP (configurable in header file). While WiFi is connected, small dot in 7 segment LED starts blink.


## Firebase SDK
[Firebase ESP32 Client](https://www.arduino.cc/reference/en/libraries/firebase-arduino-client-library-for-esp8266-and-esp32/) is used.

After WiFi connection is established and IP address is obtained from AP, SDK for Firebase realtime database is initialized.

## Sensor detection

While the system is alive, it checks sensor output and if its state is changed, it accumulated and the time avarage is caluculated. And then after some duration of time, it stores new state and time where it happens to Firebase realtime database.

Data in Firebase is referred from web app frontend directly using JavaScript SDK and shown in the app, which is described above.

The sensor state also reflrects to LED indicator. 

## Test button

Devopment board has a H/W push button (see, below Hardware section).
The log is to be sent for testing or debugging purpose, if press the button.

# Hardware

- WayinTop ESP32 development board ([Amazon Japan](https://www.amazon.co.jp/WayinTop-ESP32%E9%96%8B%E7%99%BA%E3%83%9C%E3%83%BC%E3%83%89-BLE%E3%83%A2%E3%82%B8%E3%83%A5%E3%83%BC%E3%83%AB-ESP-WROOM-32%E5%AE%9F%E8%A3%85%E6%B8%88%E3%81%BF-%E5%B0%82%E7%94%A8USB%E3%82%B1%E3%83%BC%E3%83%96%E3%83%AB%E4%BB%98%E3%81%8D/dp/B086QKRY25/ref=sr_1_1_sspa?adgrpid=143731318967&hvadid=651256732064&hvdev=c&hvlocphy=1009297&hvnetw=g&hvqmt=e&hvrand=5099709688062319516&hvtargid=kwd-1248050266493&hydadcr=9356_13660209&jp-ad-ap=0&keywords=wayintop+esp32&qid=1694666382&sr=8-1-spons&sp_csd=d2lkZ2V0TmFtZT1zcF9hdGY&psc=1))


- KKHMF vibration sensor ([Amazon Japan](https://www.amazon.co.jp/KKHMF-SW-420-%E6%8C%AF%E5%8B%95%E3%82%B9%E3%82%A4%E3%83%83%E3%83%81-%E8%AD%A6%E5%A0%B1%E5%99%A8%E3%82%BB%E3%83%B3%E3%82%B5%E3%83%BC%E3%83%A2%E3%82%B8%E3%83%A5%E3%83%BC%E3%83%AB-Arduino/dp/B014KJ0V3W/ref=sr_1_7?keywords=%E6%8C%AF%E5%8B%95%E3%82%BB%E3%83%B3%E3%82%B5%E3%83%BC&qid=1694669605&sr=8-7))

- 7 segments red LED ([Akizuki shop](https://akizukidenshi.com/catalog/g/gI-00640/))
- Push switch (for sending test data to Firebase)


![hardware image](https://github.com/shizuka-na-kazushi/vib-sensor-data-sender/blob/main/images/Vibratrion-sensor-with-esp32-chip.png?raw=true)

