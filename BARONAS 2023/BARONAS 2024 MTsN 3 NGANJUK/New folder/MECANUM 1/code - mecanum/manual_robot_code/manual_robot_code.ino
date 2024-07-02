//Project : Manual Robot Baronas 2024
//Board   : Arduino Mega
//Author  : Helda Pratama

#include "hardware.h"
#include "motor.h"

void setup() {
  hardwareInit();
}

void loop() {
  ps2x.read_gamepad(false, vibrate);
  readAnalogStick();

  //Motor Drive
  if (key_r1) {
    if (key_r2) runningSpeed = 200;
    else runningSpeed = 180;
  } else if (key_r2) runningSpeed = 250;
  else runningSpeed = 180;

  if (key_up || analog.ly > 30) vx = runningSpeed;
  else if (key_down || analog.ly < -30) vx = -runningSpeed;
  else vx = 0;

  if (key_right || analog.lx < -30) vy = runningSpeed;
  else if (key_left || analog.lx > 30) vy = -runningSpeed;
  else vy = 0;

  if (analog.rx < -30) vphi = runningSpeed;
  else if (analog.rx > 30) vphi = -runningSpeed;
  else vphi = 0;

  omniDrive(vx, vy, vphi);

  //Servo Drive
  if (key_triangle) {
    if (gripKubus) {
      servoGrip.write(160);
      gripKubus = false;
      delay(10);
    } else {
      servoGrip.write(60);
      gripKubus = true;
      delay(10);
    }
  }

  if (key_square) {
    if (liftBola) {
      servo2Lift.write(60);  //turun
      liftBola = false;
      delay(10);
    } else {
      servo2Lift.write(150);  //naik
      liftBola = true;
      delay(10);
    }
  }

  if (key_circle) {
    if (gripBola1) {
      servo2GripLeft.write(30);  //buka
      gripBola1 = false;
      delay(30);
    } else {
      servo2GripLeft.write(100);  //tutup
      gripBola1 = true;
      delay(30);
    }
  }

  if (key_cross) {
    if (gripBola2) {
      servo2GripRight.write(30);  //buka
      gripBola2 = false;
      delay(10);
    } else {
      servo2GripRight.write(100);  //tutup
      gripBola2 = true;
      delay(10);
    }
  }

  if (key_l1) {
    jumlahTekanL1++;
    if (jumlahTekanL1 == 1) {
      servoLift.write(90);
      delay(10);
    } else if (jumlahTekanL1 == 2) {
      servoLift.write(160);
      delay(10);

      jumlahTekanL1 = 0;
    }
  }

  if (key_l2) {
    servoLift.write(50);
    delay(10);
  }

}
