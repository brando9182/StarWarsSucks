/*-----------------------------Includes--------------------------------------*/
/*---------------------------Definitions-------------------------------------*/
#define LINE_SENSOR_PIN_0   A0
#define LINE_SENSOR_PIN_1   A1
#define LINE_SENSOR_PIN_2   A2
#define LINE_SENSOR_THRSHLD 200 //tentative value

/*---------------------------Constants---------------------------------------*/
/*---------------------------Module Variables--------------------------------*/

/*-----------------------------Public Functions------------------------------*/
bool line_below_sensor (uint8_t sensor_number) {
  if ((sensor_number == 0) && (analogRead(LINE_SENSOR_PIN_0) > LINE_SENSOR_THRSHLD)) return true;
  if ((sensor_number == 1) && (analogRead(LINE_SENSOR_PIN_1) > LINE_SENSOR_THRSHLD)) return true;
  if ((sensor_number == 2) && (analogRead(LINE_SENSOR_PIN_2) > LINE_SENSOR_THRSHLD)) return true;
  return false;
}
