/*-----------------------------Includes--------------------------------------*/
/*---------------------------Definitions-------------------------------------*/
#define MOTOR_DIRECTION_PIN_1   6
#define MOTOR_ENABLE_PIN_1      5
#define MOTOR_DIRECTION_PIN_2   4
#define MOTOR_ENABLE_PIN_2      12

/*---------------------------Constants---------------------------------------*/
static const uint8_t MOTOR_LOWEST_PULSE   = 0;
static const uint8_t MOTOR_MID_PULSE      = 127;
static const uint8_t MOTOR_HIGHEST_PULSE  = 255;

/*---------------------------Module Variables--------------------------------*/
/*-----------------------------Public Functions------------------------------*/
void init_motors (void) {
  pinMode(MOTOR_DIRECTION_PIN_1, OUTPUT);
  pinMode(MOTOR_DIRECTION_PIN_2, OUTPUT);
  pinMode(MOTOR_ENABLE_PIN_1, OUTPUT);
  pinMode(MOTOR_ENABLE_PIN_2, OUTPUT);

  digitalWrite(MOTOR_DIRECTION_PIN_1, HIGH); //set to one direction 
  digitalWrite(MOTOR_DIRECTION_PIN_2, HIGH); //set to one direction 
  digitalWrite(MOTOR_ENABLE_PIN_1, LOW); 
  digitalWrite(MOTOR_ENABLE_PIN_2, LOW);  
}

 void drive_motor_direction_toggle (uint8_t motorNumber) {
 if ((motorNumber = 0) & !digitalRead(MOTOR_DIRECTION_PIN_1)) digitalWrite(MOTOR_DIRECTION_PIN_1, HIGH);
  if ((motorNumber = 0) & digitalRead(MOTOR_DIRECTION_PIN_1)) digitalWrite(MOTOR_DIRECTION_PIN_1, LOW);
  if ((motorNumber = 1) & !digitalRead(MOTOR_DIRECTION_PIN_2)) digitalWrite(MOTOR_DIRECTION_PIN_2, HIGH);
  if ((motorNumber = 1) & digitalRead(MOTOR_DIRECTION_PIN_2)) digitalWrite(MOTOR_DIRECTION_PIN_2, LOW);
}


void stop_drive_motor (uint8_t motorNumber) {
  if (motorNumber = 0) analogWrite(MOTOR_ENABLE_PIN_1, 127);
  if (motorNumber = 1) analogWrite(MOTOR_ENABLE_PIN_2, 127);
}

void set_motor_speed (uint8_t motorNumber, uint8_t motorSpeed) {
  uint8_t pulseLength;
  if(motorSpeed > 255) motorSpeed = 255; //saturate
  //spinning one direction
  if ((motorNumber == 0) && !digitalRead(MOTOR_DIRECTION_PIN_1)) {
    analogWrite(MOTOR_ENABLE_PIN_1, motorSpeed);
  }
  if ((motorNumber == 1) && !digitalRead(MOTOR_DIRECTION_PIN_2)) {
    analogWrite(MOTOR_ENABLE_PIN_2, motorSpeed);
  }
  
  //spinning the other direction
  if ((motorNumber == 0) && digitalRead(MOTOR_DIRECTION_PIN_1)) {
    analogWrite(MOTOR_ENABLE_PIN_1, motorSpeed);
  }
  if ((motorNumber == 1) && digitalRead(MOTOR_DIRECTION_PIN_2)) {
    analogWrite(MOTOR_ENABLE_PIN_2, motorSpeed);
  }
}

