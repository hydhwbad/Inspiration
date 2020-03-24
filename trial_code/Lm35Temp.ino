float Temp;
int Lm35in = A0;
int chno;
int samples;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long t1, t2;
  t1= millis();
  getTemp();
  t2= millis();
  Serial.print("Temp: ");
  Serial.print(Temp);
  Serial.print(" ");
  Serial.print(t1);
  Serial.print(" ");
  Serial.println(t2);  
  Serial.print(" ");
  Serial.println(t2-t1);  

  delay(5000);
  
  
  //delay(2000);
}

void getTemp() {
  float tread;
  tread = readVolt(Lm35in, 25);
  Temp = tread * 100;
}


float readVolt(int chno, int samples) {
  analogReference(EXTERNAL);
  float Avg = 0;
  float smplData[samples];
  float AvgHigh;
  float AvgLow;
  float adcfilt;
  int count;
  for (int loop1 = 0; loop1 < samples; loop1++){
    smplData[loop1] = analogRead(chno) * 0.0048825;
    Avg = Avg + smplData[loop1];
    delay(10);
  }
  
  Avg = Avg/samples;
  AvgHigh = Avg + 0.05;
  AvgLow = Avg - 0.05;
  count =0;
  adcfilt = 0;
  for (int loop2 = 0; loop2 < samples; loop2 ++){
    if (smplData[loop2] > AvgLow) {
        if (smplData[loop2] < AvgHigh){
          adcfilt = adcfilt + smplData[loop2];
          count = count + 1;
        }
      }
    }
    if (count > 0) {
      adcfilt = adcfilt/count;
    }
     else{
        adcfilt = Avg;
        //Serial.print("D Avg ");
      }
    return adcfilt;
}
