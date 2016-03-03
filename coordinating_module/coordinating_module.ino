/*-----------------------------Includes--------------------------------------*/
/*---------------------------PIN Definitions-------------------------------------*/
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
  init_distance_sensor();
//  init_ending_timer();
  init_light_ring();
//  init_line_sensor();
//  init_motors();
  init_token_deploy();
  init_token_sensors();
//  init_token_sensors();
}

uint8_t set_up_done = 1;
uint8_t facing_walls = 0;
void loop() {
  set_up_done = start_up(set_up_done);
  drive_forward(.3);
  if(button_state_report()){
    off_state();
    delay(1000);
  }
  delay(100);
 //deployment_home();
 //delay(1000);
 //deploy_tokens(5);
// indicator_pulse();
// long_distance_sensor_report(1);
 
}

void off_state(){
  //turn motors, lights etc off
  drive_forward(0);
  delay(1000); //block for one second
  while(button_state_report() == 0){};
  return;
}

>>>>>>> 60945c5dcbe2dbbba505ac1a96c7f132b9a24c9e
