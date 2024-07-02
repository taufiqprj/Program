/*//lcd
#include <LiquidCrystal.h>
#define lcdRS 0
#define lcdEN 1
#define lcdD4 5
#define lcdD5 6
#define lcdD6 7
#define lcdD7 3
#define lcdBackLight  4
LiquidCrystal lcd(lcdRS, lcdEN, lcdD4, lcdD5, lcdD6, lcdD7);

//button
#define buttonOK    2
#define buttonUp    A1
#define buttonDown  A2
#define buttonBack  21
#define buttonPlus  A7
#define buttonMin   19
#define buttonUnpressed (digitalRead(buttonOK)&&digitalRead(buttonUp)&&digitalRead(buttonDown)&&digitalRead(buttonBack)&&digitalRead(buttonPlus)&&digitalRead(buttonMin))
#define buttonPressed   !buttonUnpressed

//sensor
#define enableSensorRight 22
#define enableSensorLeft  23

//motor
#define motorDirLeft  11
#define motorDirRight 14
#define motorPWMLeft  12
#define motorPWMRight 13
#define motorEnable   9

//servo
#include <Servo.h>
Servo lift;
Servo grip;

//obstacle
#define obsPin    8

void hardwareInit() {
  lcd.begin(16, 2);
  lift.attach(18);
  grip.attach(20);
  pinMode(obsPin, INPUT_PULLUP);
  pinMode(buttonOK, INPUT_PULLUP);
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonBack, INPUT_PULLUP);
  pinMode(buttonPlus, INPUT_PULLUP);
  pinMode(buttonMin, INPUT_PULLUP);
  pinMode(lcdBackLight, OUTPUT);
  pinMode(motorDirLeft, OUTPUT);
  pinMode(motorDirRight, OUTPUT);
  pinMode(motorEnable, OUTPUT);
  digitalWrite(lcdBackLight, 1);
  digitalWrite(motorEnable, 1);
  lift.write(liftDown);
  grip.write(gripOff);
} */

//lcd
#include <LiquidCrystal.h>
#define lcdRS 0
#define lcdEN 1
#define lcdD4 5
#define lcdD5 6
#define lcdD6 7
#define lcdD7 3
#define lcdBackLight  4
LiquidCrystal lcd(lcdRS, lcdEN, lcdD4, lcdD5, lcdD6, lcdD7);

//button
#define buttonOk    2
#define buttonUp    A1
#define buttonDown  A2
#define buttonBack  21
#define buttonPlus  A7
#define buttonMin   19
#define buttonUnpressed (digitalRead(buttonOk)&&digitalRead(buttonUp)&&digitalRead(buttonDown)&&digitalRead(buttonBack)&&digitalRead(buttonPlus)&&digitalRead(buttonMin))
#define buttonPressed   !buttonUnpressed

//sensor
#define enableSensorNarrow  22
#define enableSensorWide    23

//motor
#define motorDirLeft  11
#define motorDirRight 14
#define motorPWMLeft  12
#define motorPWMRight 13
#define motorEnable   9

//servo
#include <Servo.h>
Servo servoGrip;
Servo servoLift;
#define servoPinC2  18
#define servoPinC4  20

//external
#define ext1Pin     9       //input obs
#define ext2Pin     15      //relay pelontar

//serial bluetooth
#include <SoftwareSerial.h>
SoftwareSerial mySerial(16, 17);  //Rx, Tx

void hardwareInit() {
  lcd.begin(16, 2);
  pinMode(buttonOk, INPUT_PULLUP);
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  pinMode(buttonBack, INPUT_PULLUP);
  pinMode(buttonPlus, INPUT_PULLUP);
  pinMode(buttonMin, INPUT_PULLUP);
  pinMode(lcdBackLight, OUTPUT);
  pinMode(motorDirLeft, OUTPUT);
  pinMode(motorDirRight, OUTPUT);
  pinMode(motorEnable, OUTPUT);
  pinMode(enableSensorNarrow, OUTPUT);
  pinMode(enableSensorWide, OUTPUT);

  pinMode(ext1Pin, INPUT_PULLUP);
  pinMode(ext2Pin, OUTPUT);

  digitalWrite(lcdBackLight, 1);
  digitalWrite(motorEnable, 1);

  digitalWrite(ext2Pin, 0);

  servoGrip.attach(servoPinC2);
  servoLift.attach(servoPinC4);
}
