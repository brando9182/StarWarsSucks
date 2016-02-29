/*-----------------------------Includes--------------------------------------*/
/*---------------------------Definitions-------------------------------------*/
/*---------------------------Constants---------------------------------------*/
/*---------------------------Module Variables--------------------------------*/
/*-----------------------------Public Functions------------------------------*/

void setup() {
  Serial.begin(9600);
  while(!Serial); //wait for serial to finish setting up
  init_motors ();
}

void loop() {
//  for(int i = 20; i < 100; i++){
//    set_motor_speed(0, i);
//    set_motor_speed(1, i);
//    Serial.println(i);
//    delay(500);
//  }
}
