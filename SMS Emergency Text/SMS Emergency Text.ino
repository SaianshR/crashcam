#include <M5StickCPlus.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;

float accX = 0;
float accY = 0;
float accZ = 0;

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.IMU.Init();
  USE_SERIAL.begin(115200);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  for(uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  wifiMulti.addAP("YYYY", "ZZZZZ");


}

void loop() {
  // jerk detector
    while (1) {
      M5.IMU.getAccelData(&accX, &accY, &accZ);
      if (accX > 1.5 || accY > 1.5) {
          break;
      }

  // send sms

     // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url

      http.begin("https://api.46elks.com/a1/sms");
      http.addHeader("Content-Type", "application/x-www-form-urlencoded"); 
      http.setAuthorization("XXXXX", "YYYYYY");
      int httpCode = http.POST("'from:+XXXXX','to:+XXXXX','message:###SOS###'");

    USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
     httpCode = http.GET();

    // httpCode will be negative on error
    if(httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            USE_SERIAL.println(payload);
        }
    } else {
        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
}

}
}  

