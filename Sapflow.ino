// ---------------------------------
//             LIBRARIES
//----------------------------------
#include <SPI.h> //for SD Card
#include <SD.h>  //for SD Card
#include <RTClib.h> //for RTC
#include <Wire.h> //for RTC


// ---------------------------------
//        Included C Files
//----------------------------------
#include "config.h"  //holds variables that change function of device
#include "probes.h" // holds heater and measurement probe functionality
#include "rtc.h" //holds RTC functionality
#include "sdCard.h" //holds SD Card functionality


// ---------------------------------
//    Temp Variables - I wanna move this to config later
//----------------------------------
int delayTime = 10000; //time between measurements of probes in milliseconds
int heatTime = 5000; //time to heat up, use this to change temperature peak

// ---------------------------------
//             SETUP
//----------------------------------
void setup() {
  //Delay so program can finish uploading before starting, to check later for removal
  delay(5000); 
  
  //Begins Serial Moniter for Debugging and Testing
  Serial.begin(9600);
  
  // Begin RTC
  beginRTC();

  // SD CARD BEGIN
  beginSD(createFileName());

  // Setup Heater
  beginHeater();

}


// ---------------------------------
//             MAIN LOOP
//----------------------------------
void loop() {
  delay(delayTime); //delay between readings
  heat(heatTime); //heats us probes... hopefully
  measureAndWrite(); //look below on functionality  
}

//measureAndWrite - fully measures and inserts measurements in csv document
//  Return: boolean for write success or failure
boolean measureAndWrite() {
  return writeToSD(convertTempsCSV(voltToTemp(getTime()))); // A little messy but gets measurement and adds it to SD
}
