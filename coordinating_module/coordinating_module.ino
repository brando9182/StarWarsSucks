/*-----------------------------Includes--------------------------------------*/
#include <Timers.h>

/*---------------------------PIN Definitions---------------------------------*/
#define DEPLOYMENT_SERVO_PIN        2   //CONFIRMED (3/3), NHS
#define MOTOR_ENABLE_RIGHT          3
#define MOTOR_DIRECTION_RIGHT       12
#define MOTOR_ENABLE_LEFT           5
#define MOTOR_DIRECTION_LEFT        6
#define TOKEN_SENSOR_PIN_0          7   //CONFIRMED (3/3), NHS
#define TOKEN_SENSOR_PIN_1          9   //CONFIRMED (3/3), NHS
#define TOKEN_SENSOR_PIN_2          8   //CONFIRMED (3/3), NHS
#define TOKEN_SENSOR_PIN_3          10  //CONFIRMED (3/3), NHS
#define BUTTON_PIN                  11
#define LINE_SENSOR_PIN_2           A5
#define INDICATOR_PIN               13  //CONFIRMED (3/3), NHS
#define LONG_DISTANCE_SENSOR_PIN_0  A0  //Front-facing
#define LONG_DISTANCE_SENSOR_PIN_1  A1  //Back-facing
#define SHORT_DISTANCE_SENSOR_PIN   A2
#define LINE_SENSOR_PIN_0           A3
#define LINE_SENSOR_PIN_1           A4

/*--------------------------------Definitions----------------------------------*/
#define TIMER_DEPLOY            9
#define DEPLOY_PULSE            500

#define TIMER_PIVOT             10
#define PIVOT_PULSE             340

#define TIMER_OFFSET_PIVOT      15
#define OFFSET_PIVOT_PULSE      500

#define TIMER_BACKUP            14
#define BACKUP_PULSE            100

#define DEFAULT_SPEED           50

#define SIDE_BIN_DISTANCE       18
#define FRONT_ORIENT_DISTANCE   120
#define SIDE_BIN_DISTANCE       12

/*---------------------------Function prototypes-------------------------------*/
static void T1_1 (void);
static void T1_2 (void);
static void T2_1 (void);
static void T2_2 (void);
static void T2_3 (void);
static void T3_1 (void);
static void T3_3 (void);
static void T3_8 (void);
static void T8_8 (void);
static void T8_9 (void);
static void T9_1 (void);
static void T9_4 (void);
static void T4_1 (void);
static void T4_4 (void);
static void T4_5 (void);
static void T5_1 (void);
static void T5_5 (void);
static void T5_6 (void);
static void T6_6 (void);
static void T6_1 (void);
static void T6_7 (void);
static void lineFollow (void);
static bool orientedCorrectly (void);
static bool binTrigger (void);
static bool buttonEvent (void);
static void haltCode (void);

/*---------------------------Constants---------------------------------------*/
static const uint8_t STATE_1  = 0;
static const uint8_t STATE_2  = 1;
static const uint8_t STATE_3  = 2;
static const uint8_t STATE_4  = 3;
static const uint8_t STATE_5  = 4;
static const uint8_t STATE_6  = 5;
static const uint8_t STATE_7  = 6;
static const uint8_t STATE_8  = 7;
static const uint8_t STATE_9  = 8;

/*---------------------------Module Variables--------------------------------*/
uint8_t state;
uint8_t front_previous = FRONT_ORIENT_DISTANCE + 1;
uint8_t side_previous;
uint8_t button_previous;

/*-----------------------State Machine Coordinator---------------------------*/

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
  //init_compass();
}

