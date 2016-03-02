/*-----------------------------Includes--------------------------------------*/
/*---------------------------Definitions-------------------------------------*/
//None of these may be correct
#define MOTOR_ENABLE_PIN_2          3
#define MOTOR_DIRECTION_PIN_2       4
#define MOTOR_ENABLE_PIN_1          5
#define MOTOR_DIRECTION_PIN_1       6
#define BUTTON_PIN                  11
#define INDICATOR_PIN               13
#define LONG_DISTANCE_SENSOR_PIN_0  A0
#define LONG_DISTANCE_SENSOR_PIN_1  A1
#define SHORT_DISTANCE_SENSOR_PIN   A2
#define LINE_SENSOR_PIN_0           A3
#define LINE_SENSOR_PIN_1           A4
#define LINE_SENSOR_PIN_2           A5

/*-------------------------Movement definitions------------------------------*/
#define RIGHT_MOTOR             0
#define LEFT_MOTOR              1
#define FORWARD                 HIGH
#define REVERSE                 LOW
#define CLOCKWISE                0
#define COUNTERCLOCKWISE        1
/*---------------------------Constants---------------------------------------*/
/*---------------------------Module Variables--------------------------------*/
/*-----------------------------Public Functions------------------------------*/

void setup() {
  Serial.begin(9600);

  init_button();
  init_motors();
  init_distance_sensor();
  init_ending_timer();
  init_light_ring();
  init_line_sensor();
  init_token_deploy();
  init_compass();
  init_token_sensors();

Serial.println("all components initialized");
}

void loop() {
 //drive_forward(1); 
 delay(1000);
 indicator_blanket_set(100, 100, 100, 100);
 //deployment_home();
 //delay(1000);
 //deploy_tokens(5);
// Serial.println(line_below_sensor(1));
// indicator_pulse();
// long_distance_sensor_report(1);
 
}
