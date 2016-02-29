/*-----------------------------Includes--------------------------------------*/
/*---------------------------Definitions-------------------------------------*/
#define TOKEN_SENSOR_PIN_0    7
#define TOKEN_SENSOR_PIN_1    8
#define TOKEN_SENSOR_PIN_2    9
#define TOKEN_SENSOR_PIN_3    10
#define TOKEN_SENSOR_NUM      4

/*---------------------------Constants---------------------------------------*/
/*---------------------------Module Variables--------------------------------*/
uint8_t token_curr_num = 1;
uint8_t token_order [TOKEN_SENSOR_NUM];

/*-----------------------------Public Functions------------------------------*/
void init_token_sensors (void) {
  pinMode(TOKEN_SENSOR_PIN_0, INPUT);
  pinMode(TOKEN_SENSOR_PIN_1, INPUT);
  pinMode(TOKEN_SENSOR_PIN_2, INPUT);
  pinMode(TOKEN_SENSOR_PIN_3, INPUT);
}

//Returns whether or not there is a token currently in a slot (`true` if yes, `false` if not)>
//The threshold value between a line and the reflective ground is determined by TOKEN_SENSOR_THRSHLD 
//(the higher the value, the less light is reaching the sensor). The parameter lets the user choose which
//line sensor they are querrying (0 through 3).
bool token_in_slot (uint8_t sensor_number) {
  if ((sensor_number == 0) & !digitalRead(TOKEN_SENSOR_PIN_0)) return true;
  if ((sensor_number == 1) & !digitalRead(TOKEN_SENSOR_PIN_1)) return true;
  if ((sensor_number == 2) & !digitalRead(TOKEN_SENSOR_PIN_2)) return true;
  if ((sensor_number == 3) & !digitalRead(TOKEN_SENSOR_PIN_3)) return true;
  return false;
}

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

