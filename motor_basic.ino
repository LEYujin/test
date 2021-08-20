#include <Servo.h>

byte servoPin_R = 10;
byte servoPin_L = 8;
Servo servo_L;
Servo servo_R;

void setup() {
  servo_R.attach(servoPin_R);
  servo_L.attach(servoPin_L);
  servo_R.writeMicroseconds(1500); // send "stop" signal to ESC.
  servo_L.writeMicroseconds(1500); // send "stop" signal to ESC.

  delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop() {
  int signal = 1700; // Set signal value, which should be between 1100 and 1900

  servo_L.writeMicroseconds(1300); // Send signal to ESC.
  servo_R.writeMicroseconds(1300); // Send signal to ESC.
}
