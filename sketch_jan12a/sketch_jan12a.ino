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

void room(){
  proximitySensors.read();

  int sensorOne = proximitySensors.countsFrontWithLeftLeds();
  int sensorTwo = proximitySensors.countsFrontWithRightLeds();
  
  if(sensorOne && sensorTwo < 4 ){
    Serial.println("Object detected");
  }
//  Serial.println(sensorOne);
//  Serial.println("Prox sensor one");
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
       
        motors.setSpeeds(100, 100);
     //   Serial.write("Here2");
        delay(1000);
        stopMotor();
}

void automation(){
  
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
      reverse();
      Serial.println("Reverse");
      Serial.println(lineSensorValues[2]);
    }
     else{
      motors.setSpeeds(motorsSpeed, motorsSpeed);
    }
}

void loop() {
  lineSensors.read(lineSensorValues);
  //int inChar = Serial1.read();
  //Serial.println(inChar);
     if (Serial1.available()) {
      //Serial1.write('w');
        char inChar = Serial1.read();
        Serial.println(inChar);
//        Serial.println("In the loop");
//      //  room();
//        Serial1.println(inChar);
//        bool buttonPress = inChar;
//          if(buttonPress && inChar=='a') {
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
//          if(buttonPress && inChar=='l') {
//            delay(500);
//            left();
//          }
//
//          buttonPress = inChar;
//          if(buttonPress && inChar=='d') {
//            delay(500);
//            right();
//          }

          //buttonPress = inChar;
      //    Serial1.println("Testing");
      //    Serial.print(inChar);
          if(inChar == '1') {
            Serial1.println("We got here");
            Serial.println("We got here");
            delay(500);
            Serial1.write("Reversed");
            reverse();
          }
   }
}
