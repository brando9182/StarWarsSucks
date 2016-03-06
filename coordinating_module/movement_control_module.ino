//MODULE IS FULLY FUNCTIONING/DEBUGGED (3/3), NHS
//Find offset still required
/*-----------------------------Includes--------------------------------------*/
/*---------------------------Definitions-------------------------------------*/
#define MAX_SPEED               100


/*---------------------------Constants---------------------------------------*/
const char FORWARD                        = 0;
const char REVERSE                        = 1;
const char RIGHT_MOTOR                    = 0;
const char LEFT_MOTOR                     = 1;
static const uint8_t MAX_PULSE            = 255;
//this is a multiplier gets us a slope of .08 leftward (where 0 is perfectly straight)
//right motor * motor offset = left motor
static const float MOTOR_OFFSET         = 1.045; 

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
  
  digitalWrite(MOTOR_ENABLE_LEFT, HIGH);
  digitalWrite(MOTOR_ENABLE_RIGHT, HIGH);
  analogWrite(MOTOR_DIRECTION_LEFT, 128 * MOTOR_OFFSET);
  analogWrite(MOTOR_DIRECTION_RIGHT, 125);
}

static void drive(int8_t leftMotorSpeed, int8_t rightMotorSpeed){
  if(leftMotorSpeed < 0){
    set_motor_speed(LEFT_MOTOR, abs(leftMotorSpeed), REVERSE);
  } else {
    set_motor_speed(LEFT_MOTOR, leftMotorSpeed, FORWARD);
  }
    if(rightMotorSpeed < 0){
    set_motor_speed(RIGHT_MOTOR, abs(rightMotorSpeed), REVERSE);
  } else {
    set_motor_speed(RIGHT_MOTOR, rightMotorSpeed, FORWARD);
  }
}

//CONFIRMED WORKING (3/3), NHS
void stop_motors (void) {
  set_motor_speed (RIGHT_MOTOR, 0, FORWARD);
  set_motor_speed (LEFT_MOTOR, 0, FORWARD);
}

//CONFIRMED WORKING (3/3), NHS
static void set_motor_speed (char motor, uint8_t motorSpeed, uint8_t motorDirection) {
  uint8_t pulseLength = 0;
  if (motor == LEFT_MOTOR){
    if(motorDirection == FORWARD){
          pulseLength = map(motorSpeed, 0, MAX_SPEED, MAX_PULSE/2, MAX_PULSE);
    }
    else if(motorDirection == REVERSE){
          pulseLength = 125 - map(motorSpeed, 0, MAX_SPEED, 0, MAX_PULSE/2);
    }
    analogWrite(MOTOR_DIRECTION_LEFT, pulseLength);
  }
  if (motor == RIGHT_MOTOR){
    if(motorDirection == FORWARD){
          pulseLength = map(motorSpeed, 0, MAX_SPEED, MAX_PULSE/2, MAX_PULSE);
    }
    else if(motorDirection == REVERSE){
          pulseLength = 125 - map(motorSpeed, 0, MAX_SPEED, 0, MAX_PULSE/2);
    }
    analogWrite(MOTOR_DIRECTION_RIGHT, pulseLength * MOTOR_OFFSET );
  }
}

