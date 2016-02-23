//////////////////////////////////////////////////
//    PhotoResistor interface
//    Measured with a sinking 560 ohm resistor to ground
//    If you want to change the resistor value, the NO_LIGHT_MAX will need to change
//////////////////////////////////////////////////

//even in complete darkness it outputs a value of ~32 (voltage divider)
#define NO_LIGHT_MAX 40

int photoResistorPin = A2;
int photoResistorValue = 0;

//returns true if a chip is in
//this assumes the chip will block the light from hitting the PhRs
bool isChipIn(){
  photoResistorValue = analogRead(photoResistorPin);
  
  if(photoResistorValue < NO_LIGHT_MAX){
    return true;
  }
  else{
    return false;
  }
}

// use for testing the photoresistor
void photoResistorTest(){
  photoResistorValue = analogRead(photoResistorPin);
  Serial.print("PhotoResistorValue = ");
  Serial.println(photoResistorValue);
  Serial.println("-----------------------");
  delay(1000);
}

