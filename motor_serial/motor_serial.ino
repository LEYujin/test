#include <Servo.h>
Servo left;
Servo right;

byte motor_left = 9;
byte motor_right = 10;

void setup()
{
 Serial.begin(9600);
 left.attach(motor_left);
 right.attach(motor_right);

 left.writeMicroseconds(1500); // send "stop" signal to ESC.
 right.writeMicroseconds(1500);
 
 delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop()
{
  while (Serial.available() == 0)
  int val;
  int val = Serial.parseInt();
  
  Serial.println(val); Serial.println("\n");
  
  if (0 < val && val < 180) //Forward
  {
    left.writeMicroseconds(1700); //yujin
    right.writeMicroseconds(1700); //yujin
  }
  
  else if (180 <= val && val < 270)//Reverse Direction, Turn Left
  {
    left.writeMicroseconds(1500); //yujin
    right.writeMicroseconds(1700); //yujin
  }
     
  else (270 <= val && val < 360); //Reverse Direction, Turn Right
  {
    left.writeMicroseconds(1700); //yujin
    right.writeMicroseconds(1500); //yujin
  }
}
