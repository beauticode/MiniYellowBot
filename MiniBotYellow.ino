#include "ArduinoNunchuk.h"
#include <Wire.h>

#define motorOne_EN 2 //All motors are currently parallel to this line.
#define motorOne_A 3
#define motorOne_B 5 
#define motorTwo_A 6
#define motorTwo_B 10
#define motorThree_A 9
#define motorThree_B 11
#define motorFour_A A0
#define motorFour_B A1
#define directionSwitchDelay 1000
#define BAUD 19200
int lastSwitch=0;
bool dir=true;//true=forward
//300=Highest Pitch
//700=Lowest Pitch
//If value around 500, stay still...If between between 300 and 470, move down. 530 and 700, move up
ArduinoNunchuk nunchuk=ArduinoNunchuk();

void setup() {
  // put your setup code here, to run once:
  pinMode(motorOne_EN,OUTPUT); //Currently enables assl motors
  pinMode(motorOne_A,OUTPUT);
  pinMode(motorOne_B,OUTPUT);
  pinMode(motorTwo_A,OUTPUT);
  pinMode(motorTwo_B,OUTPUT);
  pinMode(motorThree_A,OUTPUT);
  pinMode(motorThree_B,OUTPUT);
  pinMode(motorFour_A,OUTPUT);
  pinMode(motorFour_B,OUTPUT);
  digitalWrite(motorOne_EN,HIGH);
  Serial.begin(BAUD);
  nunchuk.init();
}

void loop() {
  nunchuk.update();
  //Using serial port to transmit data to the PC about the button presses & axis movements (for debugging)
  /*Serial.print("Button Z:");
  Serial.println(nunchuk.zButton);
  Serial.print("Button C:");
  Serial.println(nunchuk.cButton);
  Serial.print("Y analog: ");
  Serial.println(nunchuk.analogY);*/
  //Conditional statements used to determine position of remote, and attempt to "scale" the value to an appropriate PWM value between 0-255. (I would now approach this alot differently. but keeping it the way it is now)
  if(nunchuk.accelY>=300&&nunchuk.accelY<=470) {
    analogWrite(motorOne_B,(nunchuk.accelY-300)+85);
    analogWrite(motorOne_A,0);
    Serial.println("Moving gdown");
  } else if(nunchuk.accelY>=470&&nunchuk.accelY<=530) {
    analogWrite(motorOne_A,0);
    analogWrite(motorOne_B,0);
    Serial.println("Stationary");
  } else if(nunchuk.accelY>=530&&nunchuk.accelY<=700) {
    analogWrite(motorOne_A,(nunchuk.accelY-530)+85);//700-530 = 170 (under the maximum), so add the difference to make 255
    analogWrite(motorOne_B,0);
    Serial.println("Moving up");
  }
  //This segment needs to  be fixed
  if(nunchuk.analogY>=32&&nunchuk.analogY<=124) { //127 is idle point (+ and - 3 for tolerance range)
    analogWrite(motorTwo_B,(nunchuk.analogY-32)+(255-(nunchuk.analogY-32))); //Needs to be fixed, comeeup with new algorithm
    analogWrite(motorTwo_A,0);
    Serial.println("Moving gdown");
  } else if(nunchuk.analogY>=124&&nunchuk.analogY<=130) {
    analogWrite(motorTwo_A,0);
    analogWrite(motorTwo_B,0);
    Serial.println("Stationary");
  } else if(nunchuk.analogY>=130&&nunchuk.analogY<=226) {
    analogWrite(motorTwo_A,(nunchuk.analogY-130)+(255-(nunchuk.analogY-130)));
    analogWrite(motorTwo_B,0);
    Serial.println("Moving up");
  }
  if(nunchuk.accelX>=300&&nunchuk.accelX<=470) {
    analogWrite(motorThree_B,(nunchuk.accelX-300)+85);
    analogWrite(motorThree_A,0);
    Serial.println("Moving gdown");
  } else if(nunchuk.accelX>=470&&nunchuk.accelX<=530) {
    analogWrite(motorThree_A,0);
    analogWrite(motorThree_B,0);
    Serial.println("Stationary");
  } else if(nunchuk.accelX>=530&&nunchuk.accelX<=700) {
    analogWrite(motorThree_A,(nunchuk.accelX-530)+85);//700-530 = 170 (under the maximum), so add the difference to make 255
    analogWrite(motorThree_B,0);
    Serial.println("Moving up");
  }

  /*if(nunchuk.zButton&&nunchuk.cButton) {
    digitalWrite(motorOne_EN,HIGH);
  } else if((!nunchuk.zButton)&&(!nunchuk.cButton)) {
    digitalWrite(motorOne_EN,LOW);
  }*/


}
