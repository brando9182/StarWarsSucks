/*-----------------------------Includes--------------------------------------*/
/*---------------------------Definitions-------------------------------------*/
//#define LINE_SENSOR_PIN_0   A3
//#define LINE_SENSOR_PIN_1   A4
//#define LINE_SENSOR_PIN_2   A5
#define LINE_SENSOR_THRSHLD 200 //needs to be set

/*---------------------------Constants---------------------------------------*/
/*---------------------------Module Variables--------------------------------*/

/*-----------------------------Public Functions------------------------------*/
void init_line_sensor (void) {
}

bool line_below_sensor (uint8_t sensor_number) {
  if ((sensor_number == 0) && (analogRead(LINE_SENSOR_PIN_0) > LINE_SENSOR_THRSHLD)) return true;
  if ((sensor_number == 1) && (analogRead(LINE_SENSOR_PIN_1) > LINE_SENSOR_THRSHLD)) return true;
  if ((sensor_number == 2) && (analogRead(LINE_SENSOR_PIN_2) > LINE_SENSOR_THRSHLD)) return true;
  return false;
}
