/*-----------------------------Includes--------------------------------------*/
#include <Wire.h>

/*---------------------------Definitions-------------------------------------*/
#define COMPASS_ADDRESS 0x1E

/*---------------------------Constants---------------------------------------*/
/*---------------------------Module Variables--------------------------------*/
int compass_ideal_orientation;

/*----------------------------Public Functions-------------------------------*/
void init_compass (void){
  Wire.begin();
  Wire.beginTransmission(COMPASS_ADDRESS);
  Wire.write(0x02);
  Wire.write(0x00);
  Wire.endTransmission();
}

void compass_calibrate (void) {
  compass_ideal_orientation = compass_read_heading();
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
