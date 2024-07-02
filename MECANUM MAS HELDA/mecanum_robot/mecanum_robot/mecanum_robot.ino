#include <Ps3Controller.h>

//Editable Global Variable
const int liftAscend = 250;
const int liftDescend = -250;

int runningSpeed1 = 40;
int runningSpeed2 = 90;
int runningSpeed3 = 140;
int runningSpeed4 = 200;

const int GripLeftTake = 40;
const int GripLeftRelease = 15;

const int GripRightTake = 40;  //58
const int GripRightRelease = 75;
//const int rearGripMid = 0;

const int GriperUp = 10;
const int GriperDown = 90;

double const_vy = 1.3;
double const_vphi = 1.2;

//Global Variable
static bool gripLeft = false;
static bool gripRight = false;
static bool gripUp = false;
#define front 0
#define rear 1
int heading = front;

//static bool servoRotationState = false;
int i = 0;
int rackNumber = 0;
static bool sprintState = false;

//Joystick
#define keyStart (Ps3.data.button.start)
#define keySelect (Ps3.data.button.select)
#define keyUp (Ps3.data.button.up)
#define keyRight (Ps3.data.button.right)
#define keyLeft (Ps3.data.button.left)
#define keyDown (Ps3.data.button.down)
#define keyL3 (Ps3.data.button.l3)
#define keyR3 (Ps3.data.button.r3)
#define keyL1 (Ps3.data.button.l1)
#define keyR1 (Ps3.data.button.r1)
#define keyL2 (Ps3.data.button.l2)
#define keyR2 (Ps3.data.button.r2)
#define keyTriangle (Ps3.data.button.triangle)
#define keyCircle (Ps3.data.button.circle)
#define keyCross (Ps3.data.button.cross)
#define keySquare (Ps3.data.button.square)

struct {
  int lx;
  int ly;
  int rx;
  int ry;
} analog;

//Motor
/*
      front
  1 ||       || 2
        ^^

  3 ||       || 4

  motor1 enable 27
  motor1 pwm    14
  motor2 enable 12
  motor2 pwm    13
  motor3 enable 32
  motor3 pwm    33
  motor4 enable 25
  motor4 pwm    26
*/

#define dir1Pin 27
#define pwm1Pin 14
#define dir2Pin 12
#define pwm2Pin 13
#define dir3Pin 33
#define pwm3Pin 32
#define dir4Pin 25
#define pwm4Pin 26
int runningSpeed, vx, vy, vphi;

#define motorLift1Pin 16
#define motorLift2Pin 17

//Servo
#include <ESP32_Servo.h>
#define servoGripLeftPin 19
#define servoGripUpPin 18
#define servoGripRightPin 12

Servo servoGripLeft;
Servo servoGripUp;
Servo servoGripRight;

//Limit Switch
const int bottomLSPin = 2;
const int topLSPin = 15;


void setup() {
  Serial.begin(115200);

  servoGripLeft.attach(servoGripLeftPin);
  servoGripUp.attach(servoGripUpPin);
  servoGripRight.attach(servoGripRightPin);

  servoGripRight.write(GripRightRelease);

  servoGripLeft.write(GripLeftRelease);
  servoGripUp.write(GriperUp);

  pinMode(bottomLSPin, INPUT_PULLUP);
  pinMode(topLSPin, INPUT_PULLUP);

  Ps3.begin("5c:6d:20:68:76:15");
  Serial.println("Ready.");
}

void loop() {
  readAnalogStick(0);

  //Special Key

  if (keyR1) {
    if (keyR2) runningSpeed = runningSpeed3;
    else runningSpeed = runningSpeed2;
  } else if (keyR2) runningSpeed = runningSpeed4;
  else {
    runningSpeed = runningSpeed1;
  }

  //Motor Drive
  if (keyUp || analog.ly > 30 || keyCross) vx = runningSpeed;
  else if (keyDown || analog.ly < -30 || keySquare) vx = -runningSpeed;
  else vx = 0;

  if (keyLeft || analog.lx > 30) vy = runningSpeed;
  else if (keyRight || analog.lx < -30) vy = -runningSpeed;
  else vy = 0;

  if (analog.rx > 30) vphi = -runningSpeed;
  else if (analog.rx < -30) vphi = runningSpeed;
  else vphi = 0;

  omniDrive(vx, vy, vphi);

  //lift
  if (keyL1 && digitalRead(topLSPin)) {
    setLiftMotor(liftAscend, 0);
    Serial.println("Lift Up");
    delay(20);
  } else setLiftMotor(0, 0);

  if (keyL2 && digitalRead(bottomLSPin)) {
    setLiftMotor(liftDescend, 0);
    Serial.println("Lift Down");
    delay(20);
  } else setLiftMotor(0, 0);

  if (keyStart) heading = front;
  if (keySelect) heading = rear;

  //gripper
  //servo
  if (keyCircle) {
    if (gripLeft || gripRight) {
      servoGripLeft.write(GripLeftTake);
      servoGripRight.write(GripRightTake);
      delay(100);
      setLiftMotor(liftAscend, 0);
      delay(350);
      setLiftMotor(0, 0);

      gripLeft = false;
      gripRight = false;
    } else {
      servoGripLeft.write(GripLeftRelease);
      servoGripRight.write(GripRightRelease);

      gripLeft = true;
      gripRight = true;
    }
    delay(250);
  }
  if (keyTriangle) {
    gripUp = !gripUp;
    if (gripUp) {
      servoGripUp.write(GriperUp);
    } else {
      servoGripUp.write(GriperDown);
    }
    delay(250);
  }

  if (keyR3) {
    gripRight = !gripRight;
    if (gripRight) {
      servoGripRight.write(GripRightTake);
    } else {
      servoGripRight.write(GripRightRelease);
    }
    delay(250);
  }
  if (keyL3) {
    gripLeft = !gripLeft;
    if (gripLeft) {
      servoGripLeft.write(GripLeftTake);
    } else {
      servoGripLeft.write(GripLeftRelease);
    }
    delay(250);
  }
}

