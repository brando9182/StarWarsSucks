/*-----------------------------Includes--------------------------------------*/
#include <Timers.h>

/*---------------------------PIN Definitions---------------------------------*/
#define DEPLOYMENT_SERVO_PIN        2
#define MOTOR_ENABLE_RIGHT          12
#define MOTOR_DIRECTION_RIGHT       3
#define MOTOR_ENABLE_LEFT           6
#define MOTOR_DIRECTION_LEFT        5
#define TOKEN_SENSOR_PIN_0          7
#define TOKEN_SENSOR_PIN_1          9
#define TOKEN_SENSOR_PIN_2          8
#define TOKEN_SENSOR_PIN_3          10
#define BUTTON_PIN                  11
#define LINE_SENSOR_PIN_2           A5
#define INDICATOR_PIN               13
#define LONG_DISTANCE_SENSOR_PIN_0  A0
#define LONG_DISTANCE_SENSOR_PIN_1  A1
#define SHORT_DISTANCE_SENSOR_PIN   A2
#define LINE_SENSOR_PIN_0           A3
#define LINE_SENSOR_PIN_1           A4

/*--------------------------------Definitions----------------------------------*/
#define TIMER_DEPLOY                9
#define DEPLOY_PULSE                500
#define TIMER_BACKUP                14
#define BACKUP_PULSE                100
#define DRIVE_SPEED                 30
#define LINE_SPEED                  30
#define SIDE_BIN_DISTANCE           18
#define FRONT_ORIENT_DISTANCE       120

/*---------------------------Function prototypes-------------------------------*/
/*---------------------------Constants---------------------------------------*/
static const uint8_t STATE_1  = 1;
static const uint8_t STATE_2  = 2;
static const uint8_t STATE_3  = 3;
static const uint8_t STATE_4  = 4;
static const uint8_t STATE_5  = 5;
static const uint8_t STATE_6  = 6;
static const uint8_t STATE_7  = 7;
static const uint8_t STATE_8  = 8;

/*---------------------------Module Variables--------------------------------*/
uint8_t state;
uint8_t front_previous = FRONT_ORIENT_DISTANCE + 1;
uint8_t side_previous;
uint8_t button_previous;
extern const char FORWARD;
extern const char REVERSE;
extern const char RIGHT_MOTOR;
extern const char LEFT_MOTOR;
/*---------------------------Start-up Sequence-------------------------------*/
void setup() {
  Serial.begin(9600);
  init_ending_timer();
  init_button();
  init_distance_sensor();
  init_ending_timer();
  init_light_ring();
  init_line_sensor();
  init_motors();
  init_token_deploy();
  init_token_sensors();
  deployment_home();
  start_ending_timer();
  indicator_clear();
}

/*-----------------------State Machine Coordinator---------------------------*/
void loop() {
  //start_up();
  Serial.println(state);
  switch (state) {
    case (STATE_1):
      if (buttonEvent()) {
        T1_2 ();
        deployment_home();
      } else {
        T1_1 ();
      }
    break;
    case (STATE_2):
      if (orientedCorrectly()) {
        T2_3 ();
      } else if (competition_ended() | buttonEvent()) {
        Serial.println("back");
        T2_1 ();
      } else {
        T2_2 ();
      }
    break;
    case (STATE_3):
      if (line_under_right()) {
        T3_4 ();
      } else if (buttonEvent() | competition_ended()) {
        T3_1 ();
      } else {
        T3_3 ();
      }
    break;
    case (STATE_4):
      if (TMRArd_IsTimerExpired(TIMER_BACKUP)) {
        T4_5 ();
      } else if (buttonEvent() | competition_ended()) {
        T4_1 ();
      } else {
        T4_4 ();
      }
    break;
    case (STATE_5):
      if (line_under_rear()) {
        T5_6 ();
      } else if (buttonEvent() | competition_ended()) {
        T5_1 ();
      } else {
        T5_5 ();
      }
    break;
    case (STATE_6):
      if (line_under_left()){
        T6_7 ();
      } else if (buttonEvent() | competition_ended()) {
        T6_1 ();
      } else{
        T6_7 ();
      }
    break;
    case (STATE_7):
      if (binTrigger()) {
        T7_8();
      } else if (buttonEvent() | competition_ended()) {
        T7_1 ();
      } else {
        T7_7();
      }
    break;
    case (STATE_8):
      if (buttonEvent() | competition_ended()) {
        T8_1 ();
      } else {
        T8_7();
      }
//    case (STATE_9):
//      //delay a bit     
    default:
      state = STATE_1;
    break;
  }
}

/*---------------------------Transition Functions----------------------------*/
static void T1_1 (void) {
  indicator_pulse();
  state = STATE_1;
}

static void T1_2 (void) {
  start_ending_timer ();
  indicator_clear ();
  deployment_home ();
  indicator_blanket_set(50, 50, 0, 0);
  state = STATE_2;
}

static void T2_1 (void) {
  stop_motors ();
  deployment_home ();
  state = STATE_1;
}

static void T2_2 (void) {
  drive (DRIVE_SPEED, -DRIVE_SPEED);
  state = STATE_2;
}

