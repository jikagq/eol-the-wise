void Control_servo(String cmd){
  int taille = cmd.length();
  
  if(cmd.charAt(2) == '1'){
    String subs = cmd.substring(4, taille);
    int angle = subs.toInt();
    Serial.println(angle);
    Servo1.write(angle);
  }else{
    String subs = cmd.substring(4, taille);
    int angle = subs.toInt();
    Serial.println(angle);
    Servo2.write(angle);
  }
  
  
  
  
}