void readAnalogStick(int enDebug) {
  if (enDebug) {
    Serial.print("ly:");
    Serial.print(Ps3.data.analog.stick.ly);
    Serial.print(" lx:");
    Serial.print(Ps3.data.analog.stick.lx);
    Serial.print(" ry:");
    Serial.print(Ps3.data.analog.stick.ry);
    Serial.print(" rx:");
    Serial.println(Ps3.data.analog.stick.rx);
  }
  analog.ly = (Ps3.data.analog.stick.ly);
  analog.lx = (Ps3.data.analog.stick.lx);
  analog.ry = (Ps3.data.analog.stick.ry);
  analog.rx = (Ps3.data.analog.stick.rx);
}

void setMotor(int speed1, int speed2, int speed3, int speed4) {
  Serial.print(speed1);
  Serial.print(", ");
  Serial.print(speed2);
  Serial.print(", ");
  Serial.print(speed3);
  Serial.print(", ");
  Serial.println(speed4);

  speed1 = constrain(speed1, -255, 255);
  speed2 = constrain(speed2, -255, 255);
  speed3 = constrain(speed3, -255, 255);
  speed4 = constrain(speed4, -255, 255);

  if (speed1 < 0) {
    analogWrite(dir1Pin, -speed1);
    analogWrite(pwm1Pin, 0);
  } else {
    analogWrite(dir1Pin, 0);
    analogWrite(pwm1Pin, speed1);
  }

  if (speed2 < 0) {
    analogWrite(dir2Pin, -speed2);
    analogWrite(pwm2Pin, 0);
  } else {
    analogWrite(dir2Pin, 0);
    analogWrite(pwm2Pin, speed2);
  }

  if (speed3 < 0) {
    analogWrite(dir3Pin, -speed3);
    analogWrite(pwm3Pin, 0);
  } else {
    analogWrite(dir3Pin, 0);
    analogWrite(pwm3Pin, speed3);
  }

  if (speed4 < 0) {
    analogWrite(dir4Pin, -speed4);
    analogWrite(pwm4Pin, 0);
  } else {
    analogWrite(dir4Pin, 0);
    analogWrite(pwm4Pin, speed4);
  }
}

void omniDrive(int vx, int vy, int v_phi) {
  int m1 = vx + (-(vy * const_vy)) + (-(v_phi * const_vphi));
  int m2 = vx + (vy * const_vy) + (v_phi * const_vphi);
  int m3 = vx + (vy * const_vy) + (-(v_phi * const_vphi));
  int m4 = vx + (-(vy * const_vy)) + (v_phi * const_vphi);
  setMotor(m1, m2, m3, m4);
}

void setLiftMotor(int speedLift, int enDebug) {
  if (enDebug) {
    Serial.print("Lift:");
    Serial.println(speedLift);
  }
  if (speedLift >= 0) {
    analogWrite(motorLift1Pin, speedLift);
    analogWrite(motorLift2Pin, 0);
  } else {
    analogWrite(motorLift1Pin, 0);
    analogWrite(motorLift2Pin, -speedLift);
  }
}

//Editable Semi-Auto Function
/*void indexRunning(int index) {
  switch (index) {
    case 0:  //index 0
      setMotor(-230, 230, 0);
      delay(160);
      setMotor(200, 200, 0);
      delay(250);
      //setMotor(100, 200, 0);
      // delay(550);
      break;
    case 1:  //index 1
      ///setMotor(230, 230, 0);
      //delay(250);
      // setMotor(-230, 230, 0);
      // delay(800);
      break;
    case 2:
      //setMotor(230, 230, 0);
      //delay(250);
      //setMotor(-230, 230, 0);
      //delay(800);
      break;

    case 3:  //index 1
      //setMotor(230, 230, 0);
      //delay(250);
      // setMotor(-230, 230, 0);
      // delay(800);
      break;
    case 4:  //index 1
      //setMotor(230, 230, 0);
      //delay(250);
      //setMotor(-230, 230, 0);
      // delay(800);
      break;
  }


  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(name);

  display.setCursor(0, 20);
  display.println("STTKD");

  display.setCursor(0, 40);
  display.print("i: ");
  display.println(index);
  display.display();
}
*/