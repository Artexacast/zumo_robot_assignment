#include <Zumo32U4.h>
#include "Keyboard.h"
#include <Wire.h>
//Serial1 communicates over XBee
//Serial communicates over USB cable

Zumo32U4Motors motors;
Zumo32U4ProximitySensors proximitySensors;
Zumo32U4LineSensors lineSensors;


int16_t lastError = 0;

uint16_t lineSensorValues[5] = { 0, 0, 0, 0, 0 };
//#define NUM_SENSORS 5
//unsigned int lineSensorValues[NUM_SENSORS];

bool proximityLeft;
bool proximityRight;
bool proximityFront;

int motorsSpeed = 100;
int Serialdata=0;
int turnSpeed = 200;

void setup() {
  // put your setup code here, to run once:
  lineSensors.initFiveSensors();
  proximitySensors.initThreeSensors();
 
  Serial.begin(9600);
  Serial1.begin(9600);
  Keyboard.begin();
 // zumocalibrateLineSensors();
}

void zumocalibrateLineSensors(){
//  delay(1000);
  for(uint16_t i = 0; i < 120; i++)
  {
    if (i > 30 && i <= 90)
    {
      motors.setSpeeds(-200, 200);
    }
    else
    {
      motors.setSpeeds(200, -200);
    }

    lineSensors.calibrate();
  }
  motors.setSpeeds(0, 0);
  delay(5000);
}

void forward(){
  delay(1000);
  motors.setSpeeds(motorsSpeed, motorsSpeed);
  //Serial.write("Here2");
}

void stopMotor(){
  motors.setSpeeds(0,0);
}

void left(){
        delay(1000);
        motors.setSpeeds(-50, 50);
        Serial.write("Here2");
        delay(3000);
        stopMotor();
}

void right(){
        delay(1000);
        motors.setSpeeds(50, -50);
        Serial.write("Here2");
        delay(3000);
        stopMotor();
}

void reverse(){
       
        motors.setSpeeds(-75, -75);
        Serial.write("Here2");
        delay(1000);
        stopMotor();
}

void loop() {

  lineSensors.read(lineSensorValues);
  //zumocalibrateLineSensors();
//  Serial.println("Left");
//  Serial.println(lineSensors.readLine(lineSensorValues[0]));
//  Serial.println("Middle");
//   Serial.println(lineSensors.readLine(lineSensorValues[1]));
//   Serial.println("Right");
//   Serial.println(lineSensors.readLine(lineSensorValues[2]));

  int16_t position = lineSensors.readLine(lineSensorValues[0]);
 // 
 // Serial.println(position);
//Serial.println(lineSensorValues[0]);
  if (lineSensorValues[0] < 150){
    motors.setSpeeds(motorsSpeed, -motorsSpeed);
    delay(50);
    forward();
     Serial.println("Left");
     Serial.println(lineSensorValues[0]);
  }

  else if (lineSensorValues[4] < 90){
    motors.setSpeeds(-motorsSpeed, motorsSpeed);
    delay(50);
    forward();
    Serial.println("Right");
    Serial.println(lineSensorValues[2]);
  }

   else if (lineSensorValues[2] > 1000){
   // motors.setSpeeds(-motorsSpeed, motorsSpeed);
   // delay(50);
    reverse();
 //   delay(50);
    Serial.println("Reverse");
    Serial.println(lineSensorValues[2]);
  }
   else{
    motors.setSpeeds(motorsSpeed, motorsSpeed);
  }
//  int16_t error = position;
//
//  int16_t speedDifference = error / 4 + 6 * (error - lastError);
//
//  lastError = error;
//
//  int16_t leftSpeed = (int16_t)motorsSpeed + speedDifference;
//  int16_t rightSpeed = (int16_t)motorsSpeed - speedDifference;
//  
//  leftSpeed = constrain(leftSpeed, 0, (int16_t)motorsSpeed);
//  rightSpeed = constrain(rightSpeed, 0, (int16_t)motorsSpeed);
 
  //motors.setSpeeds(leftSpeed, rightSpeed);
//    // put your main code here, to run repeatedly:
//    
//    // check for incoming serial data:
//     if (Serial.available() > 0) {
//        
//        // read incoming serial data:
//        char inChar = Serial.read();
//
//        bool buttonPress = inChar;
//          if(buttonPress && inChar=='w') {
//            delay(500);
//            forward();
//          }
//        
//          buttonPress = inChar;
//          if(buttonPress && inChar=='s') {
//            delay(500);
//            stopMotor();
//          }
//
//          buttonPress = inChar;
//          if(buttonPress && inChar=='a') {
//            delay(500);
//            left();
//          }
//
//          buttonPress = inChar;
//          if(buttonPress && inChar=='d') {
//            delay(500);
//            right();
//          }
//
//          buttonPress = inChar;
//          if(buttonPress && inChar=='r') {
//            delay(500);
//            reverse();
//          }
//   }
}
