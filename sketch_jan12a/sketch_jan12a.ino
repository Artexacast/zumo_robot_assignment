#include <Zumo32U4.h>
#include "Keyboard.h"
#include <Wire.h>
//Serial1 communicates over XBee
//Serial communicates over USB cable

Zumo32U4Motors motors;
Zumo32U4ProximitySensors proximitySensors;
Zumo32U4LineSensors lineSensors;
Zumo32U4Buzzer buzzer;
const char sound_effect[] PROGMEM = "O4 T100 V15 L4 MS g12>c12>e12>G6>E12 ML>G2";


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
  stopMotor();
  proximitySensors.read();

  int sensorOne = proximitySensors.countsFrontWithLeftLeds();
  int sensorTwo = proximitySensors.countsFrontWithRightLeds();
  Serial.println(sensorOne);
  if(sensorOne > 5 ){
    Serial.println("Object detected");
    buzzer.playFromProgramSpace(sound_effect);
    delay(1000);
  }
  stopMotor();
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
  stopMotor();
        delay(1000);
        motors.setSpeeds(-100, 100);
        Serial.write("Here2");
        delay(1100);
        stopMotor();
       // automation();
}

void right(){
  stopMotor();
       delay(1000);
        motors.setSpeeds(100, -100);
        Serial.write("Here2");
        delay(1100);
        stopMotor();
   //     automation();
}

void reverse(){
       
        motors.setSpeeds(-100, -100);
     //   Serial.write("Here2");
        delay(1000);
        stopMotor();
}

void automation(){
  Serial.println("Left");
  Serial.println(lineSensorValues[0]);
  Serial.println("Right");
  Serial.println(lineSensorValues[4]);
  Serial.println("Middle");
  Serial.println(lineSensorValues[2]);
  
    if (lineSensorValues[0] > 450){
      motors.setSpeeds(motorsSpeed, motorsSpeed-50);
      delay(50);
      automation();
//       Serial.println("Left");
//       Serial.println(lineSensorValues[0]);
    }
  
    else if (lineSensorValues[4] > 400){
      motors.setSpeeds(motorsSpeed-50, motorsSpeed);
      delay(50);
      forward();
//      Serial.println("Right");
//      Serial.println(lineSensorValues[2]);
    }
  
     else if (lineSensorValues[2] > 400){
      stopMotor();
      //reverse();
//      Serial.println("Reverse");
//      Serial.println(lineSensorValues[2]);
    }
     else{
      motors.setSpeeds(motorsSpeed, motorsSpeed);
    }
}

void loop() {
  lineSensors.read(lineSensorValues);
  //automation();
  //int inChar = Serial1.read();
  //Serial.println(inChar);
     if (Serial1.available()) {
      //Serial1.write('w');
        char inChar = Serial1.read();
        Serial.println(inChar);
//        Serial.println("In the loop");
//        Serial1.println(inChar);
//        bool buttonPress = inChar;
//          if(buttonPress && inChar=='a') {
//            delay(500);
//            forward();
//          }
//          
//          buttonPress = inChar;
//          if(buttonPress && inChar=='automationas') {
//            delay(500);
//            stopMotor();
//          }
//
//          buttonPress = inChar;4

          if(inChar=='6') {
                      delay(500);
                      reverse();
                    }
          if(inChar=='2') {
            delay(500);
            left();
          }

          if(inChar=='7') {
            delay(500);
            stopMotor();
          }

          if(inChar=='4') {
            delay(500);
            automation();
          }
//
//          buttonPress = inChar;
          if(inChar=='3') {
            delay(500);
            right();
          }

          //buttonPress = inChar;
      //    Serial1.println("Testing");
      //    Serial.print(inChar);
          if(inChar == '1') {
            delay(500);
            
            room();
          }
   }
}
