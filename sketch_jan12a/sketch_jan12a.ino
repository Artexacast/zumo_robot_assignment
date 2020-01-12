#include <Zumo32U4.h>

//Serial1 communicates over XBee
//Serial communicates over USB cable

Zumo32U4Motors motors;
Zumo32U4ProximitySensors proximitySensors;

int motorsSpeed = 250;
void setup() {
  // put your setup code here, to run once:
  
  //XBee
  Serial.begin(9600);
  Serial1.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
motors.setSpeeds(motorsSpeed, motorsSpeed);

delay(1000);

motors.setSpeeds(0,0);


}
