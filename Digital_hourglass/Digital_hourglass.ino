const int switchPin = 8;

unsigned long previousTime=0;

int switchState = 0;
int prevSwitchState = 0;

int led=2;

long interval=1000;

 
void setup() {
  Serial.begin(9600);
 for(int x=2;x<8;x++){
  pinMode(x,OUTPUT); //Stablishing all the LEDs as outputs
 }
 pinMode(switchPin,INPUT); //Stablishing the switch as an input
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currentTime = millis();

  if (currentTime - previousTime > interval) { 
    
    previousTime = currentTime;
    digitalWrite(led, HIGH);
    Serial.print("Set ON led number ");
    Serial.println(led);
    led++;
    }
       
    if (led > 7)
      {  
        Serial.println("Set LEDs to blink"); 
        delay(interval); //We need that so that the last LED stay a bit
        led=2;
          for(int x=0;x<5;x++) { //count how many blinks
              for(int x=2;x<8;x++){ digitalWrite(x, LOW); }
              delay(100);
              Serial.println("blink 1");
              for(int x=2;x<8;x++){ digitalWrite(x, HIGH); }
              delay(100);
              Serial.println("blink 2"); 
              for(int x=2;x<8;x++){ digitalWrite(x, LOW); } //we need LEDs to remain in LOW state, so that we can turn them HIGH for next count
              Serial.println("blink 3");  
          }

     }
    
    switchState = digitalRead(switchPin);
    
    if(switchState != prevSwitchState) {
        for(int x=2;x<8;x++){
        digitalWrite (x, LOW);
      }
        led=2;
        previousTime=currentTime;
      }
      
    prevSwitchState=switchState;

}