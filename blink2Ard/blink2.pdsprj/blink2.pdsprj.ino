#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(A0,INPUT);
  pinMode(4,INPUT_PULLUP);
  pinMode(7, OUTPUT);
}

int readPin(int pn){
  return digitalRead(pn);
}

void setPin(int pn, int state){
  digitalWrite(pn, state);
}

void loop() {
  //lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Value : ");
  lcd.setCursor(10, 0);
  lcd.print(analogRead(A0));
  Serial.println(analogRead(A0));
  
  // put your main code here, to run repeatedly:
  if(readPin(4)==LOW ||  analogRead(A0)>500){
    setPin(7,HIGH);
    delay(1000);
    setPin(7,LOW);
    delay(1000);
  }else{
    setPin(7,LOW);
  }
}
