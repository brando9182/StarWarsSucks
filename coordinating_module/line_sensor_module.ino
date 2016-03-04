//MODULE IS FULLY FUNCTIONING/DEBUGGED (3/3), NHS
/*-----------------------------Includes--------------------------------------*/
/*---------------------------Definitions-------------------------------------*/
#define LINE_SENSOR_THRSHLD 950

/*---------------------------Constants---------------------------------------*/
/*---------------------------Module Variables--------------------------------*/
/*-----------------------------Public Functions------------------------------*/
//CONFIRMED WORKING (3/3), NHS
void init_line_sensor (void) {
}

//CONFIRMED WORKING (3/3), NHS
bool line_under_left (void) {
  if (analogRead(LINE_SENSOR_PIN_2) > LINE_SENSOR_THRSHLD) return true;
  return false;
}

//CONFIRMED WORKING (3/3), NHS
bool line_under_right (void) {
  if (analogRead(LINE_SENSOR_PIN_0) > LINE_SENSOR_THRSHLD) return true;
  return false;
}

//CONFIRMED WORKING (3/3), NHS
bool line_under_center (void) {
  if (analogRead(LINE_SENSOR_PIN_1) > LINE_SENSOR_THRSHLD) return true;
  return false;
}
