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
/*---------------------------Constants---------------------------------------*/
/*---------------------------Module Variables--------------------------------*/
/*-----------------------------Public Functions------------------------------*/

//D1 = -.5, E1 = -.25, D2 = -.5, E2 = -.08 mps = .5

void setup() {
  Serial.begin(9600);

//  init_button();
    init_motors();
//  init_distance_sensor();
//  init_ending_timer();
//  init_light_ring();
//  init_line_sensor();
//  init_token_deploy();
//  init_compass();
//  init_token_sensors();

Serial.println("all components initialized");
}

void loop() {
  //set_motor_speed (0, 100);
  //set_motor_speed (1, 100);

  
  //Place coordinating state machine here
}
