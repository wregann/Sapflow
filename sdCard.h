#include <SPI.h>
#include <SD.h>

const int SDChip = 10;
String fileName;
File myFile;

void beginSD(String nameFile) {
  if (!SD.begin(10)) {
    Serial.println("SD Begin Failed");
  }
  else {
    Serial.println("SD Begin Success");
  }


  Serial.println(nameFile);
  fileName = nameFile;

  
  if (SD.exists(nameFile)) {
    Serial.println("File Removed");
    SD.remove(nameFile);
  }



  myFile = SD.open(fileName, FILE_WRITE);
  myFile.println("Time,TempTop,TempBottom,TempDiff");
  myFile.close();
  Serial.println("File Created");
  
}

boolean writeToSD(String data) {
  SD.begin(SDChip);
  myFile = SD.open(fileName, FILE_WRITE);
  if (myFile) {
    myFile.println(data);
    myFile.close();
    return true;
  }
  else {
    Serial.println("write to SD Card failed");
    myFile.close();
    return false;
  }
}

String convertTempsCSV(struct temps measuredTemps) {
  String tempsString;
  tempsString += measuredTemps.Time;
  tempsString += ",";
  tempsString += measuredTemps.TTop;
  tempsString += ",";
  tempsString += measuredTemps.TBottom;
  tempsString += ",";
  tempsString += measuredTemps.TDiff;
  return tempsString;
}
