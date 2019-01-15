void Control_servo(String cmd){
  int taille = cmd.length();
  
  if(cmd.charAt(2) == '1'){
    String subs = cmd.substring(4, taille-1);
    int angle = subs.toInt();
    Servo1.write(angle);
  }else{
    String subs = cmd.substring(4, taille-1);
    int angle = subs.toInt();
    //Servo2.write(angle);
  }
  
  
  
  
}
