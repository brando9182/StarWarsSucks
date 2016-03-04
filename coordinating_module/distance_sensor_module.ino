//MODULE IS FULLY FUNCTIONING/DEBUGGED (3/3), NHS
/*-----------------------------Includes--------------------------------------*/
/*---------------------------Definitions-------------------------------------*/
/*---------------------------Constants---------------------------------------*/
static const char LONG_RANGE = 0;
static const char SHORT_RANGE = 1;
static const char LONG_RANGE_BACK = 0;
static const char LONG_RANGE_FRONT = 1;
static const uint8_t SHORT_DISTANCE_MAP_MAX_INDEX = 75;
static const uint8_t LONG_DISTANCE_MAP_MAX_INDEX = 68;
static const uint8_t SHORT_DISTANCE_MAP_START = 3;        //units in centimeters
static const float SHORT_DISTANCE_MAP_INCREMENT = 0.5;  //units in centimeters
static const uint8_t LONG_DISTANCE_MAP_START = 15;        //units in centimeters
static const uint8_t LONG_DISTANCE_MAP_INCREMENT = 2;     //units in centimeters
static const uint16_t SHORT_DISTANCE_MAPPING [76] = {626, 583, 543, 506, 472, 441, 413, 387, 363, 341, 321, 303, 287, 272,
                                                    259, 246, 235, 225, 216, 207, 200, 193, 187, 181, 175, 170, 166, 161,
                                                    157, 153, 150, 146, 143, 140, 136, 133, 130, 127, 124, 121, 118, 116,
                                                    113, 110, 107, 105, 102, 100, 97, 95, 93, 91, 89, 87, 85, 84, 82, 81, 
                                                    80, 79, 78, 77, 76, 76, 75, 75, 74, 73, 72, 72, 70, 69, 67, 65, 62};
static const uint16_t LONG_DISTANCE_MAPPING [69] =  {568, 545, 523, 500, 478, 457, 435, 415, 395, 377, 359, 342, 326, 311,
                                                    297, 283, 271, 260, 249, 240, 231, 223, 215, 208, 202, 196, 191, 186,
                                                    182, 178, 174, 170, 167, 163, 160, 157, 154, 151, 148, 145, 142, 139,
                                                    137, 134, 131, 128, 126, 123, 120, 118, 116, 113, 111, 110, 108, 106,
                                                    105, 104, 103, 102, 101, 100, 100, 99, 98, 97, 96, 94, 91};

/*---------------------------Module Variables--------------------------------*/
/*-----------------------------Public Functions------------------------------*/
//CONFIRMED WORKING (3/3), NHS
void init_distance_sensor (void){
}

//CONFIRMED WORKING (3/3), NHS
//Returns distance in centimeters
uint8_t front_distance_sensor (void){
  uint16_t rawValue = analogRead(LONG_DISTANCE_SENSOR_PIN_0);
  return (analogToCMMapping (LONG_RANGE, rawValue));
}

//CONFIRMED WORKING (3/3), NHS
//Returns distance in centimeters
uint8_t back_distance_sensor (void){
  uint16_t rawValue = analogRead(LONG_DISTANCE_SENSOR_PIN_1);
  return (analogToCMMapping (LONG_RANGE, rawValue));
}

//CONFIRMED WORKING (3/3), NHS
//Returns distance in centimeters
uint8_t side_distance_sensor (void){
  uint16_t rawValue = analogRead(SHORT_DISTANCE_SENSOR_PIN);
  return (analogToCMMapping (SHORT_RANGE, rawValue));
}

/*-----------------------------Helper Functions------------------------------*/
//CONFIRMED WORKING (3/3), NHS
static uint8_t analogToCMMapping (char sensorType, uint16_t analogValue) {
  uint8_t curIndex = 0;
  if (sensorType == LONG_RANGE) {
    while ((analogValue < LONG_DISTANCE_MAPPING[curIndex]) && (curIndex < LONG_DISTANCE_MAP_MAX_INDEX)) curIndex++;
    return ((uint8_t)(LONG_DISTANCE_MAP_START + LONG_DISTANCE_MAP_INCREMENT*curIndex));
  }
  if (sensorType == SHORT_RANGE) {
    while ((analogValue < SHORT_DISTANCE_MAPPING[curIndex])&& (curIndex < SHORT_DISTANCE_MAP_MAX_INDEX)) curIndex++;
    return ((uint8_t)(SHORT_DISTANCE_MAP_START + SHORT_DISTANCE_MAP_INCREMENT*curIndex));
  }
}

