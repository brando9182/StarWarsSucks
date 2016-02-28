

/*---------------------------Constants---------------------------------------*/
static const uint8_t MOTOR_LOWEST_PULSE   = 0;
static const uint8_t MOTOR_MID_PULSE      = 127;
static const uint8_t MOTOR_HIGHEST_PULSE  = 255;

/*---------------------------Definitions-------------------------------------*/
//Pin declarations
#define MOTOR_DIRECTION_PIN_1 2
#define MOTOR_DIRECTION_PIN_2 4
#define MOTOR_ENABLE_PIN_1    3
#define MOTOR_ENABLE_PIN_2    5

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

//analog write 0 - 255, no need for remapping


