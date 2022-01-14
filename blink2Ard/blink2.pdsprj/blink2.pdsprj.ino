#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
int count;
int flag;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(A0,INPUT);
  pinMode(4,INPUT_PULLUP);
  pinMode(7, OUTPUT);
  count = 0;
  flag=0;
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

  lcd.setCursor(0, 1);
  lcd.print("Count : ");
  lcd.setCursor(9, 1);
  
  // put your main code here, to run repeatedly:
//  if(readPin(4)==LOW ||  analogRead(A0)>500){
//    setPin(7,HIGH);
//    delay(1000);
//    setPin(7,LOW);
//    delay(1000);
//  }else{
//    setPin(7,LOW);
//  }
  if(analogRead(A0)>500 && flag==0){
    setPin(7, HIGH);
    count=count+1;
    lcd.setCursor(9, 1);
    lcd.print(count);
    flag=1;
  } else if(analogRead(A0)<500 && flag==1){
    setPin(7, LOW);
    flag=0;
  }
}
