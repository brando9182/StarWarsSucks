//NOT WORKING YET, DEVELOPMENT PUT ON HOLD
/*-----------------------------Includes--------------------------------------*/
#include <Wire.h>
/*---------------------------Definitions-------------------------------------*/
//Requires pins 2 and 3
#define COMPASS_ADDRESS 0x1E
//TODO: measure this
#define VOLTS_TO_DEGREES 1

/*---------------------------Constants---------------------------------------*/
struct compass {
   int x;
   int y;
   int z;
} compass_values;
//this can also be instanntiated as a struct,
//a better coder than me should do this
int ideal_x = 0;
/*---------------------------Module Variables--------------------------------*/
int compass_ideal_orientation;

/*----------------------------Public Functions-------------------------------*/
void init_compass (void){
  //Initialize Serial and I2C communications
  Wire.begin();
  
  //Put the HMC5883 IC into the correct operating mode
  Wire.beginTransmission(COMPASS_ADDRESS); //open communication with HMC5883
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Serial.println("about to end transmission");
  Wire.endTransmission();
    Serial.println("ended transmission");
}

void compass_calibrate (void) {
  compass_ideal_orientation = compass_read_heading();
}

int degrees_from_ideal(){
	update_compass();
	int degrees_from_ideal = (compass_values.x - ideal_x) * VOLTS_TO_DEGREES;
	if(compass_values.y > compass_values.x) degrees_from_ideal += 180;
	//return degrees_from_ideal;
  return compass_values.x;
}

void update_compass(void){
  Wire.beginTransmission(COMPASS_ADDRESS);
	Wire.write(0x03); //select register 3, X MSB register
	Wire.endTransmission();
	Wire.requestFrom(COMPASS_ADDRESS, 6);
  if(6<=Wire.available()){
    compass_values.x = Wire.read()<<8; //X msb
    compass_values.x |= Wire.read(); //X lsb
    compass_values.z = Wire.read()<<8; //Z msb
    compass_values.z |= Wire.read(); //Z lsb
    compass_values.y = Wire.read()<<8; //Y msb
    compass_values.y |= Wire.read(); //Y lsb
	}
}

//Returns x-value axis compass value
int compass_read_heading(void) {
  int x,y,z;
  Wire.beginTransmission(COMPASS_ADDRESS);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  Wire.requestFrom(COMPASS_ADDRESS, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }
  return x;
}

void print_compass_info(){
   int x,y,z; //triple axis data

  //Tell the HMC5883L where to begin reading data
  Wire.beginTransmission(COMPASS_ADDRESS);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
  
 
 //Read data from each axis, 2 registers per axis
  Wire.requestFrom(COMPASS_ADDRESS, 6);
  if(6<=Wire.available()){
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }
  
  //Print out values of each axis
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("  z: ");
  Serial.println(z);
  
  delay(250);
}

