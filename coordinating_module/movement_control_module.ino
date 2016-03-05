//MODULE IS FULLY FUNCTIONING/DEBUGGED (3/3), NHS
//Find offset still required
/*-----------------------------Includes--------------------------------------*/
/*---------------------------Definitions-------------------------------------*/
#define MAX_SPEED               100

/*---------------------------Constants---------------------------------------*/
static const char FORWARD                 = 0;
static const char REVERSE                 = 1;
char RIGHT_MOTOR             = 0;
char LEFT_MOTOR              = 1;
static const uint8_t MAX_PULSE            = 255;
static const uint8_t MOTOR_OFFSET         = 12; //TODO: measure PWM offset

/*---------------------------Module Variables--------------------------------*/
uint8_t left_motor_speed = 0;
uint8_t right_motor_speed = 0;
/*-----------------------------Public Functions------------------------------*/
//CONFIRMED WORKING (3/3), NHS
void init_motors (void) {
  pinMode(MOTOR_ENABLE_LEFT, OUTPUT);
  pinMode(MOTOR_ENABLE_RIGHT, OUTPUT);
  pinMode(MOTOR_DIRECTION_LEFT, OUTPUT);
  pinMode(MOTOR_DIRECTION_RIGHT, OUTPUT);
  
  digitalWrite(MOTOR_DIRECTION_LEFT, HIGH);
  digitalWrite(MOTOR_DIRECTION_RIGHT, HIGH);
  stop_motors();
}

//CONFIRMED WORKING (3/3), NHS
//Controls motor speeds and direction with full forward speed being `100` and full negative being `-100`
void drive (int8_t leftMotorSpeed, int8_t rightMotorSpeed) {
  if (leftMotorSpeed < 0) set_motor_direction(LEFT_MOTOR, REVERSE);
  if (leftMotorSpeed > 0) set_motor_direction(LEFT_MOTOR, FORWARD);
  
  if (rightMotorSpeed < 0) set_motor_direction(RIGHT_MOTOR, REVERSE);
  if (rightMotorSpeed > 0) set_motor_direction(RIGHT_MOTOR, FORWARD);
  set_motor_speed(RIGHT_MOTOR, abs(rightMotorSpeed));
  right_motor_speed = abs(rightMotorSpeed);
  set_motor_speed(LEFT_MOTOR, abs(leftMotorSpeed) - MOTOR_OFFSET);
  left_motor_speed = abs(leftMotorSpeed) - MOTOR_OFFSET;
}

//CONFIRMED WORKING (3/3), NHS
void stop_motors (void) {
  set_motor_speed (RIGHT_MOTOR, 0);
  set_motor_speed (LEFT_MOTOR, 0);
}

/*-----------------------------Helper Functions------------------------------*/
//CONFIRMED WORKING (3/3), NHS
static void set_motor_direction(char motor, char motor_direction){
  if (motor == LEFT_MOTOR) {
    if (motor_direction == FORWARD) digitalWrite(MOTOR_DIRECTION_LEFT, HIGH);
    if (motor_direction == REVERSE) digitalWrite(MOTOR_DIRECTION_LEFT, LOW);
  }
  if (motor == RIGHT_MOTOR) {
    if (motor_direction == FORWARD) digitalWrite(MOTOR_DIRECTION_RIGHT, HIGH);
    if (motor_direction == REVERSE) digitalWrite(MOTOR_DIRECTION_RIGHT, LOW);
  }
}

//CONFIRMED WORKING (3/3), NHS
static void set_motor_speed (char motor, uint8_t motorSpeed) {
  uint8_t pulseLength = map(motorSpeed, 0, MAX_SPEED, 0, MAX_PULSE);
  if (motor == RIGHT_MOTOR) analogWrite(MOTOR_ENABLE_RIGHT, pulseLength);
  if (motor == LEFT_MOTOR) analogWrite(MOTOR_ENABLE_LEFT, pulseLength);
}

