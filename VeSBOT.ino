
#include <Wire.h>
#include "MPU6050.h"
#define period 1000
/*Ultrasonic Definations*/

// defines pins numbers
const int trigPinF = 30;//
const int echoPinF = 31;
const int trigPinD = 32;
const int echoPinD = 33;
const int trigPinL = 34;
const int echoPinL = 35;
const int trigPinR = 36;
const int echoPinR = 37;
// defines variables
long durationF;
long durationD;
long durationL;
long durationR;
int distanceF;
int distanceD;
int distanceL;
int distanceR;

/* ultra */
MPU6050 mpu;

int count=0;
char okFlag=0;

byte degree[8] = {
  0b00000,
  0b00110,
  0b01111,
  0b00110,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};


#include<AFMotor.h>

AF_DCMotor blm(1);//Back left Motor
AF_DCMotor brm(2);//Back Right Motor
AF_DCMotor frm(3);//Front Right Motor
AF_DCMotor flm(4);//Front Left Motor

Vector rawAccel;
  Vector normAccel;
  
void setup() {

/* Ultrasonic Setup */
pinMode(trigPinF, OUTPUT);// Sets the trigPin as an Output
pinMode(echoPinF, INPUT); // Sets the echoPin as an Input
pinMode(trigPinD, OUTPUT);// Sets the trigPin as an Output
pinMode(echoPinD, INPUT); // Sets the echoPin as an Input
pinMode(trigPinL, OUTPUT);// Sets the trigPin as an Output
pinMode(echoPinL, INPUT); // Sets the echoPin as an Input
pinMode(trigPinR, OUTPUT);// Sets the trigPin as an Output
pinMode(echoPinR, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communicationcommunication
/* Ultrasonic Setup */

/*Ultrasonic code execution*/

  // put your setup code here, to run once:
Serial.begin(9600);
blm.setSpeed(200);//Normal Speed
brm.setSpeed(200);
frm.setSpeed(200);
flm.setSpeed(200);

Serial.println("Initialize MPU6050");
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  count=0;
  mpu.calibrateGyro();
  mpu.setThreshold(3);
  Serial.print("MPU6050 Interface");
  delay(2000);
}

void stopit(){
  blm.setSpeed(0);
  brm.setSpeed(0);
  frm.setSpeed(0);
  flm.setSpeed(0);
frm.run(BACKWARD); 
flm.run(BACKWARD);  
brm.run(BACKWARD);  
blm.run(BACKWARD);
//return; 
}

void turnforward(){
frm.run(FORWARD); 
flm.run(FORWARD);  
brm.run(FORWARD);  
blm.run(FORWARD);
}

void backward(){
frm.run(BACKWARD); 
flm.run(BACKWARD);  
brm.run(BACKWARD);  
blm.run(BACKWARD);
}

void turnleft(){
frm.run(FORWARD); 
flm.run(BACKWARD);  
brm.run(FORWARD);  
blm.run(BACKWARD);
}

void turnright(){
frm.run(BACKWARD); 
flm.run(FORWARD);  
brm.run(BACKWARD);  
blm.run(FORWARD);
}


void accelShow()
{
 Serial.print(" X     Y     Z");
   rawAccel = mpu.readRawAccel();
   normAccel = mpu.readNormalizeAccel();
  Serial.print(" Chadh/Utar = ");
  Serial.print(normAccel.XAxis);
  Serial.print(" Left/Right = ");
  Serial.print(normAccel.YAxis);
  Serial.print(" Znorm = ");
  Serial.println(normAccel.ZAxis);
  delay(100);
}



void loop() 
{  


// Clears the trigPin
digitalWrite(trigPinF, LOW);
delayMicroseconds(2);
digitalWrite(trigPinD, LOW);
delayMicroseconds(2);
digitalWrite(trigPinL, LOW);
delayMicroseconds(2);
digitalWrite(trigPinR, LOW);
delayMicroseconds(2);

// Sets the trigPinF on HIGH state for 10 micro seconds
digitalWrite(trigPinF, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinF, LOW);
// Reads the echoPinF, returns the sound wave travel time in microseconds
durationF= pulseIn(echoPinF, HIGH);
// Calculating the distanceF
distanceF= durationF * 0.034/2;

// Sets the trigPinB on HIGH state for 10 micro seconds
digitalWrite(trigPinD, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinD, LOW);
// Reads the echoPinB, returns the sound wave travel time in microseconds
durationD= pulseIn(echoPinD, HIGH);
// Calculating the distanceB
distanceD= durationD * 0.034/2;

// Sets the trigPinL on HIGH state for 10 micro seconds
digitalWrite(trigPinL, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinL, LOW);
// Reads the echoPinL, returns the sound wave travel time in microseconds
durationL= pulseIn(echoPinL, HIGH);
// Calculating the distanceB
distanceL= durationL * 0.034/2;

// Sets the trigPinR on HIGH state for 10 micro seconds
digitalWrite(trigPinR, HIGH);
delayMicroseconds(10);
digitalWrite(trigPinR, LOW);
// Reads the echoPinR, returns the sound wave travel time in microseconds
durationR= pulseIn(echoPinR, HIGH);
// Calculating the distanceB
distanceR= durationR * 0.034/2;
/*Ultrasonic code execution*/

Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();
 accelShow();
 delay(2000);
 Serial.print(" Chadh/Utar = ");
  Serial.print(normAccel.XAxis);
    long st=millis();
    Serial.println("Accelerometer");

if(distanceF<20)
 {
    if(distanceL<10 && distanceR<10)//8>9
   {
     backward();
     if(distanceL>distanceR)
    {
     turnleft();
    }
    else
    {
    turnright();
    }
   }
    else if(distanceL>distanceR)
    {
     turnleft();
    }
    else
    {
    turnright();
    }
 }
 else
 {
 turnforward();
 }
}//down if

/*Gyro code*/
 /*while(millis()<st+period)
    {
  
      if(normAccel.XAxis<-2)///Vehicle is moving upward
      {
        Serial.println("chadh lagla");
         Serial.print(" Chadh/Utar = ");
         Serial.print(normAccel.XAxis);
  blm.setSpeed(255);//full speed
  brm.setSpeed(255);
  frm.setSpeed(255);
  flm.setSpeed(255);
        turnforward();
        delay(1000);//Fastly upward
      }

      if(normAccel.XAxis>2)// Vehicle is moving Downward
      {
        Serial.println("Utar lagla");
         Serial.print(" Chadh/Utar = ");
  Serial.print(normAccel.XAxis);
  blm.setSpeed(100);//slow speed
  brm.setSpeed(100);
  frm.setSpeed(100);
  flm.setSpeed(100);
        turnforward();
        delay(1000);// Slowly Downward
      }
  if(normAccel.YAxis>2)// Vehicle is Tilted Left 
      {
        Serial.println("left Tilted");
         Serial.print(" Left/Right = ");
  Serial.print(normAccel.XAxis);
  blm.setSpeed(200);//increase speed
  brm.setSpeed(150);
  frm.setSpeed(150);
  flm.setSpeed(200);//increase speed
        turnright(); 
      }

  if(normAccel.YAxis<-2)// Vehicle is Tilted Right 
      {
        Serial.println("Right Tilted");
        Serial.print(" Left/Right = ");
  Serial.print(normAccel.XAxis);
  blm.setSpeed(150);
  brm.setSpeed(200);//increase speed
  frm.setSpeed(200);//increase speed
  flm.setSpeed(150);
        turnleft(); 
      }
      
       turnforward();
    }
}*/
