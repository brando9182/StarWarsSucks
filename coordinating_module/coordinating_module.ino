/*-----------------------------Includes--------------------------------------*/
/*---------------------------PIN Definitions-------------------------------------*/
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
#define INDICATOR_PIN               13  //CONFIRMED (3/3), NHS
#define LONG_DISTANCE_SENSOR_PIN_0  A0  //Front-facing
#define LONG_DISTANCE_SENSOR_PIN_1  A1  //Back-facing
#define SHORT_DISTANCE_SENSOR_PIN   A2
#define LINE_SENSOR_PIN_0           A3
#define LINE_SENSOR_PIN_1           A4
#define LINE_SENSOR_PIN_2           A5

/*-------------------------Movement definitions------------------------------*/
/*---------------------------Constants---------------------------------------*/
/*---------------------------Module Variables--------------------------------*/
/*-----------------------------Public Functions------------------------------*/

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
  drive(-100, 0);
}
