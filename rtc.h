#include <RTClib.h>
#include <Wire.h>
RTC_PCF8523 rtc;

// BEGIN RTC -
void beginRTC() {
  if (! rtc.begin()) {
    Serial.println("RTC Begin Failed");
  }
  else {
    Serial.println("RTC Begin Success");
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

//Creates a name for the file based on the current date
//Returns a string of desired name
String createFileName() {
  String fileName;
  DateTime now = rtc.now();
  fileName += now.month();
  fileName += now.day();
  fileName += now.year();
  fileName += ".csv";
  
  return fileName;
}

//Returns String of current time - need to check over
String getTime() {
  String curTime;
  DateTime now = rtc.now();
  curTime += now.hour();
  curTime += ":";
  curTime += now.minute();
  curTime += ":";
  curTime += now.second();
  curTime += " ";
  curTime += now.month();
  curTime += "/";
  curTime += now.day();
  return curTime;
}
