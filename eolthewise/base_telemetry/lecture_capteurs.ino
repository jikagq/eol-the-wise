volatile int wind_tick =0;
volatile int pluie_tick =0;


/*analogues measures*/
int get_girouette_raw(void){  
    return analogRead(GirouettePin) ;
}
int get_temperature_raw(void){   
    return analogRead(TemperaturePin);
}
int get_luminosite_raw(void){
    return analogRead(LightPin);
}


/*digital measure*/
int get_encoder_raw(){
  int value=0;
  value = (digitalRead(EncodePin0)*pow(2,0)) + (digitalRead(EncodePin1)*pow(2,1)) + ( digitalRead(EncodePin2)*pow(2,2))+ (digitalRead(EncodePin3)*pow(2,3));
  Serial.println(digitalRead(EncodePin0));
  Serial.println(digitalRead(EncodePin1));
  Serial.println(digitalRead(EncodePin2));
  Serial.println(digitalRead(EncodePin3));
  return value;
}

float get_windspeed_raw(void) {
  float windspeed_raw = 0;
  
  windspeed_raw = getFrequency(AnemometerPin);

  //Serial.println(windspeed_raw);
  
  if(windspeed_raw == -1){
    return 0.0;
  }else{
    return windspeed_raw/2.4;
    //return windspeed_raw;
  }
}

float get_humi_raw(void){
  float humidite_raw = 0;
  
  humidite_raw = getFrequency(HumiPin);
  if(humidite_raw == -1){
    return 0.0;
  }else{
    return humidite_raw;
  }
}

long getFrequency(int pin) {
  //https://tushev.org/articles/arduino/9/measuring-frequency-with-arduino
  #define SAMPLES 4
  long highTime=0;    //integer for storing high time
  long lowTime=0;     //integer for storing low time
  float period=0;    // integer for storing period
  float freq=0;      //storing frequency
  
  for(unsigned int j=0; j<SAMPLES; j++){
    //freq+= 500000/pulseIn(pin, LOW, 250000);//low or high ? + timeout
    //freq+= 1000000/((pulseInLong(pin, HIGH, 250000))*2);//low or high ? + timeout
    //2*4096ech*0.25s=34min d'attente!!! 

    highTime=pulseInLong(pin,HIGH, 500000);  //read high time
    //Serial.println(highTime);
    lowTime=pulseInLong(pin,LOW, 500000);    //read low time
    period = highTime+lowTime; // Period = Ton + Toff
    //Serial.println(period);
    if(period == 0.0){
      freq =0;
    }else{
      freq += 1000000/period;       //getting frequency with totalTime is in Micro seconds
    }
    
  }
return freq / SAMPLES;
}


float get_rain_raw(void){
  //float rain_raw = 0;
  //Serial.println(pluie_tick * 0,2794);
  //Serial.println(pluie_tick);
  return pluie_tick * 0.2794;
}


volatile unsigned long lastInterrupt;
void int_pluvio(void){
   if(millis() - lastInterrupt > 10) // we set a 10ms no-interrupts window
    {    
      pluie_tick++;
      //Serial.println(pluie_tick);
      lastInterrupt = millis();
    }
}


/*int get_windspeed_raw() {
  //avec interruption sur 2 ou 3
  int int_time = millis();
  int cur_time=0;
  wind_tick =0;
  
  attachInterrupt(digitalPinToInterrupt(AnemometerPin), int_anemometer, CHANGE);
  while(cur_time < int_time+60000){
    cur_time = millis();
    Serial.println(cur_time);
  }
  detachInterrupt(digitalPinToInterrupt(AnemometerPin)) ;

  return wind_tick * 2,4;
  
}
void int_anemometer(){
  wind_tick++; 
}*/





/**float freqmeasurement(void){
  //!!! avec la lib freq measure uniqument sur pin8 et pin 10 et 9 inutile avec en pwm
  //http://www.pjrc.com/teensy/td_libs_FreqMeasure.html
  double sum=0;
  int count=0;
  int i = 0;
  FreqMeasure.begin();
  for(i=0;i<10);i++){
    if (FreqMeasure.available()) {
      // average several reading together
      sum = sum + FreqMeasure.read();
      count = count + 1;
      if (count > 30) {
        float frequency = FreqMeasure.countToFrequency(sum / count);
        Serial.println(frequency);
        sum = 0;
        count = 0;
      }
    }
  }
  FreqMeasure.end();
  return frequency;
}**/








