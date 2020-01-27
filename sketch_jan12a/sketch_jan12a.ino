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

uint16_t lineSensorValues[5] = { 0, 0, 0, 0, 0 };

bool proximityLeft;
bool proximityRight;
bool proximityFront;

int motorsSpeed = 100;
int Serialdata=0;

void setup() {
  // put your setup code here, to run once:
  lineSensors.initFiveSensors();
  proximitySensors.initThreeSensors();
 
  Serial.begin(9600);
  Serial1.begin(9600);

}

void room(){
  stopMotor();
  proximitySensors.read();

  //read values of proximity sensors
  int sensorOne = proximitySensors.countsFrontWithLeftLeds();
  int sensorTwo = proximitySensors.countsFrontWithRightLeds();
 
  if(sensorOne > 5 ){
    //if values are greater than 5, play a sound
    Serial.println("Object detected");
    buzzer.playFromProgramSpace(sound_effect);
    delay(1000);
  }
  stopMotor();
}

//Functions for movement

void forward(){
  delay(1000);
  motors.setSpeeds(motorsSpeed, motorsSpeed);
}

void stopMotor(){
  motors.setSpeeds(0,0);
}

void left(){
  stopMotor();
        delay(1000);
        motors.setSpeeds(-100, 100);
        Serial.write("Here2");
        delay(950);
        stopMotor();
}

void oneEighty(){
      motors.setSpeeds(-100, 100);
      Serial.write("Here2");
      delay(2200);
      stopMotor();
}

void right(){
       stopMotor();
       delay(1000);
       motors.setSpeeds(100, -100);
       Serial.write("Here2");
       delay(1100);
       stopMotor();
}

void reverse(){
        motors.setSpeeds(-100, -100);
        delay(1000);
        stopMotor();
}

//corridor tracking and wall detection
void automation(){
  Serial.println("Left");
  Serial.println(lineSensorValues[0]);
  Serial.println("Right");
  Serial.println(lineSensorValues[4]);
  Serial.println("Middle");
  Serial.println(lineSensorValues[2]);

  //check values of all line sensors and use functions accordingly
  
    //left line sensor
    if (lineSensorValues[0] > 450){
      motors.setSpeeds(motorsSpeed, motorsSpeed-50);
      delay(50);
      automation();
    }
    ]//right line sensor
    else if (lineSensorValues[4] > 400){
      motors.setSpeeds(motorsSpeed-50, motorsSpeed);
      delay(50);
      forward();
    }

    //middle sensor
    else if (lineSensorValues[2] > 400){
      stopMotor();
      reverse();
      stopMotor();
    }
   //if no sensors triggered, just move forward
     else{
      motors.setSpeeds(motorsSpeed, motorsSpeed);
    }
}

void loop() {
  lineSensors.read(lineSensorValues);
  automation();
     if (Serial1.available()) {
        char inChar = Serial1.read();
        Serial.println(inChar);

        //read values from gui and perform action
          if(inChar == '1') {
            delay(500);
            room();
          }
          if(inChar=='2'){
            delay(500);
            left();
          }

          if(inChar=='3'){
            delay(500);
            right();
          }
          
          if(inChar=='4'){
            delay(500);
            automation();
          }

          if(inChar=='6'){
            delay(500);
            reverse();
           }
          
          if(inChar=='7'){
            delay(500);
            stopMotor();
          }

          if(inChar=='8'){
          //  delay(500);
            oneEighty();
          }
   }
}
