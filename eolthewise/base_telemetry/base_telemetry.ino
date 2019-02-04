/*Wind farm ping project 55
 * wind side
 *base_telemetry.ino
 *Communication and command processing
 *Théo Paris 2018
*/

#include <Adafruit_INA219.h>
#include <Wire.h>
#include <Servo.h>

/*analogue measures pins*/
#define TemperaturePin 0
#define LightPin 1
#define GirouettePin 2

/*digital measures pins*/
#define EncodePin0 4
#define EncodePin1 5
#define EncodePin2 6
#define EncodePin3 7

#define AnemometerPin 2//interrupt
#define HumiPin 8

#define PluviometerPin 3//interrupt


/*Servo Pins*/
#define ServoPin1 9
#define ServoPin2 11

/*I2C PINS*/
Adafruit_INA219 ina219;

/*servomoteurs*/
Servo Servo1;
Servo Servo2;

/*variables for saving measure to send*/
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


/*Var for communicate with raspberry pi*/
char incomingChar = '\0';   // for incoming serial data
String Trame_RX ="";
String Trame_TX ="";
bool flag_trame_recu=0;




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
  /*calibrate ina219*/
  //ina219.setCalibration_32V_1A();
  ina219.setCalibration_16V_400mA();

  /*servomoteurs*/
  Servo1.attach(ServoPin1);
  Servo2.attach(ServoPin2);

  }


// the loop function runs over and over again forever
void loop() {
  
  
 if(flag_trame_recu == 1){//check if a valid command has been received 
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      interpreteur();//process the command
      //Serial.println("recu: "+Trame_RX);
     reset_all();//when process is finished reset all communication variable
    }else{
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    }


    //update_valeurs(void);
   // delay();

  /*test*/
  /*update_valeurs();
   Serial.println(send_all_measure());
  reset_all();
   delay(2000);*/

}

/*listen the serial port and detect trame*/
void serialEvent(){
  if (Serial.available() > 0) {
        incomingChar = Serial.read();  // read the incoming byte:
        if(incomingChar == ';'){//fin de trame
          flag_trame_recu=1;//trame detected
        }else{//ajout du caractere Ã  la suite de la chaine
          Trame_RX = Trame_RX+ incomingChar;
          flag_trame_recu=0;  //no trame detected
        }
    }
}

/*detect the command received*/
void interpreteur(void){
    char c = '\0';
    c = Trame_RX.charAt(0); // the first caracter reprsesent the type of the command
    switch(c){
          case '0' :{//com test
              Serial.println("Base telemetry V2");
              Serial.println("Serial Frame detected");
              Serial.println("Ground telemetry ok");
              Serial.println("Communication test ok :)");
              reset_all();
              break;
          }
          case '1':{//pwm servo command
              String cmd =  Trame_RX;
              Control_servo(cmd);//1:1,180;
               //Serial.println("ACK;");
               reset_all();
               break;
          }
          case '2' :{//send all value
                update_valeurs();
                Serial.println(send_all_measure());
                reset_all();
                break;
          }
          case '3':{//update sensors
              update_valeurs();
              //Serial.println("ACK;");
              reset_all();
              break;
          }
          case 't':{//tempÃ©rature
               Trame_TX = temperature+";";//create trame
               Serial.println(Trame_TX);//send the trame on serial port
               reset_all();//reset all communciation variable
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

/*reset communication variables*/
void reset_all(void){
  incomingChar = '\0';   // for incoming serial data
  Trame_RX ="";
  Trame_TX ="";
  flag_trame_recu =0;
}


/*update all sensors data*/
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

/*returns all sensors values*/
String  send_all_measure(void){
   return "t:"+temperature+","+"l:"+luminosite+","+"g:"+girouette+","+"e:"+encodeur+","+"w:"+windspeed+","+"h:"+humidite+","+"r:"+rain+","+"v:"+voltage+","+"c:"+current+","+"p:"+power+";";
}



























