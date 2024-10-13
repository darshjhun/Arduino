// Arduino code for Parking lot with Manual control and Sensor based control
// With LiquidCrystal Display
// Author: Chandan J
// Date: 05 Oct 2024

#include <Servo.h>
#include <LiquidCrystal.h>

// Initiate LCD with appropriate PIN numbers on Arduino Board
// LCD RS pin to digital pin 12
// LCD Enable pin to digital pin 11
// LCD D4 pin to digital pin 5
// LCD D5 pin to digital pin 4
// LCD D6 pin to digital pin 3
// LCD D7 pin to digital pin 2
// LCD R/W pin to GND
// LCD VSS pin to GND
// LCD VCC pin to 5V
// LCD LED+ to 5V through a 220 ohm resistor
// LCD LED- to GND
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// make some custom characters:
byte heart[8] = {
  0b00000,
  0b01010,
  0b11111,
  0b11111,
  0b11111,
  0b01110,
  0b00100,
  0b00000
};

// Defining servo motor
Servo myServo;
const int servoPin = 10;

bool barRaised = false;
bool carEntering = false;
bool carExisting = false;
int msgDisplayTime = 0;

// Setting up horizontal angle and vertical angle
// Since Servo can turn from 0 to 180, adjust it 
// as per your servo motor orientation
const int horizonalAngle = 90;
const int verticalAngle = 180;
// Keeping initial angle to horizontal
int angle = horizonalAngle;

// Potentiometer PIN for manual control
const int potPin = A0;
int potVal = 0;
int previousPotVal = 0;

// IR Sensor PINs
const int frontIRPin = 7;
const int backIRPin = 8;

const int maxParkingSlot = 3;
int currentlyParked = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(servoPin, OUTPUT);
  pinMode(potPin, INPUT);
  pinMode(frontIRPin, INPUT);
  pinMode(backIRPin, INPUT);
  myServo.attach(servoPin);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // create a new character
  lcd.createChar(0, heart);  
  // Print a love message to the lcd.
  defaultDisplayMsg();
}

void loop() {
  // put your main code here, to run repeatedly:
  myServo.attach(10);
  int currentTime = millis();
  if(currentTime - msgDisplayTime > 5000){ // Reset to default message after 5 seconds
    defaultDisplayMsg();
    msgDisplayTime = currentTime;
  }
  // Manual Control with Potentiometer
  potVal = analogRead(potPin);
  if (previousPotVal != potVal) {
    manual_control();
    // Storing current value, to check if it was changed
    previousPotVal = potVal;
  } else {
    // Sensor Based Control
    ir_sensor_based_control();
  }
  delay(500);
}

// Manual control with Potentiometer 
void manual_control(){
  // Mapping steps from horizontal position to vertical position
  angle = map(potVal, 0, 1023, horizonalAngle, verticalAngle);
  myServo.write(angle);
}

void ir_sensor_based_control(){
  int frontIRValue = digitalRead(frontIRPin);
  int backIRValue = digitalRead(backIRPin);
  if ( frontIRValue == LOW) { // Front sensor detects object
    frontSensorActuator();
  } 
  if ( backIRValue == LOW) { // Back sensor detects object
    backSensorActuator();
  }
}

// Enter parking
void frontSensorActuator(){
  if(maxParkingSlot <= currentlyParked ){ // First check if Parking is full
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sorry!");
    lcd.setCursor(0, 1);
    lcd.print("Parking Full!");
  } else if(!barRaised){ // Check if bar is not raised(due to existing) -> Means car is entering
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome!");
    lcd.setCursor(0, 1);
    lcd.print("Enter ==> ");
    raise_bar();
    carEntering = true; // Set the car entering flag
    currentlyParked += 1; // Increase the currently parked count
  } else if (carExisting) { // If the bar is already raised and carExiting, then lower the bar
    lower_bar();
    carEntering = false; // Reset carEntering to false
    carExisting = false; // Reset carExisting to false
  }
}

// Exit parking
void backSensorActuator(){
  carExisting = true;
  if(currentlyParked < 0 ){ // Check if there in no currently parked car
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Strange!");
    lcd.setCursor(0, 1);
    lcd.print("Very Strange!"); // Isn't it "VERY STRANGE!" :-)
    currentlyParked = 0; // Still reset currentlyParked to 0.
  } else if(!barRaised) { // Check if bar is not already raised(due to entering)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Good Bye!");
    lcd.setCursor(0, 1);
    lcd.print("<== EXIT");
    raise_bar();
    carExisting = true; // Set the car exiting flag
    currentlyParked -= 1; // Decrease the count of currently parked car
  } else if (carEntering) { // If the bar is already raised and carEntering, then lower the bar
    lower_bar();
    carEntering = false; // Reset carEntering to false
    carExisting = false; // Reset carExisting to false
  }
}

// Method to raise the bar
void raise_bar(){
  Serial.println("Raising Bar");
  barRaised = true;
  myServo.write(verticalAngle);
}

// Method to lower the bar
void lower_bar(){
  Serial.println("Lowering Bar");
  barRaised = false;
  myServo.write(horizonalAngle);
}

void defaultDisplayMsg(){
  lcd.clear();
  lcd.setCursor(0, 0);// set the cursor to the top left
  lcd.print("I ");
  lcd.write(byte(0)); // when calling lcd.write() '0' must be cast as a byte
  lcd.print(" Arduino! ");
  lcd.setCursor(0, 1);
  lcd.print("Parking slots: ");
  lcd.print(maxParkingSlot - currentlyParked);  // Directly print the integer
}
