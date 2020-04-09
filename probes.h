#define HEATPIN 12;

const int sampleSize = 16;
const int R1 = 10000;
const double c1 = 1.009249522e-03;
const double c2 = 2.378405444e-04;
const double c3 = 2.019202697e-07;

struct temps {
  String Time;
  double TTop, TBottom, TDiff;
};

void beginHeater() {
  pinMode(13, OUTPUT);
}

//Tests Heating Based on Timer Variable
void heat(int timer) {
  Serial.println("Begin Heating");
  digitalWrite(13, HIGH);
  delay(timer);
  digitalWrite(13, LOW);
  Serial.println("End Heating");
}

//
struct temps voltToTemp(String curTime) {
  struct temps measuredTemps; 
  double VT, VB,logR2T, R2T, logR2B, R2B, TT, TB;
   
  VT = VT + analogRead(0);
  VB = VB + analogRead(1);
  
  R2T = R1 * (1023.0 / VT - 1.0);
  R2B = R1 * (1023.0 / VB - 1.0);
  
  logR2T = log(R2T);
  logR2B = log(R2B);
  
  TT = (1.0 / (c1 + c2*logR2T + c3*logR2T*logR2T*logR2T));
  TB = (1.0 / (c1 + c2*logR2B + c3*logR2B*logR2B*logR2B));
  
  TT -= 273.15;
  TB -= 273.15;
  
  TT = (TT * 9.0)/ 5.0 + 32.0; 
  TB = (TB * 9.0)/ 5.0 + 32.0; 
  
  Serial.println("--------------------");
  Serial.print("TT: ");
  Serial.println(TT);
  Serial.print("TB: ");
  Serial.println(TB);
  
  measuredTemps = {curTime, TT, TB, (TT - TB)};
  
  return measuredTemps;
}
