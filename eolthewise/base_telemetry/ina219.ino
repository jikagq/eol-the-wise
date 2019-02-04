/*Wind farm ping project 55
 * wind side
 *ina219.ino
 *Use ina219 sensors to get current voltage and power
 *Théo Paris 2018
*/

float voltage_raw =0;
float current_raw =0;

/*returns voltage mV from ina219 sensors*/
float get_voltage_raw(void){
  float shuntvoltage = 0;

  ina219.setCalibration_16V_400mA();
  shuntvoltage = ina219.getShuntVoltage_mV();
  voltage_raw = (shuntvoltage*1000)/1000;
  
  return voltage_raw;
}

/*returns current mA from ina219 sensors*/
float get_current_raw(void){  
   ina219.setCalibration_16V_400mA();
  current_raw = ina219.getCurrent_mA();
  return current_raw;
}

/*returns power mW from ina219 sensors*/
float get_power_raw(void){
  float power_raw =0;
   ina219.setCalibration_16V_400mA();
  power_raw = (current_raw)*voltage_raw;
  return power_raw;
}

/*I2C power measure*/
/*float get_voltage_raw(void){
  float shuntvoltage = 0;
  float busvoltage = 0;
  float voltage_raw = 0;

  //ina219.setCalibration_16V_400mA();

  shuntvoltage = ina219.getShuntVoltage_mV();
  busvoltage = ina219.getBusVoltage_V();
  voltage_raw = busvoltage + (shuntvoltage / 1000);
  return voltage_raw;
}

float get_current_raw(void){  
  float current_raw = 0;
  
  ina219.setCalibration_16V_400mA();
  //current_raw = ina219.getCurrent_mA();
  return current_raw;
}

float get_power_raw(void){
  float power_raw = 0;
  //ina219.setCalibration_16V_400mA();
  power_raw = ina219.getPower_mW();
  return power_raw;
}*/







