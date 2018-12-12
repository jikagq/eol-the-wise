/*code base station telemetry*/

/*analogue measures*/
#define TemperaturePin 0
#define LightPin 1
#define GirouettePin 2



/*digital measures*/
#define AnemometerPin 2
#define PluviometerPin 3
#define HumiPin 4

#define EncodePin1 4
#define EncodePin2 5
#define EncodePin3 6
#define EncodePin4 7

/*Servo Pins*/
#define ServoPin1 10
//#define ServoPin2 11

/*I2C PINS*/

int temp = 0;
int lum = 0;
int gir = 0;

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
          /* case 'h':{//humidité
               //suite
              reset_all();
              break;
               }*/
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

void update_valeurs(void){
   gir   = get_girouette();
   temp = get_temperature();
   lum  = get_luminosite();
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
int get_anemometer(){
  
}
int get_pluvio(){
  
}
int get_encoder(){

}
int get_humi(){
  
}
/*I2C power measure*/
void get_INA219_values(){
  
}

/*Control_servo(void){
  bool etat = 0;
  int pwm = 0;

  Trame_RX.charAt(2);
  //analogWrite(pinDEL, luminosite);

  
}*/


