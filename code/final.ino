#include <Servo.h>

#include <LiquidCrystal.h>
const int irsensor = A5; //ir sensor pin  
int sensorValue = 0; //ir sensor reading values               
int servoPin = 9; //pin where servo is attached to
int i = 0; //servo degrees 
Servo servo; //my Servo is called servo


const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

   // select the input pin Photo Diode.
int i1=0,i2=0,i3=0,i4=0;     // to store photo diode input

void setup() {
Serial.begin(9600);
  servo.attach(servoPin); //attach servo to servo pin
  lcd.begin(16, 2);
  // Print a message to the LCD.
        i1 = analogRead(A1);
        i2 = analogRead(A2);
        i3 = analogRead(A3);
        i4 = analogRead(A4);

  if(i1<500 && i2<500 && i3<500 && i4<500)
  lcd.print("NO SPACE");
  else
  {
    if(i1>500)
    lcd.print("MOVE TO SLOT 1");
    else if(i2>500)
    lcd.print("MOVE TO SLOT 2");
    else if(i3>500)
    lcd.print("MOVE TO SLOT 3");
    else if(i4>500)
    lcd.print("MOVE TO SLOT 4");
  }
}

void loop() {


        i1 = analogRead(A1);
        i2 = analogRead(A2);
        i3 = analogRead(A3);
        i4 = analogRead(A4);

        Serial.print("Input Value:");
        Serial.print(i1 ); 
        Serial.print(i2 ); 
        Serial.print(i3 ); 
        Serial.print(i4 ); // Printing Analog input value of Photo Diode.
        Serial.print("\n");           // moving to new line
        delay(500);        

    lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);

  sensorValue = analogRead(irsensor); //ir sensor reading values             
Serial.println(sensorValue);
  if(sensorValue < 600) //if sensorValue is lower than 600
  {for (int i = 90;i>=0; i--)
    //servo degrees increses from 0 to 180
    {
      servo.write(i); //servo goes to (i) position
      delay(15); //delay of 15 so it as time to change the position gently
      if(analogRead(irsensor) <600) //if it detecs something at that position
      {
        servo.write(i); //stay in that position
        delay(1000); //and here instead of waiting 3 seconds, can it only continue whith the code if sensorValue gets lower than 600
      }
    }
    //the same just from 180 to 0 (in the opposite direction)
    for (int i = 0; i<=90;i++)
    {
      servo.write(i);
      delay(15);
      if(analogRead(irsensor) > 600)
      {
        servo.write(i);
        delay(1000);
      }
    }
  }

}
