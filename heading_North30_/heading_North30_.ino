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

  left.attach(servoleft);
  right.attach(servoright);

  left.writeMicroseconds(1500); // send "stop" signal to ESC.
  right.writeMicroseconds(1500); // send "stop" signal to ESC.

  delay(7000); // delay to allow the ESC to recognize the stopped signal
}

void loop() {
  mlx.readData(data); //Read the values from the sensor
  float x = float(data.x) - 200;
  float y = float(data.y) - 270;
  Serial.print(x); Serial.print("\t");
  Serial.print(y);  Serial.print("\t");
  float heading = atan2(y, x); 
  
  if (heading < 0)
    heading += 2 * M_PI ;
    
    int signal = heading ;
    heading = heading * 180/M_PI ;
    Serial.print(heading); Serial.print("\n");
    
  if (20 <= heading && heading <= 40) //Go straight
  { 
    left.writeMicroseconds(1550);
    right.writeMicroseconds(1550); 
  }

  if (40 < heading && heading < 85 ) //left
  { 
    left.writeMicroseconds(1510); 
    right.writeMicroseconds(1560); 
  }
  
  if (85 <= heading && heading < 160 ) //Left
  { 
    left.writeMicroseconds(1510); 
    right.writeMicroseconds(1610); 
  }

  if ( 160 <= heading && heading < 210 ) //reverse, left
  { 
    left.writeMicroseconds(1510); 
    right.writeMicroseconds(1650); 
  }

  if (210 <= heading && heading < 260 ) //reverse, right
  { 
    left.writeMicroseconds(1650); 
    right.writeMicroseconds(1510); 
  }
  
  if (260 <= heading && heading < 335 ) //Right
  { 
    left.writeMicroseconds(1610); 
    right.writeMicroseconds(1510); 
  }
  
  if (335 <= heading && heading <= 360 ) //right
  { 
    left.writeMicroseconds(1560); 
    right.writeMicroseconds(1510); 
  }

    if (0 <= heading && heading < 20 ) //right
  { 
    left.writeMicroseconds(1560); 
    right.writeMicroseconds(1510); 
  }
    
  delay(500);
  
}
