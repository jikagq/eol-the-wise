/*Wind farm ping project 55
 * wind side
 *lecture_capteurs.ino
 *Read sensors measures
 *Théo Paris 2018
*/
volatile int wind_tick =0;
volatile int pluie_tick =0;


/*analogues measures*/

/*measure weather vane sensor*/
int get_girouette_raw(void){  
    return analogRead(GirouettePin) ;
}

/*measure temperature sensor*/
float get_temperature_raw(void){  
  int AnalogVolt = 0;
  
  AnalogVolt = analogRead(TemperaturePin);
  float temperature_raw = (float)(AnalogVolt *5) /(float)1023;
 temperature_raw = (temperature_raw *100) -273;
  return temperature_raw;
}
/*measure light sensor*/
int get_luminosite_raw(void){
    return analogRead(LightPin);
}

/*digital measure*/

/*measure encoder*/
int get_encoder_raw(){

  int value=0;
  bool e0=1;
  bool e1=1;
  bool e2=1;
  bool e3 =1;

  e0=digitalRead(EncodePin0);
  e1=digitalRead(EncodePin1);
  e2=digitalRead(EncodePin2);
  e3=digitalRead(EncodePin3);

  /*etais ce la l'erreur ????*/
  Serial.println("");

  if(e0 == 0){
    //Serial.println(1);
    e0=1;
  }else{
    //Serial.println(0);
    e0=0;
  }
  if(e1 == 0){
    //Serial.println(1);
    e1=1;
  }else{
    //Serial.println(0);
    e1=0;
  }
  if(e2 == 0){
    //Serial.println(1);
    e2=1;
  }else{
    //Serial.println(0);
    e2=0;
  }
  if(e3 == 0){
   // Serial.println(1);
    e3=1;
  }else{
    //Serial.println(0);
    e3=0;
  }
  value = (e0*pow(2,0)) + (e1*pow(2,1)) + ( e2*pow(2,2))+ (e3*pow(2,3));
  value = GrayToBinary(value);//convert gray code from encodeur to natural binnary
  return value;
}

/*convert gray code to natural binnary*/
unsigned int GrayToBinary(unsigned int num)
{
    unsigned int mask = num >> 1;
    while (mask != 0)
    {
        num = num ^ mask;
        mask = mask >> 1;
    }
    return num;
}

/*measure moist sensor*/
float get_humi_raw(void){
  float humidite_raw = 0;
  
  humidite_raw = getFrequency(HumiPin);
  if(humidite_raw == -1){
    return 0.0;
  }else{
    return humidite_raw;
  }
}

/*measure a frequency*/
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

/*measure pluviometer data*/
/*0.2794ml = 1 pluviometer switch*/
float get_rain_raw(void){
  return pluie_tick * 0.2794;
}

/*inteerupt that count when the pluviometer switch*/
volatile unsigned long lastInterrupt;
void int_pluvio(void){
   if(millis() - lastInterrupt > 10) // we set a 10ms no-interrupts window
    {    
      pluie_tick++;//count the number of pluviometer switch
      lastInterrupt = millis();
    }
}
 
/*measure the wind speed km/s with interrup*/
float get_windspeed_raw() {
  wind_tick =0;
  attachInterrupt(digitalPinToInterrupt(AnemometerPin), int_anemometer, CHANGE);//enable interrupt
  delay(1000);//when the interrupt is enable wait 1s to measure the number of anemometer tick's
  detachInterrupt(digitalPinToInterrupt(AnemometerPin)) ;//disable the interrup
  return wind_tick * 2.4;
}
void int_anemometer(){
  wind_tick++; //count the number of anemometer tick's
}








