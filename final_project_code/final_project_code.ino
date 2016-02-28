/////////////////////////////////////////////////
//put title stuff here
// TODO: maybe we should define all the pins inn this file
/////////////////////////////////////////////////


//distance sensors////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  while(!Serial); //wait for serial to finish setting up
  intializeMotors();
}

void loop() {
  //find lowest value at which is moves
  for(int i = 20; i < 100; i++){
    set_motor_speed(0, i);
    set_motor_speed(1, i);
    Serial.println(i);
    delay(500);
  }
}
////////////////////////////////////////////////////