static void T2_3 (void) {
  indicator_blanket_set(50, 0, 50, 0);
  state = STATE_3;
}

static void T3_1 (void) {
  stop_motors ();
  deployment_home ();
  state = STATE_1;
}

static void T3_3 (void) {
  drive(DRIVE_SPEED * 1.1, DRIVE_SPEED);  //temp
  state = STATE_3;
}

static void T3_4 (void) {
  TMRArd_InitTimer(TIMER_BACKUP, BACKUP_PULSE);
  indicator_blanket_set(0, 0, 50, 50);
  state = STATE_4;
}

static void T4_1 (void) {
  stop_motors ();
  deployment_home ();
  state = STATE_1;
}

static void T4_5 (void) {
  indicator_blanket_set(10, 10, 10, 10);
  state = STATE_5;
}

static void T4_4 (void) {
  drive(DRIVE_SPEED +20, DRIVE_SPEED +20);
  state = STATE_4;
}

static void T5_5 (void) {
  drive (DRIVE_SPEED, 0);
  state = STATE_5;
}

static void T5_1 (void) {
  stop_motors ();
  deployment_home ();
  state = STATE_1;
}

static void T5_6 (void) {
  stop_motors();
  indicator_blanket_set(0, 50, 0, 10);
  state = STATE_6;
}

static void T6_1 (void) {
  stop_motors ();
  deployment_home ();
  state = STATE_1;
}

static void T6_6 (void) {
  drive (DRIVE_SPEED-10, (DRIVE_SPEED-10));
  state = STATE_6;
}

static void T6_7 (void){
  drive (-(DRIVE_SPEED), -(DRIVE_SPEED-10)); 
  state = STATE_7;
}

static void T7_1 (void) {
  stop_motors ();
  deployment_home ();
  state = STATE_1;
}

static void T7_7 (void) {
  if (!line_under_rear()) {
    drive (-(LINE_SPEED-8),0);
  } else if (!line_under_rear() & !line_under_right()) {
    drive (-(LINE_SPEED-12),0);
  } else {
    drive (-(LINE_SPEED+1), -(LINE_SPEED+12));
  }
  state = STATE_7;
}

static void T7_8 (void) {
  deploy_tokens(1);
  state = STATE_8;
}

static void T8_1 (void) {
  stop_motors ();
  deployment_home ();
  state = STATE_1;
}

static void T8_7 (void) {
  state = STATE_7;
}

/*-----------------------------Helper Functions------------------------------*/
static bool orientedCorrectly (void) {
  uint8_t front_current = front_distance_sensor();
  if ((front_current > FRONT_ORIENT_DISTANCE) && (front_previous < FRONT_ORIENT_DISTANCE)) {
    front_previous = front_current;
    return true;
  }
  front_previous = front_current;
  return false;
}

static bool binTrigger (void) {
  uint8_t side_current = side_distance_sensor();
  if ((side_current > SIDE_BIN_DISTANCE) && (side_previous < SIDE_BIN_DISTANCE) && TMRArd_IsTimerExpired(TIMER_DEPLOY)) {
    side_previous = side_current;
    TMRArd_InitTimer (TIMER_DEPLOY, DEPLOY_PULSE);
    return true;
  }
  side_previous = side_current;
  return false;
}

static bool buttonEvent (void) {
  uint8_t button_current = button_state();
  if ((button_current == 1) && (button_previous == 0)) {
     button_previous = button_current;
     return true;
  }
  button_previous = button_current;
  return false;
}

static void haltCode (void) {
  stop_motors();
  while(1);
}

int miniState = 0;
int rotSpd = 10;
void start_up(){
  while(!button_state());
  while(1){
    Serial.print("miniState");
    Serial.println(miniState);
    Serial.print("front: ");
    Serial.println(front_distance_sensor());
    Serial.print("back: ");
    Serial.println(back_distance_sensor());
    Serial.print("side: ");
    Serial.println(side_distance_sensor());
    Serial.print("front + back = ");
    Serial.println(front_distance_sensor() + back_distance_sensor());
    Serial.println("---------------");
    delay(250);
    if(miniState == 0 && (front_distance_sensor() + back_distance_sensor()) < 120){
      set_motor_speed (LEFT_MOTOR, 40, FORWARD);
      set_motor_speed (RIGHT_MOTOR, 40, FORWARD);
      miniState = 1;
    }
    //turning
    if(miniState == 1 && front_distance_sensor() < 100){
      set_motor_speed (LEFT_MOTOR, 30, FORWARD);
      set_motor_speed (RIGHT_MOTOR, 40, FORWARD);
      miniState = 2;
    }
    if(miniState == 2 && side_distance_sensor() < 4 && back_distance_sensor() < 20){
      set_motor_speed(LEFT_MOTOR, 10, FORWARD);
      set_motor_speed(RIGHT_MOTOR, 10, FORWARD);
      miniState == 3;
      //do something else
    }
    if(button_state()){
      haltCode();
    }
  }
  Serial.println("startup");
     // set_motor_speed (LEFT_MOTOR, 80, FORWARD);
     // set_motor_speed (RIGHT_MOTOR, 80, FORWARD);
  //stop_motors();
  while(1);
}

