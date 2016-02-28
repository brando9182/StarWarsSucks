

/*---------------------------Constants---------------------------------------*/
static const uint8_t MOTOR_LOWEST_PULSE   = 0;
static const uint8_t MOTOR_MID_PULSE      = 127;
static const uint8_t MOTOR_HIGHEST_PULSE  = 255;

static const uint8_t LINE_SENSOR_THRSHLD  = 200;  //tentative value
static const uint8_t TOKEN_SENSOR_THRSHLD = 250; //1k pull-up resistor, tentative

/*---------------------------Definitions-------------------------------------*/
//Pin declarations
#define MOTOR_DIRECTION_PIN_1 3
#define MOTOR_DIRECTION_PIN_2 5
#define MOTOR_ENABLE_PIN_1    2
#define MOTOR_ENABLE_PIN_2    4

//General declarations
#define DEBOUNCE_LENGTH       1  //min stability period, measured in milliseconds
#define INDICATOR_LED_NUM     16
#define INDICATOR_PULSE       5
#define COMPASS_ADDRESS       0x1E
#define MOTOR_TOP_SPEED       500

/*---------------------------Module Variables--------------------------------*/
static unsigned char output_pin;
static unsigned int remaining_toggles;
static unsigned char ticks_per_interrupt;

/*---------------------------Public Function Definitions---------------------*/

void intializeMotors (void) {
  pinMode(MOTOR_DIRECTION_PIN_1, OUTPUT);
  pinMode(MOTOR_DIRECTION_PIN_2, OUTPUT);
  pinMode(MOTOR_ENABLE_PIN_1, OUTPUT);
  pinMode(MOTOR_ENABLE_PIN_2, OUTPUT);
  
  digitalWrite(MOTOR_ENABLE_PIN_1, HIGH); //set intially off

}

 void drive_motor_direction_toggle (uint8_t motorNumber) {
 if ((motorNumber = 0) & !digitalRead(MOTOR_DIRECTION_PIN_1)) digitalWrite(MOTOR_DIRECTION_PIN_1, HIGH);
  if ((motorNumber = 0) & digitalRead(MOTOR_DIRECTION_PIN_1)) digitalWrite(MOTOR_DIRECTION_PIN_1, LOW);
  if ((motorNumber = 1) & !digitalRead(MOTOR_DIRECTION_PIN_2)) digitalWrite(MOTOR_DIRECTION_PIN_2, HIGH);
  if ((motorNumber = 1) & digitalRead(MOTOR_DIRECTION_PIN_2)) digitalWrite(MOTOR_DIRECTION_PIN_2, LOW);
}

//dont want to wasste a pin
//void stop_drive_motor (uint8_t motorNumber) {
//  if (motorNumber = 0) analogWrite(MOTOR_ENABLE_PIN_1, 127);
//  if (motorNumber = 1) analogWrite(MOTOR_ENABLE_PIN_2, 127);
//}

void set_motor_speed (uint8_t motorNumber, uint8_t motorSpeed) {
  uint8_t pulseLength;
  if ((motorNumber = 0) & !digitalRead(MOTOR_DIRECTION_PIN_1)) {
    pulseLength = map(motorSpeed, 0, MOTOR_TOP_SPEED, MOTOR_MID_PULSE, MOTOR_LOWEST_PULSE);
    analogWrite(MOTOR_ENABLE_PIN_1, pulseLength);
  }
  if ((motorNumber = 1) & !digitalRead(MOTOR_DIRECTION_PIN_2)) {
    pulseLength = map(motorSpeed, 0, MOTOR_TOP_SPEED, MOTOR_MID_PULSE, MOTOR_LOWEST_PULSE);
    analogWrite(MOTOR_ENABLE_PIN_2, pulseLength);
  }
  if ((motorNumber = 0) & digitalRead(MOTOR_DIRECTION_PIN_1)) {
    pulseLength = map(motorSpeed, 0, MOTOR_TOP_SPEED, MOTOR_MID_PULSE, MOTOR_HIGHEST_PULSE);
    analogWrite(MOTOR_ENABLE_PIN_1, pulseLength);
  }
  if ((motorNumber = 1) & digitalRead(MOTOR_DIRECTION_PIN_2)) {
    pulseLength = map(motorSpeed, 0, MOTOR_TOP_SPEED, MOTOR_MID_PULSE, MOTOR_HIGHEST_PULSE);
    analogWrite(MOTOR_ENABLE_PIN_2, pulseLength);
  }
}


