////////////////////////////////////////////////////////////////////////////////////////
//    Interface for using the distance sensors
//    Assumes they are mounted on the fron and back of the robot
//    Need to fine tune MIN_PROX_DIFFERENCE
//    Note that smaller inupts corresponse to a closer barrier
//////////////////////////////////////////////////////////////////////////////////////////////


//minimum difference between IR sensors for one to be cosidered
//facing the wall and the other one not
#define MIN_PROX_DIFFERENCE 100 
#define FRONT_CLEAR_RIGHT_BLOCKED 0
#define FRONT_BLOCKED_RIGHT_CLEAR 1

int proximityPinFront = A0;
int proximityValueFront = 0;
int proximityPinRight = A1;
int proximityValueRight = 0;    

void initDistanceSensorPins(){
  //nothing to do
}

//will check status of front facing and right facing proximity sensors
//if the condition specified is true, returns true
//note uses the differnce threshold defined above 
//TODO: needs tuning
bool frontRightProximity(bool desired_state){
  
  proximityValueFront = analogRead(proximityPinFront);
  proximityValueRight = analogRead(proximityPinRight);
  
  if(proximityValueFront - MIN_PROX_DIFFERENCE > proximityValueRight){
    return true;
  }
  else{
    return false;
  }
}

//use for testing the distance sensors
//includes a facing correct direction statement
//for orienting in the beggining of the round
void distanceSensorTest(){
  //Read value from proximity sensor
  proximityValueFront = analogRead(proximityPinFront);
  proximityValueRight = analogRead(proximityPinRight);
  Serial.print("proximitySensorFront = ");
  Serial.println(proximityValueFront);
  Serial.print("proximitySensorRight = ");
  Serial.println(proximityValueRight);
  if(proximityValueFront - MIN_PROX_DIFFERENCE > proximityValueRight){
    Serial.println("Faccing correct direction");
  }
  Serial.println("-----------------------");
  delay(1000);
}

