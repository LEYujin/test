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
  mlx.setGainSel(1);
  mlx.setResolution(0, 0, 0); //x, y, z
  mlx.setOverSampling(0);
  mlx.setDigitalFiltering(0);
  
  left.attach(servoleft);
  right.attach(servoright);

  left.attach(servoleft);
  right.attach(servoright);

  left.writeMicroseconds(1500); // send "stop" signal to ESC.
  right.writeMicroseconds(1500); // send "stop" signal to ESC.

  delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop() {
  mlx.readData(data); //Read the values from the sensor
  float x = float(data.x) + 30 ;
  float y = float(data.y) + 35 ;
  Serial.print("mag : \t ");
  Serial.print(x); Serial.print("\t");
  Serial.print(y);  Serial.print("\t");
  float heading = atan2(y, x);
  
  if (heading < 0)
    heading += 2 * M_PI ;
    
    int signal = heading ;
    heading = heading * 180/M_PI ; 
  
  if (330 <= heading && heading < 360) //North, left
  { 
    left.writeMicroseconds(1510);
    right.writeMicroseconds(1610); 
  }

  if (0 <= heading && heading < 30 ) //North, left
  { 
    left.writeMicroseconds(1510); 
    right.writeMicroseconds(1610); 
  }

  if ( 30 <= heading && heading < 90 ) //reverse, left
  { 
    left.writeMicroseconds(1510); 
    right.writeMicroseconds(1650); 
  }

  if (90 <= heading && heading < 150 ) //reverse, right
  { 
    left.writeMicroseconds(1650); 
    right.writeMicroseconds(1510); 
  }
  
  if (150 <= heading && heading < 210 ) //South, right
  { 
    left.writeMicroseconds(1610); 
    right.writeMicroseconds(1510); 
  }
  
  if (210 <= heading && heading < 240 ) //South+West, right
  { 
    left.writeMicroseconds(1590); 
    right.writeMicroseconds(1510); 
  }

    if (240 <= heading && heading < 270 ) //South+West, right
  { 
    left.writeMicroseconds(1560); 
    right.writeMicroseconds(1510); 
  }
  
    if (270 <= heading && heading < 300 ) //North+West, left
  { 
    left.writeMicroseconds(1510); 
    right.writeMicroseconds(1560); 
  } 
   
  if (300 <= heading && heading < 330 ) //North+West, left
  { 
    left.writeMicroseconds(1590); 
    right.writeMicroseconds(1510); 
  }
  
  delay(5000);
  
}
