
const int switchPin = 2;
int switchState = 0;
const int motorPin = 9;
const int ledPin = 13;

void setup() {
  pinMode(switchPin, INPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  switchState = digitalRead(switchPin);
  if(switchState == HIGH){
    digitalWrite(motorPin, HIGH);
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(motorPin, LOW);
    digitalWrite(ledPin, HIGH);
  }

}
