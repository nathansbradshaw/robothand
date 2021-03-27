#include "Arduino.h"
#include <Servo.h>
Servo fingerServos[5];  // create servo object to control a servo
void moveServo(int);
int FingerPositions[5] = {0, 0, 0, 0, 0};
String serial_cmd = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("This work?");
  delay(1000);
  fingerServos[0].attach(7);  // attaches the servo on pin 9 to the servo object
  fingerServos[1].attach(8);  // attaches the servo on pin 9 to the servo object
  fingerServos[2].attach(9);  // attaches the servo on pin 9 to the servo object
  fingerServos[3].attach(10);  // attaches the servo on pin 9 to the servo object
  fingerServos[4].attach(11);  // attaches the servo on pin 9 to the servo object
}

void loop() {
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
  }
  moveServo(0);
  moveServo(1);
  moveServo(2);
  moveServo(3);
  moveServo(4);
}

void moveServo(int servoNumber) {
  if (FingerPositions[servoNumber] == 1) {
    fingerServos[servoNumber].write(90);
  } else if (FingerPositions[servoNumber] == 2) {
    fingerServos[servoNumber].write(0);
  } else {
    fingerServos[servoNumber].write(180);
  }
}
