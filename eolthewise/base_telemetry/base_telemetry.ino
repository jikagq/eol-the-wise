#include <Adafruit_INA219.h>
#include <Wire.h>

#include <Servo.h>

//#include <FreqMeasure.h>

/*code base station telemetry*/

/*analogue measures*/
#define TemperaturePin 0
#define LightPin 1
#define GirouettePin 2

/*digital measures*/
#define EncodePin0 4
#define EncodePin1 5
#define EncodePin2 6
#define EncodePin3 7

#define AnemometerPin 2
#define HumiPin 8

#define PluviometerPin 3


/*Servo Pins*/
#define ServoPin1 9
#define ServoPin2 10

/*I2C PINS*/
Adafruit_INA219 ina219;

String temperature = "0";
String luminosite = "0";
String girouette = "0";

String encodeur = "0";
String windspeed = "0";
String humidite = "0";

String rain = "0";

String voltage = "0";
String current = "0";
String power = "0";


/*Var communication*/
char incomingChar = '\0';   // for incoming serial data
String Trame_RX ="";
String Trame_TX ="";
bool flag_trame_recu=0;

/*servomoteurs*/
Servo Servo1;
Servo Servo2;


void setup() {
  Serial.begin(9600);      // open the serial port at 9600 bps:
  
  
  pinMode(LED_BUILTIN, OUTPUT);  // initialize digital pin LED_BUILTIN as an output.
 digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  
  pinMode(TemperaturePin, INPUT);
  pinMode(LightPin, INPUT);
  pinMode(GirouettePin, INPUT);

  pinMode(EncodePin0, INPUT_PULLUP);
  pinMode(EncodePin1, INPUT_PULLUP);
  pinMode(EncodePin2, INPUT_PULLUP);
  pinMode(EncodePin3, INPUT_PULLUP);

 pinMode(AnemometerPin, INPUT_PULLUP);
  pinMode(HumiPin, INPUT);

  /*interruption pour le pluviometre*/
  pinMode(PluviometerPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PluviometerPin), int_pluvio, FALLING);
  
  /*ina219 ini*/
  ina219.begin();
  /*calibration si besoin*/
  //ina219.setCalibration_32V_1A();
  //ina219.setCalibration_16V_400mA();

  /*servomoteurs*/
  Servo1.attach(ServoPin1);
  Servo2.attach(ServoPin2);

  }

//volatile bool flag_pluie = 0;
//unsigned long previousMillis = 0;        // will store last time LED was updated
//const long interval = 2000;           // interval at which to blink (milliseconds)


// the loop function runs over and over again forever
void loop() {
  
  
 if(flag_trame_recu == 1){//check si une trame valide a Ã©tÃ© reÃ§u
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      interpreteur();//traitement
      //Serial.println("recu: "+Trame_RX);
     reset_all();//une fois traitement fini reset
    }else{
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    }

    /*if(flag_pluie == 1){
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        attachInterrupt(digitalPinToInterrupt(PluviometerPin), int_pluvio, FALLING);
        flag_pluie =0;
      }
    }*/
    /*Serial.println("insgfs");  
    delay(100);

    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(100);*/
}

void serialEvent(){
  if (Serial.available() > 0) {
        incomingChar = Serial.read();  // read the incoming byte:
        if(incomingChar == ';'){//fin de trame
          flag_trame_recu=1;
        }else{//ajout du caractere Ã  la suite de la chaine
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
          case '1':{//controle pwm servo
              String cmd =  Trame_RX;
              Control_servo(cmd);//1:1,180;
               Serial.println("ACK;");
               reset_all();
               break;
          }
          case '2' :{//send all
                update_valeurs();
                Serial.println(send_all_measure());
                reset_all();
                break;
          }
          case '3':{//mise Ã  jour des capteurs
              update_valeurs();
              Serial.println("ACK;");
              reset_all();
              break;
          }
          case 't':{//tempÃ©rature
               Trame_TX = temperature+";";
               Serial.println(Trame_TX);
               reset_all();
               break;
               }
          case 'l':{//luminositÃ©
               Trame_TX = luminosite+";";
               Serial.println(Trame_TX);
               reset_all();
               break;
               }
          case 'g':{//girouette
              Trame_TX = girouette+";";
              Serial.println(Trame_TX);
              reset_all();
              break;
          }
          case 'e':{//encodeur
              Trame_TX = encodeur+";";
              Serial.println(Trame_TX);
              reset_all();
              break;
               }
          case 'w':{//vitesse anemometre
              windspeed = String(get_windspeed_raw());//test!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
              Trame_TX = windspeed+";";
              Serial.println(Trame_TX);
              reset_all();
              break;
               } 
          case 'h':{//humiditÃ©
              Trame_TX = humidite+";";
              Serial.println(Trame_TX);
              reset_all();
              break;
               }
          case 'r':{//pluie
              Trame_TX = rain+";";
              Serial.println(Trame_TX);
              reset_all();
              break;
               }
          case 'v':{//voltage
              Trame_TX = voltage+";";
              Serial.println(Trame_TX);
              reset_all();
              break;
               }
          case 'c':{//current
              Trame_TX = current+";";
              Serial.println(Trame_TX);
              reset_all();
              break;
               }
          case 'p':{//power
              Trame_TX = power+";";
              Serial.println(Trame_TX);
              reset_all();
              break;
               }
           default :{
               Serial.println("NAK;");
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



void update_valeurs(void){
   temperature = String(get_temperature_raw());
   luminosite  = String(get_luminosite_raw());
   girouette   = String(get_girouette_raw());

   

   encodeur = String(get_encoder_raw()); 


   windspeed = String(get_windspeed_raw());
   humidite = String(get_humi_raw());
   rain = String(get_rain_raw());

   voltage = String(get_voltage_raw());
   current = String(get_current_raw());
   power = String(get_power_raw());

  
}

String  send_all_measure(void){

   return "t:"+temperature+","+"l:"+luminosite+","+"g:"+girouette+","+"e:"+encodeur+","+"w:"+windspeed+","+"h:"+humidite+","+"r:"+rain+","+"v:"+voltage+","+"c:"+current+","+"p:"+power+";";
}



























