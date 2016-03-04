//MODULE IS FULLY FUNCTIONING/DEBUGGED (3/3), NHS
/*-----------------------------Includes--------------------------------------*/
/*---------------------------Definitions-------------------------------------*/
#define TOKEN_SENSOR_NUM      4

/*---------------------------Constants---------------------------------------*/
/*---------------------------Module Variables--------------------------------*/
bool binA;
bool binB;
bool binC;
bool binD;
bool binE;
bool homed;
uint8_t previous_insertion;

/*-----------------------------Public Functions------------------------------*/
//CONFIRMED WORKING (3/3), NHS
void init_token_sensors (void) {
  pinMode(TOKEN_SENSOR_PIN_0, INPUT);
  pinMode(TOKEN_SENSOR_PIN_1, INPUT);
  pinMode(TOKEN_SENSOR_PIN_2, INPUT);
  pinMode(TOKEN_SENSOR_PIN_3, INPUT);
}

//CONFIRMED WORKING (3/3), NHS
void token_read_reset (void) {
  binA = false;
  binB = false;
  binC = false;
  binD = false;
  binE = false;
  homed = false;
  previous_insertion = 0;
}

//CONFIRMED WORKING (3/3), NHS
void bin_order_update (void) {
  uint8_t current_insertion = tokenRead();
  if (!homed) {
    uint8_t delta = previous_insertion ^ current_insertion;
    if (delta == (1 << 0)) binA = true;
    if (delta == (1 << 1)) binB = true;
    if (delta == (1 << 2)) binC = true;
//    if (delta == (1 << 3)) binD = true;
//    if (delta == (1 << 4)) binE = true;
    if (delta == (1 << 3)) homed = true;
  }
}

/*-----------------------------Helper Functions------------------------------*/
//CONFIRMED WORKING (3/3), NHS
static uint8_t tokenRead (void) {
  uint8_t tokenStatus = 0;
  for (int i = 1; i <= TOKEN_SENSOR_NUM; i++) {
    tokenStatus |= tokenInSlot(i) << (i-1);
  }
  return tokenStatus;
}

//CONFIRMED WORKING (3/3), NHS
//1 indexed
static bool tokenInSlot (uint8_t sensor_number) {
  if ((sensor_number == 1) & !digitalRead(TOKEN_SENSOR_PIN_0)) return true;
  if ((sensor_number == 2) & !digitalRead(TOKEN_SENSOR_PIN_1)) return true;
  if ((sensor_number == 3) & !digitalRead(TOKEN_SENSOR_PIN_2)) return true;
  if ((sensor_number == 4) & !digitalRead(TOKEN_SENSOR_PIN_3)) return true;
  return false;
}

