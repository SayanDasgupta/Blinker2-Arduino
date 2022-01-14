#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial sim800l(0, 1); // RX,TX for Arduino and for the module it's TXD RXD, they should be inverted

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
int count;
int flag;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(A0,INPUT);
  pinMode(6,INPUT_PULLUP);
  pinMode(7, OUTPUT);
  sim800l.begin(9600);   //Module baude rate, this is on max, it depends on the version
  Serial.begin(9600);   
  delay(1000);
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
  //Serial.println(analogRead(A0));

  lcd.setCursor(0, 1);
  lcd.print("Count : ");
  lcd.setCursor(9, 1);
  
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

  if (readPin(6) == LOW) {            //And if it's pressed
    Serial.println("Button pressed");   //Shows this message on the serial monitor
    delay(200);                         //Small delay to avoid detecting the button press many times
    SendSMS(count);                          //And this function is called
  }
  if (sim800l.available()){            //Displays on the serial monitor if there's a communication from the module
    Serial.write(sim800l.read()); 
  }
}

void SendSMS(int val){
  Serial.println("Sending SMS...");               //Show this message on serial monitor
  sim800l.print("AT+CMGF=1\r");                   //Set the module to SMS mode
  delay(100);
  sim800l.print("AT+CMGS=\"+919080659745\"\r");  //Your phone number don't forget to include your country code, example +212123456789"
  delay(500);
  sim800l.print(val);       //This is the text to send to the phone number, don't make it too long or you have to modify the SoftwareSerial buffer
  Serial.println(val);
  delay(500);
  sim800l.print((char)26);// (required according to the datasheet)
  delay(500);
  sim800l.println();
  Serial.println("Text Sent.");
  delay(500);

}
