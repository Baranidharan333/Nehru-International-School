#include<LiquidCrystal.h>
LiquidCrystal lcd(11,12,5,4,3,2);

void setup(){
  pinMode(6,OUTPUT);
  lcd.begin(16,2);
  lcd.setCursor(3,1);
  lcd.print("Start");
  delay(1000);
  lcd.clear();
  lcd.setCursor(2,1);
  lcd.print("record temp");
  delay(1000);
  lcd.clear();
}

void loop()
{ 
  lcd.blink();
  int read=analogRead(A1);
  delay(1000);
  float volt=read*5;
  volt/=1023;
  float temp=(volt-0.5)*100;
  lcd.setCursor(2,2);
  lcd.print("temp =");
  lcd.print(temp);
  if(temp<=25){
    analogWrite(6,50);
  }
  else if(temp>25&&inc<50)
    analogWrite(6,100);
  else
    analogWrite(6,255);
  }
