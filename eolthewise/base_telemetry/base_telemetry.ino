#include <Adafruit_INA219.h>
//#include <Wire.h>

/*code base station telemetry*/

/*analogue measures*/
#define TemperaturePin 0
#define LightPin 1
#define GirouettePin 2



/*digital measures*/
#define AnemometerPin 2
#define PluviometerPin 3
#define HumiPin 4

#define EncodePin0 4
#define EncodePin1 5
#define EncodePin2 6
#define EncodePin3 7

/*Servo Pins*/
#define ServoPin1 10
//#define ServoPin2 11

/*I2C PINS*/
Adafruit_INA219 ina219;


int temp = 0;
int lum = 0;
int gir = 0;

int wind_tick =0;
int enc =0;
int humi =0;
int rain =0;

int voltage =0;
int current =0 ;
int power =0;

char incomingChar = '\0';   // for incoming serial data
String Trame_RX ="";
String Trame_TX ="";
bool flag_trame_recu=0;




void setup() {
  Serial.begin(9600);      // open the serial port at 9600 bps:
  ina219.begin();
  
  pinMode(LED_BUILTIN, OUTPUT);  // initialize digital pin LED_BUILTIN as an output.
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  
  pinMode(TemperaturePin, INPUT);
  pinMode(LightPin, INPUT);
  pinMode(GirouettePin, INPUT);

  pinMode(EncodePin0, INPUT);
  pinMode(EncodePin1, INPUT);
  pinMode(EncodePin2, INPUT);
  pinMode(EncodePin3, INPUT);

  pinMode(AnemometerPin, INPUT_PULLUP);
  

  //attachInterrupt(digitalPinToInterrupt(Pin), int_, CHANGE);
  
  
}




// the loop function runs over and over again forever
void loop() {
  if(flag_trame_recu == 1){//check si une trame valide a été reçu
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      interpreteur();//traitement
      //Serial.println("recu: "+Trame_RX);
     reset_all();//une fois traitement fini reset
    }else{
          digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      }
   // delay(100);
}

void serialEvent(){
  if (Serial.available() > 0) {
        incomingChar = Serial.read();  // read the incoming byte:
        if(incomingChar == ';'){//fin de trame
          flag_trame_recu=1;
        }else{//ajout du caractere à la suite de la chaine
          Trame_RX = Trame_RX+ incomingChar;
          flag_trame_recu=0;  
        }
    }
}

void interpreteur(void){
    char c = '\0';
    c = Trame_RX.charAt(0);
    switch(c){
          case '0' :{//mode test test
              Serial.println("Base station telemetry V2");
              Serial.println("Serial Frame detected");
              Serial.println("Ground telemetry ok");
              Serial.println("Communication test ok :)");
              reset_all();
              break;
          }
          case 'p':{//controle pwm servo
               //controle_servo();//p:1,255;
//               Control_servo();
               reset_all();
               break;
          }
          case 's' :{//send all
                update_valeurs();
                Serial.println(send_all_measure());
                reset_all();
                break;
          }
          case 'u':{//mise à jour des capteurs
              update_valeurs();
              Serial.println("ACK");
              reset_all();
              break;
          }
          case 'g':{//girouette
              Trame_TX = "g:"+ get_angle();
              Serial.println(Trame_TX);
              reset_all();
              break;
          }
          case 'l':{//luminosité
               Trame_TX = "l:"+ get_lum();
               Serial.println(Trame_TX);
               reset_all();
               break;
               }
           case 't':{//température
               Trame_TX = "t:"+ get_temp();
               Serial.println(Trame_TX);
               reset_all();
               break;
               }
          case 'h':{//humidité
               //suite
              reset_all();
              break;
               }
          case 'e':{//humidité
               //suite
              reset_all();
              break;
               }
           default :{
               Serial.println("NAK");
               break;
               }
          }
}

void reset_all(void){
  incomingChar = '\0';   // for incoming serial data
  Trame_RX ="";
  Trame_TX ="";
  flag_trame_recu =0;
}

String  send_all_measure(void){
   String str1 = get_angle();
   String str2 = get_lum();
   String str3 = get_temp();
   String str4 = get_enc();
   //String str5 =
   return "g:"+ str1 +" l:"+str2+" t:"+str3 ;
}


/*accede aux valeurs traiter/envoyer*/
String get_angle(void){
    return String(gir);
}
String get_temp(void){
    return String(temp);
}
String get_lum(void){ 
    return String(lum);
}
String get_enc(void){ 
    return String(enc);
}



void update_valeurs(void){
   gir   = get_girouette();
   temp = get_temperature();
   lum  = get_luminosite();

   enc = get_encoder();
   
   //windspeed = get_windspeed();

   //humi = get_humi();
  // rain = get_rain();

  // voltage = get_volt();
  // current = get_curr();
  // power = get_pow();
}

/*analogues measures*/
int get_girouette(void){  
    return analogRead(GirouettePin) ;
}
int get_temperature(void){   
    return analogRead(TemperaturePin);
}
int get_luminosite(void){
    return analogRead(LightPin);
}



















/*digital measure*/
int get_windspeed() {
  int int_time = millis();
  int cur_time=0;
  wind_tick =0;
  
  attachInterrupt(digitalPinToInterrupt(AnemometerPin), int_anemometer, CHANGE);
  while(cur_time < int_time+60000){
    cur_time = millis();
  }
  detachInterrupt(digitalPinToInterrupt(AnemometerPin)) ;

  return wind_tick * 2,4;
  
}
void int_anemometer(){
  wind_tick++; 
}





int get_pluvio(void){
  
}
int get_humi(void){
  
}


int get_encoder(){
  int value=0;
  value = (digitalRead(EncodePin0)*2^0) + (digitalRead(EncodePin1)*2^1) + ( digitalRead(EncodePin2)*2^2)+ (digitalRead(EncodePin3)*2^3);
  return value;
}

/*I2C power measure*/
float get_INA219_power(){
  float shuntvoltage = 0;
  float busvoltage = 0;
  float current_mA = 0;
  float loadvoltage = 0;
  float power_mW = 0;

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  current_mA = ina219.getCurrent_mA();
  power_mW = ina219.getPower_mW();
  loadvoltage = busvoltage + (shuntvoltage / 1000);
  
  /*Serial.print("Bus Voltage:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltage:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Current:       "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Power:         "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");*/

  return power_mW;
} 

/*Control_servo(void){
  bool etat = 0;
  int pwm = 0;

  Trame_RX.charAt(2);
  //analogWrite(pinDEL, luminosite);

  
}*/


