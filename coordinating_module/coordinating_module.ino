/*-----------------------------Includes--------------------------------------*/
/*---------------------------PIN Definitions-------------------------------------*/
//None of these may be correct
#define DEPLOYMENT_SERVO_PIN        2   //CONFIRMED (3/3), NHS
#define MOTOR_ENABLE_PIN_2          3
#define MOTOR_DIRECTION_PIN_2       4
#define MOTOR_ENABLE_PIN_1          5
#define MOTOR_DIRECTION_PIN_1       6
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

//  init_button();
//  init_compass();
//  init_distance_sensor();
//  init_ending_timer();
//  init_ending_timer();
  init_light_ring();
//  init_line_sensor();
//  init_motors();
  init_token_deploy();
  init_token_sensors();
}

void loop() {
  deployment_home ();
//  delay(500);
//  deploy_tokens(1);
////  Serial.println(deployment_tokens_remaining());
//  delay(500);

//indicator_pulse();
//indicator_blanket_set(10,10,10,0);
//delay(500);
//indicator_clear();
//delay(1000);

  //Serial.println(token_in_slot(1));
  delay(10);

  //short_distance_sensor_report();
  //line_below_sensor(1);
  drive_forward(1);
//  delay(10);
  
 }
