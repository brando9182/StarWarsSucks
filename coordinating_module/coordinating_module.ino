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

/*-------------------------Movement definitions------------------------------*/
#define RIGHT_MOTOR             0
#define LEFT_MOTOR              1
#define FORWARD                 HIGH
#define REVERSE                 LOW
#define CLOCKWISE                0
#define COUNTERCLOCKWISE        1

/*-------------------------Distance sensor definitions-----------------------*/
#define LONG_RANGE_BACK             0
#define LONG_RANGE_FRONT            1
#define SHORT_RANGE_RIGHT           2
/*---------------------------Constants---------------------------------------*/
/*---------------------------Module Variables--------------------------------*/
/*-----------------------------Public Functions------------------------------*/

void setup() {
  Serial.begin(9600);

//  init_button();
//  init_motors();
  init_distance_sensor();
//  init_ending_timer();
//  init_light_ring();
//  init_line_sensor();
//  //init_token_deploy();
//  init_compass();
//  init_token_sensors();
indicator_clear();

Serial.println("all components initialized");
}

int incomingByte = 0;   // for incoming serial data
int data0 = 0;
int data1 = 1;
int data2 = 2;
uint8_t facing_walls = 0;
void loop() {
          // send data only when you receive data:
        if (Serial.available() > 0) {
                // say what you got:
                incomingByte = Serial.parseInt();
                Serial.println(incomingByte);
                
        }
  if(incomingByte == 0){
      Serial.print("Right sensor: ");
      data0 = analogRead(SHORT_DISTANCE_SENSOR_PIN);
      data1 = analogRead(SHORT_DISTANCE_SENSOR_PIN);
      data2 = analogRead(SHORT_DISTANCE_SENSOR_PIN);
      Serial.println((data0 + data1 + data2)/3);

  } else if (incomingByte == 1){
      Serial.print("back sensor: ");
      data0 = analogRead(LONG_DISTANCE_SENSOR_PIN_1);
      data1 = analogRead(LONG_DISTANCE_SENSOR_PIN_1);
      data2 = analogRead(LONG_DISTANCE_SENSOR_PIN_1);
      Serial.println((data0 + data1 + data2)/3);
  } else if (incomingByte == 2){
      Serial.print("Front sensor: ");
      data0 = analogRead(LONG_DISTANCE_SENSOR_PIN_0);
      data1 = analogRead(LONG_DISTANCE_SENSOR_PIN_0);
      data2 = analogRead(LONG_DISTANCE_SENSOR_PIN_0);
      Serial.println((data0 + data1 + data2)/3);
  }

  //spin
  if(analogRead(LONG_DISTANCE_SENSOR_PIN_0) > 300){
    facing_walls = 1;
    indicator_clear();
  }
  if(analogRead(LONG_DISTANCE_SENSOR_PIN_0) < 200 && facing_walls){
    indicator_blanket_set(255,0,0,0);
    if(analogRead(LONG_DISTANCE_SENSOR_PIN_1) > 600){
          indicator_blanket_set(0,255,0,0);
    }
    else if(analogRead(LONG_DISTANCE_SENSOR_PIN_1) < 600){
          indicator_blanket_set(0,0,255,0);
    }
  }
  Serial.println(facing_walls);
  
  delay(100);
 //deployment_home();
 //delay(1000);
 //deploy_tokens(5);
// indicator_pulse();
// long_distance_sensor_report(1);
 
}
