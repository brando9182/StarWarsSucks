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
#define TIMER_DEPLOY                4
#define DEPLOY_PULSE                500
#define TIMER_BACKUP                14
#define BACKUP_PULSE                100
#define DRIVE_SPEED                 70
#define LINE_SPEED                  80
#define SIDE_BIN_DISTANCE           18
#define BACK_ORIENT_DISTANCE        30

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

static const float ARCH = .30;
static const float LINE_FOLLOWING_RATIO = .1; //the lower the less jittery
static const float START_ARCHING_DISTANCE = 45;

/*---------------------------Module Variables--------------------------------*/
uint8_t state;
uint8_t back_previous = BACK_ORIENT_DISTANCE + 1;
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
  //init_token_deploy();
  init_token_sensors();
  deployment_home();
  start_ending_timer();
  indicator_clear();
}

/*-----------------------State Machine Coordinator---------------------------*/
void loop() {
  //start_up();
  Serial.println(state);
  indicator_clear();
  indicator_LED_on(state);
  switch (state) {
    case (STATE_1):
      if (buttonEvent()) {
        T1_2 ();
        deployment_home();
      } else {
        TX_1 ();
      }
    break;
    case (STATE_2):
      if (orientedCorrectly()) {
        T2_3 ();
      } else if (competition_ended() | buttonEvent()) {
        Serial.println("back");
        TX_1 ();
      } else {
        T2_2 ();
      }
    break;
    case (STATE_3):
      if (line_under_right ()) {
        //hit line for first time
        T3_4 ();
      } else if (buttonEvent() | competition_ended()) {
        TX_1 ();
      } else {
        T3_3 ();
      }
    break;
    case (STATE_4):
      if (line_under_rear()) {
        T4_5 ();
      } else if (buttonEvent() | competition_ended()) {
        TX_1 ();
      } else {
        T4_4 ();
      }
    break;
    //states 4 and 5 are line following
    case (STATE_5):
      if(back_distance_sensor() < 40){
        T5_7();
      }else if(binTrigger()){
          deploy_tokens(1);
      }
      if (line_under_rear()) {
        T5_6 ();
      } else if (buttonEvent() | competition_ended()) {
        TX_1 ();
      } else {
        T5_5 ();
      }
    break;
    case (STATE_6):
      //end of line
      if(back_distance_sensor() < 40){
        T6_7();
      }else if(binTrigger()){
          deploy_tokens(1);
      } else if (line_under_right() && !line_under_rear()){
        T6_5 ();
      } else if (buttonEvent() | competition_ended()) {
        TX_1 ();
      } else{
        T6_6 ();
      }
    break;
    //states 7 and 8 are also line following
    case (STATE_7):
      if(line_under_right()){
        T7_8();
      } else if (buttonEvent() | competition_ended()) {
        TX_1 ();
      } else {
        T7_7();
      }
    break;
    case (STATE_8):
      if(line_under_rear() && !line_under_right()){
        T8_7();
      }
      if (buttonEvent() | competition_ended()) {
        TX_1 ();
      } else {
        T8_8();
      }
      break;
    default:
      state = STATE_1;
    break;
  }
}

/*---------------------------Transition Functions----------------------------*/
static void TX_1 (void){
  stop_motors ();
  deployment_home ();
  state = STATE_1;
}

static void T1_1 (void) {
  state = STATE_1;
}

static void T1_2 (void) {
  start_ending_timer ();
  deployment_home ();
  state = STATE_2;
}

static void T2_2 (void) {
  drive (-DRIVE_SPEED, DRIVE_SPEED);
  state = STATE_2;
}

static void T2_3 (void) {
  state = STATE_3;
}

static void T3_3 (void) {
  if(back_distance_sensor() < START_ARCHING_DISTANCE){
    drive(-DRIVE_SPEED, -(DRIVE_SPEED * ARCH) );
  } else{
    drive(-(DRIVE_SPEED + 2), -DRIVE_SPEED);  //temp
  }
  state = STATE_3;
}

static void T3_4 (void) {
  TMRArd_InitTimer(TIMER_BACKUP, BACKUP_PULSE);
  state = STATE_4;
}

static void T4_5 (void) {
  state = STATE_5;
}

static void T4_4 (void) {
  drive(-LINE_SPEED, 0);
  state = STATE_4;
}

static void T5_5 (void) {
  drive (-LINE_SPEED, -LINE_SPEED * LINE_FOLLOWING_RATIO);
  state = STATE_5;
}

static void T5_6 (void) {
  stop_motors();
  state = STATE_6;
}

static void T5_7 (void) {
  state = STATE_7;
}

static void T6_7 (void) {
  state = STATE_7;
}

static void T6_6 (void) {
  drive (-LINE_SPEED * LINE_FOLLOWING_RATIO, -LINE_SPEED);
  state = STATE_6;
}

static void T6_5 (void){
  state = STATE_5;
}

static void T7_6(void){
  indicator_clear();
  state = STATE_6;//change line following ratio
}

static void T7_7 (void) {
  drive(-LINE_SPEED, 0);
  state = STATE_7;
}

static void T7_8 (void) {
  state = STATE_8;
}

static void T8_8 (void) {
  drive(0, -LINE_SPEED);
  state = STATE_8;
}

static void T8_7 (void) {
  state = STATE_7;
}

/*-----------------------------Helper Functions------------------------------*/
static bool orientedCorrectly (void) {
  uint8_t back_current = back_distance_sensor();
  if ((back_current > BACK_ORIENT_DISTANCE) && (back_previous < BACK_ORIENT_DISTANCE)) {
    back_previous = back_current;
    return true;
  }
  back_previous = back_current;
  return false;
}

static bool binTrigger (void) {
  uint8_t side_current = side_distance_sensor();
  if ((side_current > SIDE_BIN_DISTANCE) && (side_previous < SIDE_BIN_DISTANCE) && TMRArd_IsTimerExpired(TIMER_DEPLOY)) {
    //indicator_blanket_set(50,0,0,0);
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

int miniState = 3;
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

