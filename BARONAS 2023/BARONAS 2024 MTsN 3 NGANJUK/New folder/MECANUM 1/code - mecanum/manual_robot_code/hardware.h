/*Hardware Pinout

  Stik PS
  data    14
  cmd     15
  clk     16
  att     17

  Motor Omni
  motor1 enable 2
  motor1 pwm    3
  motor2 enable 4
  motor2 pwm    5
  motor3 enable 6
  motor3 pwm    7
  motor4 enable 8
  motor4 pwm    9

  Servo
  servo grip    10
  servo lift    11

*/

//PS2
#include <PS2X_lib.h>
#define dataPin 14
#define cmdPin 15
#define attPin 17
#define clkPin 16
#define pressures false
#define rumble false
PS2X ps2x;
int error = 0;
byte type = 0;
byte vibrate = 0;

#define key_start (ps2x.Button(PSB_START))
#define key_select (ps2x.Button(PSB_SELECT))
#define key_up (ps2x.Button(PSB_PAD_UP))
#define key_right (ps2x.Button(PSB_PAD_RIGHT))
#define key_left (ps2x.Button(PSB_PAD_LEFT))
#define key_down (ps2x.Button(PSB_PAD_DOWN))
#define key_l3 (ps2x.Button(PSB_L3))
#define key_r3 (ps2x.Button(PSB_R3))
#define key_l1 (ps2x.ButtonPressed(PSB_L1))
#define key_r1 (ps2x.Button(PSB_R1))
#define key_l2 (ps2x.Button(PSB_L2))
#define key_r2 (ps2x.Button(PSB_R2))
#define key_triangle (ps2x.ButtonPressed(PSB_TRIANGLE))
#define key_circle (ps2x.ButtonPressed(PSB_CIRCLE))
#define key_cross (ps2x.ButtonPressed(PSB_CROSS))
#define key_square (ps2x.ButtonPressed(PSB_SQUARE))

int key_analog_up = 0;
int key_analog_down = 0;
int key_analog_left = 0;
int key_analog_right = 0;

struct {
  int lx;
  int ly;
  int rx;
  int ry;
} analog;

void readAnalogStick() {
  analog.ly = 128 - (ps2x.Analog(PSS_LY));
  analog.lx = 128 - (ps2x.Analog(PSS_LX));
  analog.ry = 128 - (ps2x.Analog(PSS_RY));
  analog.rx = 128 - (ps2x.Analog(PSS_RX));
}

//Motor Omni
#define dir1Pin 2
#define pwm1Pin 3
#define dir2Pin 4
#define pwm2Pin 5
#define dir3Pin 6
#define pwm3Pin 7
#define dir4Pin 8
#define pwm4Pin 9
int runningSpeed, vx, vy, vphi;

//Servo
#include <Servo.h>
#define servoGripPin 10
#define servoLiftPin 11
#define servo2GripLeftPin 12
#define servo2GripRightPin 13
#define servo2LiftPin 44
Servo servoGrip;
Servo servoLift;
Servo servo2GripLeft;
Servo servo2GripRight;
Servo servo2Lift;

const int grip2LeftTake = 50;
const int grip2LeftRelease = 100;
const int grip2RightTake = 50;
const int grip2RightRelease = 100;

static bool gripKubus = false;
static bool liftBola = false;
static bool gripBola1 = false;
static bool gripBola2 = false;

int servoGripState = 90;
int gripLeftState = 0;
int gripRightState = 0;

int jumlahTekanL1 = 0;

void hardwareInit() {
  Serial.begin(9600);
  pinMode(dir1Pin, OUTPUT);
  pinMode(dir2Pin, OUTPUT);
  pinMode(dir3Pin, OUTPUT);
  pinMode(dir4Pin, OUTPUT);
  digitalWrite(dir1Pin, 0);
  digitalWrite(dir2Pin, 0);
  digitalWrite(dir3Pin, 0);
  digitalWrite(dir4Pin, 0);

  servoGrip.attach(servoGripPin);
  servoLift.attach(servoLiftPin);
  servo2GripLeft.attach(servo2GripLeftPin);
  servo2GripRight.attach(servo2GripRightPin);
  servo2Lift.attach(servo2LiftPin);

atas:
  Serial.println("Find Controller");
  error = ps2x.config_gamepad(clkPin, cmdPin, attPin, dataPin, pressures, rumble);
  if (error != 0) {
    delay(1000);
    goto atas;
  }
  int type = ps2x.readType();
  switch (type) {
    case 0: Serial.println("Unknown Controller type found "); break;
    case 1: Serial.println("DualShock Controller found "); break;
    case 2: Serial.println("GuitarHero Controller found "); break;
    case 3: Serial.println("Wireless Sony DualShock Controller found "); break;
  }
  Serial.println("OK Detected");
}
