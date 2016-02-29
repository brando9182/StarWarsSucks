//WORK IN PROGRESS

/*-----------------------------Includes--------------------------------------*/
/*---------------------------Definitions-------------------------------------*/
//minimum difference between IR sensors for one to be cosidered
//facing the wall and the other one not
#define MIN_PROX_DIFFERENCE 100 
#define FRONT_CLEAR_RIGHT_BLOCKED 0
#define FRONT_BLOCKED_RIGHT_CLEAR 1

/*---------------------------Constants---------------------------------------*/
static int proximityPinFront = A0;
static int proximityValueFront = 0;
static int proximityPinRight = A1;
static int proximityValueRight = 0; 

/*---------------------------Module Variables--------------------------------*/
/*-----------------------------Public Functions------------------------------*/
void initDistanceSensorPins (void){
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
    Serial.println("Facing correct direction");
  }
  Serial.println("-----------------------");
  delay(500);
}

