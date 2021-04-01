#include "Arduino.h"
#include <Servo.h>
Servo fingerServos[5];  // create servo object to control a servo
void moveServo(int);
int FingerPositions[5] = {0, 0, 0, 0, 0};
int servoAnglesLow[5] = {45, 65, 45, 45, 90};
int servoAnglesHigh[5] = {135, 120, 135, 150, 15};
int servoAnglesMiddle[5] = {90, 90, 90, 90, 90};
String serial_cmd = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting Program");
  delay(20);

  fingerServos[0].attach(7);  // attaches the servo on pin 9 to the servo object (thumb)
  fingerServos[1].attach(8);  // attaches the servo on pin 9 to the servo object
  fingerServos[2].attach(9);  // attaches the servo on pin 9 to the servo object
  fingerServos[3].attach(10);  // attaches the servo on pin 9 to the servo object (ring)
  fingerServos[4].attach(11);  // attaches the servo on pin 9 to the servo object (pinky)
  Serial.println("Leaving Setup");
}

void loop() {
  Serial.println("Ready-to-receive");
  if (Serial) {
    serial_cmd = Serial.readString();
    //Get end of serial
    int end = serial_cmd.indexOf("x");
    //Get start if serial
    int start = serial_cmd.indexOf("h");
    if (serial_cmd != "waiting" && serial_cmd != "" && serial_cmd != "NODATA") {
      FingerPositions[0] = (serial_cmd.substring((start + 1), (start + 2))).toInt();
      FingerPositions[1] = (serial_cmd.substring((start + 2), (start + 3))).toInt();
      FingerPositions[2] = (serial_cmd.substring((start + 3), (start + 4))).toInt();
      FingerPositions[3] = (serial_cmd.substring((start + 4), (start + 5))).toInt();
      FingerPositions[4] = (serial_cmd.substring((start + 5), (start + 6))).toInt();
      Serial.print("Recieved Data------");
      Serial.print(serial_cmd);
      Serial.print("------Finger States: ");
      Serial.print(FingerPositions[0]);
      Serial.print(FingerPositions[1]);
      Serial.print(FingerPositions[2]);
      Serial.print(FingerPositions[3]);
      Serial.println(FingerPositions[4]);
      serial_cmd = "NODATA";
    }
    moveServo(0); // thumb
    moveServo(1); // Index
    moveServo(2); //Middle
    moveServo(4); // Pinky
    moveServo(3); // Ring
    
  }
delay(20);
}

void moveServo(int servoNumber) {
  if (FingerPositions[servoNumber] == 1) {
    fingerServos[servoNumber].write(servoAnglesMiddle[servoNumber]);
  } else if (FingerPositions[servoNumber] == 2) {
    fingerServos[servoNumber].write(servoAnglesLow[servoNumber]);
  } else {
    fingerServos[servoNumber].write(servoAnglesHigh[servoNumber]);
  }
}