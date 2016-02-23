/////////////////////////////////////////////////
//put title stuff here
/////////////////////////////////////////////////



void setup() {
  Serial.begin(9200);
  InitButton();
  //make sure to call this last
  //orient();
}

void loop() {
  setButtonLED(HIGH);
  while(true){
    Serial.println(isButtonPressed());
    if(isButtonPressed()){
      delay(500);
      toggleButtonLED();
    }
  }
}
