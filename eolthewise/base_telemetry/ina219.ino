/*float voltage_raw =0;
float current_raw =0;*/

/*I2C power measure*/
/*float get_voltage_raw(void){
  float shuntvoltage = 0;
  
  shuntvoltage = ina219.getShuntVoltage_mV();
  voltage_raw = (shuntvoltage*1000)/1000;
  
  return voltage_raw;
}

float get_current_raw(void){  
  current_raw = ina219.getCurrent_mA();
  return current_raw;
}

float get_power_raw(void){
  float power_raw =0;
  power_raw = (current_raw/1000)*voltage_raw;
  return power_raw;
}*/

/*I2C power measure*/
float get_voltage_raw(void){
  float shuntvoltage = 0;
  float busvoltage = 0;
  float voltage_raw = 0;
  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  voltage_raw = busvoltage + (shuntvoltage / 1000);
  return voltage_raw;
}

float get_current_raw(void){  
  float current_raw = 0;
  current_raw = ina219.getCurrent_mA();
  return current_raw;
}

float get_power_raw(void){
  float power_raw = 0;
  power_raw = ina219.getPower_mW();
  return power_raw;
}