void loop() {
//  Serial.print("Side: ");
//  Serial.print(side_distance_sensor());
//  Serial.print(",   Front: ");
//  Serial.print(front_distance_sensor());
//  Serial.print(",   Back: ");
//  Serial.println(back_distance_sensor());
//  delay(10);
//    if (binTrigger()) indicator_pulse();
//    delay(500);
//    indicator_clear();
//drive(-40,-40);
//deployment_home();

  Serial.println(state);
  switch (state) {
    case (STATE_1):
      if (buttonEvent()) {
        T1_2 ();
      } else {
        T1_1 ();
      }
    break;
    case (STATE_2):
      if (orientedCorrectly()) {
        T2_3 ();
      } else if (competition_ended() | buttonEvent()) {
        T2_1 ();
      } else {
        T2_2 ();
      }
    break;
    case (STATE_3):
      if (line_under_right()) {
        T3_8 ();
      } else if (buttonEvent() | competition_ended()) {
        T3_1 ();
      } else {
        T3_3 ();
      }
    break;
    case (STATE_8):
      if (TMRArd_IsTimerExpired(TIMER_BACKUP)) {
        T8_9 ();
      } else if (buttonEvent() | competition_ended()) {
        T8_1 ();
      } else {
        T8_8 ();
      }
    break;
    case (STATE_9):
      if (line_under_rear()) {
        haltCode();
        T9_4 ();
      } else if (buttonEvent() | competition_ended()) {
        T9_1 ();
      } else {
        T9_9 ();
      }
    break;
    case (STATE_4): //pivot
      if (TMRArd_IsTimerExpired(TIMER_OFFSET_PIVOT)) {
        T4_5 ();
      } else if (buttonEvent() | competition_ended()) {
        T4_1 ();
      } else {
        T4_4 ();
      }
    break;
    case (STATE_5): //reverse
      if (TMRArd_IsTimerExpired(TIMER_OFFSET_PIVOT)) {
        T5_6 ();
      } else if (buttonEvent() | competition_ended()) {
        T5_1 ();
      } else {
        T5_5 ();
      }
    break;
    case (STATE_6): //pivots
      if (TMRArd_IsTimerExpired(TIMER_OFFSET_PIVOT)) {
        T6_7 ();
      } else if (buttonEvent() | competition_ended()) {
        T6_1 ();
      } else {
        T6_6 ();
      }
    break;
    default:
      state = STATE_1;
    break;
  }
}


/*-----------------------------Helper Functions------------------------------*/
static void T1_1 (void) {
  indicator_pulse ();
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
  drive (DEFAULT_SPEED-10, -DEFAULT_SPEED);
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
  drive(DEFAULT_SPEED, DEFAULT_SPEED);  //temp
  state = STATE_3;
}

static void T3_8 (void) {
  TMRArd_InitTimer(TIMER_BACKUP, BACKUP_PULSE);
  indicator_blanket_set(0, 0, 50, 50);
  state = STATE_8;
}

static void T8_1 (void) {
  stop_motors ();
  deployment_home ();
  state = STATE_1;
}

static void T8_9 (void) {
  indicator_blanket_set(10, 10, 10, 10);
  state = STATE_9;
}

static void T8_8 (void) {
  drive(-DEFAULT_SPEED, -DEFAULT_SPEED);
  state = STATE_8;
}

static void T9_9 (void) {
  drive (DEFAULT_SPEED-10, 0);
  state = STATE_9;
}

static void T9_1 (void) {
  stop_motors ();
  deployment_home ();
  state = STATE_1;
}

static void T9_4 (void) {
  stop_motors ();
  TMRArd_InitTimer(TIMER_OFFSET_PIVOT, OFFSET_PIVOT_PULSE);
  indicator_blanket_set(0, 50, 0, 10);
  state = STATE_4;
}

static void T4_1 (void) {
  stop_motors ();
  deployment_home ();
  state = STATE_1;
}

static void T4_4 (void) {
  drive (DEFAULT_SPEED-10, -(DEFAULT_SPEED-10));
  state = STATE_4;
}

static void T4_5 (void) {
  TMRArd_InitTimer(TIMER_OFFSET_PIVOT, OFFSET_PIVOT_PULSE);
  indicator_blanket_set(200, 200, 200, 200);
  state = STATE_5;
}

static void T5_1 (void) {
  stop_motors ();
  deployment_home ();
  state = STATE_1;
}

static void T5_5 (void) {
  drive (-(DEFAULT_SPEED-10), -(DEFAULT_SPEED-10));
  state = STATE_5;
}

static void T5_6 (void) {
  TMRArd_InitTimer(TIMER_OFFSET_PIVOT, OFFSET_PIVOT_PULSE);
  indicator_blanket_set(0, 200, 200, 0);
  state = STATE_6;
}

static void T6_1 (void) {
  stop_motors ();
  deployment_home ();
  state = STATE_1;
}

static void T6_6 (void) {
  drive (-(DEFAULT_SPEED-10), DEFAULT_SPEED-10);
  state = STATE_6;
}

static void T6_7 (void) {
  //finish me
  haltCode();
  state = STATE_7;
}

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
  if ((side_current > SIDE_BIN_DISTANCE) && (side_previous < SIDE_BIN_DISTANCE)) {
    side_previous = side_current;
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
