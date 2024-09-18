#include <Servo.h>

Servo myServoMotor;

// Potentiometer PIN
int potPin = A0;
int potValue;
int angle;


void setup() {
  myServoMotor.attach(9); // Attach my servo motor to PIN 9
  
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  potValue = analogRead(potPin);
  Serial.print("Potentiometer Value: ");
  Serial.println(potValue);
  
  // Find angle based on potentiometer reading
  angle = map(potValue, 0, 1023, 0, 179);
  Serial.print("Angle Value: ");
  Serial.println(angle);


  // Rotate servo motor by this angle
  myServoMotor.write(angle);
  delay(10);
}
