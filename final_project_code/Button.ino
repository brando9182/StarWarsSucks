///////////////////////////////////////////////////////
//    Button interface
//    Note the LED pin is not super necessary
//    Recomend delaying, see isButtonPressed() comments
//    ON THE  LED:
//    Leftmost anf right most pins control light
//    Center right and middle right give you a resistance when not pushed
//    Center right and middle left give you a resistance when pushed
///////////////////////////////////////////////////////

int buttonPin = 2;
int buttonLEDPin = 4;
int buttonPinValue  = 0;
int buttonLEDStatus = LOW;            //keep track of the button LED ON/OFF state

//Initialize the button
void InitButton(){
  pinMode(buttonPin, INPUT);           // set button pin to input
  digitalWrite(buttonPin, HIGH);       // turn on pullup resistors

  pinMode(buttonLEDPin, OUTPUT);
  digitalWrite(buttonLEDPin, LOW);
}

//recomend adding a half second delay: delay(500)
// to serve as debouncing 
bool isButtonPressed(){
    buttonPinValue = digitalRead(buttonPin);   // read the button pin
    if(buttonPinValue == HIGH){
      return false;
    } else{
      return true;
    }
}

void setButtonLED(bool power){
    digitalWrite(buttonLEDPin, power);    // sets the LED to the button's value
    buttonLEDStatus = power;              //update button LED status
}

void ToggleButtonLED(){
  if(buttonLEDStatus == HIGH){
    digitalWrite(buttonLEDPin, LOW);
    buttonLEDStatus = LOW;
  } else{
    digitalWrite(buttonLEDPin, HIGH);
    buttonLEDStatus = HIGH;
  }
}

