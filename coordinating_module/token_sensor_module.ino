/*-----------------------------Includes--------------------------------------*/
/*---------------------------Definitions-------------------------------------*/
#define TOKEN_SENSOR_NUM      4

/*---------------------------Constants---------------------------------------*/
/*---------------------------Module Variables--------------------------------*/
uint8_t token_curr_num = 1;
uint8_t token_order [TOKEN_SENSOR_NUM];

/*-----------------------------Public Functions------------------------------*/
//CONFIRMED WORKING (3/3), NHS
void init_token_sensors (void) {
  pinMode(TOKEN_SENSOR_PIN_0, INPUT);
  pinMode(TOKEN_SENSOR_PIN_1, INPUT);
  pinMode(TOKEN_SENSOR_PIN_2, INPUT);
  pinMode(TOKEN_SENSOR_PIN_3, INPUT);
}

//CONFIRMED WORKING (3/3), NHS
bool token_in_slot (uint8_t sensor_number) {
  if ((sensor_number == 1) & !digitalRead(TOKEN_SENSOR_PIN_0)) return true;
  if ((sensor_number == 2) & !digitalRead(TOKEN_SENSOR_PIN_1)) return true;
  if ((sensor_number == 3) & !digitalRead(TOKEN_SENSOR_PIN_2)) return true;
  if ((sensor_number == 4) & !digitalRead(TOKEN_SENSOR_PIN_3)) return true;
  return false;
}

//uint8_t* token_report (void) {
//  return &token_order;
//}

//Call once all of the tokens have been deployed to reset the token insertion order count
void token_read_reset (void) {
  for (int i = 0; i < TOKEN_SENSOR_NUM; i++) {
    token_order [i] = 0;
  }
}

//Records and updates an array containing the insertion order of the information chips
void token_read_update (void) {
  for (int i = 0; i < TOKEN_SENSOR_NUM; i++) {
    if ((token_in_slot(i)) && (token_order[i] != 0))
    {
      token_order[i] = token_curr_num;
      token_curr_num++;
    }
  }
}

