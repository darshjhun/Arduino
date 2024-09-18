const int controlPin1 = 2;// the control pins will carry the 
//logic - direction to turn and applied to the H-Bridge
const int controlPin2 = 3;
const int enablePin = 9; // attached to the pin EN
const int directionSwitchPin = 4;// 4 and 5 carry the values 
//of buttonSwitches
const int onOffSwitchStateSwitchPin = 5;
const int potPin = A0; // analogic signal, because it is a 
//potentiometer delivering continuous values
int onOffSwitchState = 0;
int previousOnOffSwitchState = 0;
int directionSwitchState = 0;
int previousDirectionSwitchState = 0;

int motorEnabled = 0;
int motorSpeed = 0;
int motorDirection = 1;
void setup() {
  pinMode(directionSwitchPin,INPUT);
  pinMode(onOffSwitchStateSwitchPin,INPUT);
  pinMode(controlPin1,OUTPUT);
  pinMode(controlPin2,OUTPUT);
  pinMode(enablePin,OUTPUT);
  

  digitalWrite(enablePin,LOW);// the motor initializes at OFF
}
void loop() {
  onOffSwitchState = digitalRead(onOffSwitchStateSwitchPin);
  delay(1);
  directionSwitchState = digitalRead(directionSwitchPin);
  motorSpeed = analogRead(potPin)/4;

  if(onOffSwitchState != previousOnOffSwitchState){ // this 
//part allows the user to have the motor spin without having to 
//hold the button itself. Otherwise we should keep pressing the 
//button switch to turn the motor.   
    if(onOffSwitchState ==HIGH){ // if the user presses the 
//button, the state changes. Otherwise, it remains unchanged.
      motorEnabled = !motorEnabled;
    }
  }
  if (directionSwitchState != previousDirectionSwitchState) { // analagous to OnOffSwitchState
    if (directionSwitchState == HIGH) {
      motorDirection = !motorDirection;
    }
  }
  if(motorDirection == 1){ // If the Direction is 1, turn left.
    digitalWrite(controlPin1, HIGH);
    digitalWrite(controlPin2, LOW);
  }
  else {  // If the Direction is 0, turn right.
    digitalWrite(controlPin1, LOW);
    digitalWrite(controlPin2, HIGH);
  }

  if(motorEnabled == 1) { // If the motor should be enabled, 
//set EN to HIGH and the motorSpeed indicated by the 
//Potentiometer
    analogWrite(enablePin, motorSpeed);
  }
  else {
    analogWrite(enablePin, 0); // If the motor is turned Off, 
//set EN to LOW
  }
  
  previousDirectionSwitchState = directionSwitchState; // 
//These lines are very important to keep the current state!
  previousOnOffSwitchState = onOffSwitchState;
}