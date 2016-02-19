/////////////////////////////////////////////////
//put title stuff here
/////////////////////////////////////////////////



void setup() {
  Serial.begin(9200);
  InitCompassPins();
  //make sure to call this last
  orient();
}

void loop() {
  
}
