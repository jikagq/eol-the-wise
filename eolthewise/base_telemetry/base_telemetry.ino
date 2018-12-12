/*code base station telemetry*/

/*analogue measures*/
#define TemperaturePin 0
#define LightPin 1
#define girouettePin 2

/*digital measures*/


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
  pinMode(girouettePin, INPUT);
  
}




// the loop function runs over and over again forever
void loop() {
  
  
  /*digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("off");
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  Serial.println("on");// wait for a second
  delay(1000);*/


  if(flag_trame_recu == 1){//check si une trame valide a été reçu
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        //interpreteur();
      Serial.println("recu: "+Trame_RX);
     reset_all();//une fois traitement fini reset
    }else{
          digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      }
  
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
/*void interpreteur(void){
    char c = '\0';
    c = Trame_uart_rx[0]; //1er caractere reçu indique l'action à effectuer

    switch(c){
          case '0' :{//mode test test
              TXframe("Frame detected");
              TXframe("Ground telemetry ok");
              TXframe("Test ok :)");
              break;
          }
          case 's' :{//send all
                update_valeurs(&data_mesures);

                itoad(get_angle(&data_mesures), &tab_temp, 10);
                ajout_trame_uart('g',&tab_temp,&Trame_uart_tx);
                TXframe(&Trame_uart_tx);
                reset_uart();

                itoad(get_humi(&data_mesures), &tab_temp, 10);
                ajout_trame_uart('h',&tab_temp,&Trame_uart_tx);
                TXframe(&Trame_uart_tx);
                reset_uart();

                itoad(get_lum(&data_mesures), &tab_temp, 10);
                ajout_trame_uart('l',&tab_temp,&Trame_uart_tx);
                TXframe(&Trame_uart_tx);
                reset_uart();

                itoad(get_temp(&data_mesures), &tab_temp, 10);
                ajout_trame_uart('t',&tab_temp,&Trame_uart_tx);
                TXframe(&Trame_uart_tx);
                reset_uart();
                break;
                  }
          case 'u':{//mise à jour des capteurs
              update_valeurs(&data_mesures);
              ack();
              break;
                 }
          case 'g':{//girouette
             itoad(get_angle(&data_mesures), &tab_temp, 10);
             ajout_trame_uart('g',&tab_temp,&Trame_uart_tx);
             TXframe(&Trame_uart_tx);
             reset_uart();
              break;
                 }
          case 'h':{//humidité
               itoad(get_humi(&data_mesures), &tab_temp, 10);
               ajout_trame_uart('h',&tab_temp,&Trame_uart_tx);
               TXframe(&Trame_uart_tx);
               reset_uart();
              break;
               }
           case 'l':{//luminosité
               itoad(get_lum(&data_mesures), &tab_temp, 10);
                ajout_trame_uart('l',&tab_temp,&Trame_uart_tx);
                TXframe(&Trame_uart_tx);
                reset_uart();
               break;
               }
           case 't':{//température
               itoad(get_temp(&data_mesures), &tab_temp, 10);
                ajout_trame_uart('t',&tab_temp,&Trame_uart_tx);
                TXframe(&Trame_uart_tx);
                reset_uart();
               break;
               }
           case 'p':{//controle pwm servo
               controle_servo();//p:1,255;
               reset_uart();

               //statut_pwm = ; //0= pas de pwm 1=pwm en sortie
               //pwm = ; //valeur de la pwm
               break;
               }
           default :{
               nak();
               break;
               }
          }
}*/
void reset_all(void){
  incomingChar = '\0';   // for incoming serial data
  Trame_RX ="";
  Trame_TX ="";
  flag_trame_recu =0;
}

void send_all_data(void){
  
}

void update_valeurs(void){
   gir   = get_girouette();
   temp = get_temperature();
   lum  = get_luminosite();
}

/*lit l'adc*/
int get_girouette(void){  
    return analogRead(girouettePin) ;
}
int get_temperature(void){   
    return analogRead(TemperaturePin);
}
int get_luminosite(void){
    return analogRead(LightPin);
}


