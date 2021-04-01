#include "Arduino.h"
#include <Servo.h>

#define THUMB_LOW 45
#define THUMB_MIDDLE 90
#define THUMB_HIGH 135

#define INDEX_LOW 65
#define INDEX_MIDDLE 90
#define INDEX_HIGH 120

#define MIDDLE_LOW 45
#define MIDDLE_MIDDLE 90
#define MIDDLE_HIGH 135

#define RING_LOW 45
#define RING_MIDDLE 90
#define RING_HIGH 150

#define PINKY_LOW 90
#define PINKY_MIDDLE 90
#define PINKY_HIGH 15

Servo fingerServos[5]; // create servo object to control a servo
void moveServo(int);
int FingerPositions[5] = {THUMB_LOW, INDEX_LOW, MIDDLE_LOW, RING_LOW, PINKY_LOW};
int servoAnglesLow[5] = {THUMB_LOW, INDEX_LOW, MIDDLE_LOW, RING_LOW, PINKY_LOW};
int servoAnglesHigh[5] = {THUMB_HIGH, INDEX_HIGH, MIDDLE_HIGH, RING_HIGH, PINKY_HIGH};
int servoAnglesMiddle[5] = {THUMB_MIDDLE, INDEX_MIDDLE, MIDDLE_MIDDLE, RING_MIDDLE, PINKY_MIDDLE};
String serial_cmd = "";

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Starting Program");
  delay(20);

  fingerServos[0].attach(7);  // attaches the servo on pin 7 to the servo object (thumb)
  fingerServos[1].attach(8);  // attaches the servo on pin 8 to the servo object (Index)
  fingerServos[2].attach(9);  // attaches the servo on pin 9 to the servo object (Middle)
  fingerServos[3].attach(10); // attaches the servo on pin 10 to the servo object (ring)
  fingerServos[4].attach(11); // attaches the servo on pin 11 to the servo object (pinky)
  Serial.println("Leaving Setup");
}

void loop()
{
  Serial.println("Ready-to-receive");
  if (Serial)
  {
    serial_cmd = Serial.readString();
    //Get end of serial
    int end = serial_cmd.indexOf("x");
    //Get start if serial
    int start = serial_cmd.indexOf("h");
    if (serial_cmd != "waiting" && serial_cmd != "" && serial_cmd != "NODATA")
    {
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
    moveServo(0); // Thumb
    moveServo(1); // Index
    moveServo(2); // Middle
    moveServo(4); // Pinky
    moveServo(3); // Ring
  }
  delay(20);
}

void moveServo(int servoNumber)
{
  if (FingerPositions[servoNumber] == 1)
  {
    fingerServos[servoNumber].write(servoAnglesMiddle[servoNumber]);
  }
  else if (FingerPositions[servoNumber] == 2)
  {
    fingerServos[servoNumber].write(servoAnglesLow[servoNumber]);
  }
  else
  {
    fingerServos[servoNumber].write(servoAnglesHigh[servoNumber]);
  }
}