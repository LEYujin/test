#include <Wire.h>
#include <MLX90393.h> 
#include <Servo.h>

byte servoleft = 8;
byte servoright = 10;
Servo left;
Servo right;

MLX90393 mlx;
MLX90393::txyz data; //Create a structure, called data, of four floats (t, x, y, and z)

void setup() {
  Serial.begin(9600);
  Serial.println("MLX90393 Read Example");
  Wire.begin();
  //Connect to sensor with I2C address jumpers set: A1 = 1, A0 = 0
  //Use DRDY pin connected to A3
  //Returns byte containing status bytes
  byte status = mlx.begin();

  //Report status from configuration
  Serial.print("Start status: 0x");
  if(status < 0x10) Serial.print("0"); //Pretty output
  Serial.println(status, BIN);
  mlx.setGainSel(1);
  mlx.setResolution(0, 0, 0); //x, y, z
  mlx.setOverSampling(0);
  mlx.setDigitalFiltering(0);
  
  left.attach(servoleft);
  right.attach(servoright);

  left.writeMicroseconds(1500); // send "stop" signal to ESC.
  right.writeMicroseconds(1500); // send "stop" signal to ESC.

  delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop() {
  mlx.readData(data); //Read the values from the sensor
  float x = float(data.x) - 360;
  float y = float(data.y) - 268.5;
  Serial.print(x); Serial.print("\t");
  Serial.print(y);  Serial.print("\t");
  float heading = atan2(y, x); 
  
  if (heading < 0)
    heading += 2 * M_PI ;
    
    int signal = heading ;
    heading = heading * 180/M_PI ;
    Serial.print(heading); Serial.print("\n");
    
  if (35 <= heading && heading <= 55) //Go straight
  { 
    left.writeMicroseconds(1600);
    right.writeMicroseconds(1600); 
  }

  if (55 < heading && heading < 100 ) //left
  { 
    left.writeMicroseconds(1530); 
    right.writeMicroseconds(1600); 
  }
  
  if (100 <= heading && heading < 175 ) //Left
  { 
    left.writeMicroseconds(1530); 
    right.writeMicroseconds(1630); 
  }

  if ( 175 <= heading && heading < 225 ) //reverse, left
  { 
    left.writeMicroseconds(1530); 
    right.writeMicroseconds(1650); 
  }

  if (225 <= heading && heading < 275 ) //reverse, right
  { 
    left.writeMicroseconds(1650); 
    right.writeMicroseconds(1530); 
  }
  
  if (275 <= heading && heading < 350 ) //Right
  { 
    left.writeMicroseconds(1630); 
    right.writeMicroseconds(1530); 
  }
  
  if (350 <= heading && heading <= 360 ) //right
  { 
    left.writeMicroseconds(1600); 
    right.writeMicroseconds(1530); 
  }

    if (0 <= heading && heading < 35 ) //right
  { 
    left.writeMicroseconds(1600); 
    right.writeMicroseconds(1530); 
  }
    
  delay(500);
  
}
