/*Wind farm ping project 55
 * wind side
 *servomoteurs.ino
 *Control servomotors
 *Théo Paris 2018
*/

/*control servomotor*/
void Control_servo(String cmd){
  int taille = cmd.length();
  
  if(cmd.charAt(2) == '1'){//1 = first servomotor
    String subs = cmd.substring(4, taille);
    int angle = subs.toInt();
    Serial.println(angle);//pb ????
    Servo1.write(angle);
  }else{//2 = second servo
    String subs = cmd.substring(4, taille);
    int angle = subs.toInt();
    Serial.println(angle);//pb ????
    Servo2.write(angle);
  }
}

