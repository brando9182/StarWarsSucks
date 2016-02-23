int proximityPin1 = A0;
int proximityValue1 = 0;
int proximityPin2 = A1;
int proximityValue2 = 0;

//minimum difference between IR sensors for one to be cosidered
//facing the wall and the other one not
#define minProxDifference 100     

void initDistanceSensorPins(){
  //nothing to do
}

void distanceSensorTest(){
  //Read value from proximity sensor
  proximityValue1 = analogRead(proximityPin1);
  proximityValue2 = analogRead(proximityPin2);
  Serial.print("proximitySensor1 = ");
  Serial.println(proximityValue1);
  Serial.print("proximitySensor2 = ");
  Serial.println(proximityValue2);
  if(proximityValue1 - minProxDifference > proximityValue2){
    Serial.println("Faccing correct direction");
  }
  Serial.println("-----------------------");
  delay(1000);
}

