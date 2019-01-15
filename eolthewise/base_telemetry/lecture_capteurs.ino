int wind_tick =0;

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



int get_windspeed_raw() {
  /*avec interruption sur 2 ou 3*/
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
}






int get_humi_raw(void){
  int humidite_raw=0;

  return humidite_raw;
}



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

//https://tushev.org/articles/arduino/9/measuring-frequency-with-arduino


// int get_pluvio_raw(void){ }
