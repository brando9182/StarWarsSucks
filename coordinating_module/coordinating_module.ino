/*-----------------------------Includes--------------------------------------*/
/*---------------------------Definitions-------------------------------------*/
/*---------------------------Constants---------------------------------------*/
/*---------------------------Module Variables--------------------------------*/
/*-----------------------------Public Functions------------------------------*/

void setup() {
  Serial.begin(9600);
  while(!Serial); //wait for serial to finish setting up
  init_button();
  init_motors();
  init_distance_sensor();
  init_ending_timer();
  init_light_ring();
  init_line_sensor();
  init_token_deploy();
  init_compass();
  init_token_sensors();
}

void loop() {
  //Place coordinating state machine here
}
