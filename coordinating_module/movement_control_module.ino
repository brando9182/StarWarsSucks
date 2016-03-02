/*-----------------------------Includes--------------------------------------*/
/*---------------------------Definitions-------------------------------------*/
#define MOTOR_DIRECTION_PIN_1   6
#define MOTOR_ENABLE_PIN_1      5
#define MOTOR_DIRECTION_PIN_2   12 //originally pin 4
#define MOTOR_ENABLE_PIN_2      3 //originally pin 12
//defined in main files
//#define RIGHT_MOTOR             0
//#define LEFT_MOTOR              1
//#define FORWARD                 HIGH
//#define REVERSE                 LOW
//#define CLOCKWISE                0
//#define COUNTERCLOCKWISE        1

/*---------------------------Constants---------------------------------------*/
static const uint8_t MOTOR_LOWEST_PULSE   = 0;
static const uint8_t MOTOR_MID_PULSE      = 127;
static const uint8_t MOTOR_HIGHEST_PULSE  = 255;
//driving the motors with the same voltage will give slightly different rotational speeds
//i.e. right_votlage - C = left_voltage
static const uint8_t MOTOR_VOLTAGE_DIFFERENCE = 0;
//TODO: need to mesaure these
static const uint8_t MPS_TO_VOLTAGE = 10;
static const uint8_t MILISECONDS_PER_DEGREE = 100;  //note these two
static const uint8_t TURNING_VOLTAGE = 10;          //are codependent

/*---------------------------Module Variables--------------------------------*/
/*-----------------------------Public Functions------------------------------*/
void init_motors (void) {
  pinMode(MOTOR_DIRECTION_PIN_1, OUTPUT);
  pinMode(MOTOR_DIRECTION_PIN_2, OUTPUT);
  pinMode(MOTOR_ENABLE_PIN_1, OUTPUT);
  pinMode(MOTOR_ENABLE_PIN_2, OUTPUT);

  digitalWrite(MOTOR_DIRECTION_PIN_1, HIGH);
  digitalWrite(MOTOR_DIRECTION_PIN_2, HIGH);
  //doesn't always work the first time
  for(int i = 0; i < 5; i++){
    analogWrite(MOTOR_ENABLE_PIN_1, 255); 
  }

  for(int i = 0; i < 5; i++){
    analogWrite(MOTOR_ENABLE_PIN_2, 255);  
  }
}
/////////////////"Nicer Functions"//////////////////////////////
void drive_forward(float mps){
  uint8_t volts = mps * MPS_TO_VOLTAGE;
  
  set_motor_direction(RIGHT_MOTOR, FORWARD);
  set_motor_direction(LEFT_MOTOR, FORWARD);
  set_motor_speed(RIGHT_MOTOR, volts);
  set_motor_speed(LEFT_MOTOR, volts - MOTOR_VOLTAGE_DIFFERENCE);
}

void reverse(uint8_t mps){
  uint8_t volts = mps * MPS_TO_VOLTAGE;
  
  set_motor_direction(RIGHT_MOTOR, REVERSE);
  set_motor_direction(LEFT_MOTOR, REVERSE);
  set_motor_speed(RIGHT_MOTOR, volts);
  set_motor_speed(LEFT_MOTOR, volts - MOTOR_VOLTAGE_DIFFERENCE);
}

// You need to call this repeatedly, it will return false when done
// note static integers retain their value between calls
// also note this fucntion is super janky, look here first if something fails
bool turn(uint16_t degrees, uint16_t time, uint16_t rotating_direction){
  //record start time
  static uint8_t first_time = 0;
  static uint16_t start_time = 0;
  static uint16_t end_time = 0;
  if(first_time == 0){
    first_time = 1;
    start_time = time;
    //assuming time decreases
    end_time = time - degrees * MILISECONDS_PER_DEGREE;
    //set driving specs
    if(rotating_direction == CLOCKWISE){
      set_motor_direction(RIGHT_MOTOR, REVERSE);
      set_motor_direction(LEFT_MOTOR, FORWARD); 
    }
    else if(rotating_direction == COUNTERCLOCKWISE){
      set_motor_direction(RIGHT_MOTOR, FORWARD);
      set_motor_direction(LEFT_MOTOR, REVERSE);
    }
    set_motor_speed(RIGHT_MOTOR, TURNING_VOLTAGE);
    set_motor_speed(LEFT_MOTOR, TURNING_VOLTAGE);   
  }
  if(time > end_time){
    return false;
  }
  else{
    stop_drive_motor(RIGHT_MOTOR);
    stop_drive_motor(LEFT_MOTOR);
    first_time = 0;
    return true;
  }
  
}
/////////////////////////////////////////////////////////////
void set_motor_direction(uint8_t motorNumber, uint8_t motor_direction){
  if (motorNumber == RIGHT_MOTOR){
    if(motor_direction == FORWARD){
      digitalWrite(MOTOR_DIRECTION_PIN_1, FORWARD);
    }
    if(motor_direction == REVERSE){
      digitalWrite(MOTOR_DIRECTION_PIN_1, REVERSE);
    }
  }
  if (motorNumber == LEFT_MOTOR){
    if(motor_direction == FORWARD){
      digitalWrite(MOTOR_DIRECTION_PIN_2, FORWARD);
    }
    if(motor_direction == REVERSE){
      digitalWrite(MOTOR_DIRECTION_PIN_2, REVERSE);
    }
  }
}


 void drive_motor_direction_toggle (uint8_t motorNumber) {
  if ((motorNumber == 0) & !digitalRead(MOTOR_DIRECTION_PIN_1)) digitalWrite(MOTOR_DIRECTION_PIN_1, HIGH);
  if ((motorNumber == 0) & digitalRead(MOTOR_DIRECTION_PIN_1)) digitalWrite(MOTOR_DIRECTION_PIN_1, LOW);
  if ((motorNumber == 1) & !digitalRead(MOTOR_DIRECTION_PIN_2)) digitalWrite(MOTOR_DIRECTION_PIN_2, HIGH);
  if ((motorNumber == 1) & digitalRead(MOTOR_DIRECTION_PIN_2)) digitalWrite(MOTOR_DIRECTION_PIN_2, LOW);
}


void stop_drive_motor (uint8_t motorNumber) {
  if (motorNumber == 0) analogWrite(MOTOR_ENABLE_PIN_1, 127);
  if (motorNumber == 1) analogWrite(MOTOR_ENABLE_PIN_2, 127);
}

void set_motor_speed (uint8_t motorNumber, uint8_t volts) {
  if(volts > 12) volts = 12;
  //convert volts to pwm wave
  uint8_t pulseLength = map(volts, 0, 12, 0, 255);
  //spinning one direction
  if ((motorNumber == 0) && !digitalRead(MOTOR_DIRECTION_PIN_1)) {
    analogWrite(MOTOR_ENABLE_PIN_1, pulseLength);
  }
  if ((motorNumber == 1) && !digitalRead(MOTOR_DIRECTION_PIN_2)) {
    analogWrite(MOTOR_ENABLE_PIN_2, pulseLength);
  }
  
  //spinning the other direction
  if ((motorNumber == 0) && digitalRead(MOTOR_DIRECTION_PIN_1)) {
    analogWrite(MOTOR_ENABLE_PIN_1, pulseLength);
  }
  if ((motorNumber == 1) && digitalRead(MOTOR_DIRECTION_PIN_2)) {
    analogWrite(MOTOR_ENABLE_PIN_2, pulseLength);
  }
}

