#include <Zumo32U4.h>
#include "Keyboard.h"
//Serial1 communicates over XBee
//Serial communicates over USB cable

Zumo32U4Motors motors;
Zumo32U4ProximitySensors proximitySensors;

int motorsSpeed = 10;
int Serialdata=0;
void setup() {
  // put your setup code here, to run once:
  
  //XBee
  Serial.begin(9600);
  Serial1.begin(9600);
  Keyboard.begin();

}

void loop() {
    // put your main code here, to run repeatedly:
  
    // check for incoming serial data:
     if (Serial.available() > 0) {
        
        // read incoming serial data:
        char inChar = Serial.read();

        bool buttonPress = inChar;
          if(buttonPress && inChar=='w') {
            delay(500);
            forward();
          }

          buttonPress = inChar;
          if(buttonPress && inChar=='s') {
            delay(500);
            stopMotor();
          }

          buttonPress = inChar;
          if(buttonPress && inChar=='a') {
            delay(500);
            left();
          }

          buttonPress = inChar;
          if(buttonPress && inChar=='d') {
            delay(500);
            right();
          }

          buttonPress = inChar;
          if(buttonPress && inChar=='r') {
            delay(500);
            reverse();
          }
   }
}

void forward(){
        delay(1000);
        motors.setSpeeds(250, 250);
        Serial.write("Here2");
        delay(1000);
       
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
        delay(1000);
        motors.setSpeeds(-500, -500);
        Serial.write("Here2");
        delay(3000);
        stopMotor();
}
