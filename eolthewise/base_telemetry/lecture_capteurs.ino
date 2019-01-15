volatile int wind_tick =0;
volatile float pluie_tick =0;

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
  //Serial.println(digitalRead(EncodePin0));
  //Serial.println(digitalRead(EncodePin1));
  //Serial.println(digitalRead(EncodePin2));
  //Serial.println(digitalRead(EncodePin3));
  return value;
}

long get_windspeed_raw(void) {
  //long windspeed_raw = 0;
  //windspeed_raw = getFrequency(AnemometerPin);
  //return windspeed_raw;
  return getFrequency(AnemometerPin)*2,4;
}

long get_humi_raw(void){
  //long humidite_raw = 0;
  //humidite_raw = getFrequency(HumiPin);
  //return humidite_raw;
  return getFrequency(HumiPin);
}

long getFrequency(int pin) {
  //https://tushev.org/articles/arduino/9/measuring-frequency-with-arduino
  //We wait for the pulse to occur in 250 mS. If you are using very slow signals, increase this value as you need. (pin, HIGH, 250000)
  #define SAMPLES 4096
  long freq = 0;
  for(unsigned int j=0; j<SAMPLES; j++){
    freq+= 500000/pulseIn(pin, LOW, 250000);//low or high ? + timeout
    Serial.println(j);
  }
  return freq / SAMPLES;
}


float get_rain_raw(void){
  float rain_raw = 0;
  return rain_raw * 0,2794;
}
void int_pluvio(void){
   pluie_tick++;
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







