#include <Servo.h> // servo library
 
Servo myservo;  
 
int val;         
 
void setup() {
  myservo.attach(3); 
}
 
void loop() {
  val = analogRead(A0);// connect A0 pin to potentiometer   
  val = map(val, 0, 1023, 0, 180);     
  myservo.write(val);                 
  delay(20);                           
}
