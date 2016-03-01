/*-----------------------------Includes--------------------------------------*/
/*---------------------------Definitions-------------------------------------*/
//#define LONG_DISTANCE_SENSOR_PIN_0  A0
//#define LONG_DISTANCE_SENSOR_PIN_1  A1
//#define SHORT_DISTANCE_SENSOR_PIN   A2

/*---------------------------Constants---------------------------------------*/
/*---------------------------Module Variables--------------------------------*/
/*-----------------------------Public Functions------------------------------*/
void init_distance_sensor (void){
}

//Returns distance (once calibrated in cm) [WORK IN PROGRESS]
uint8_t long_distance_sensor_report (uint8_t sensorNumber){
  uint8_t rawValue;
  if (sensorNumber == 0) rawValue = analogRead(LONG_DISTANCE_SENSOR_PIN_0);
  if (sensorNumber == 1) rawValue = analogRead(LONG_DISTANCE_SENSOR_PIN_1);
  
  return 0; //Extract mapping function from datasheet
}

//Returns distance (once calibrated in cm) [WORK IN PROGRESS]
uint8_t short_distance_sensor_report (void){
  uint8_t rawValue = analogRead(SHORT_DISTANCE_SENSOR_PIN);
  
  return 0; //Extract mapping function from datasheet
}

