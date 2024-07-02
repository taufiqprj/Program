//editable value (boleh diedit)=========================

//pid
int kp = 5;
int kd = 10;
int maxSpeed = 230;
int minSpeed = -150;

//sensor
//int sensorSensitivity = 75;

//barcode
#define jumlahDigitBarcode  13

//char scannedBarcode[jumlahDigitBarcode];
String strScannedBarcode = "";
int codeBarcode;
String strCode1 = "6955549315068";
String strCode2 = "8998989110129";


//servo
const int gripOn = 140;
const int gripOff = 80;
const int liftUp = 120;
const int liftDown = 50;
//======================================================

//eeprom
#include <EEPROM.h>
struct eepromData {
  int tresholdSensor[16];
};
eepromData ee;

//sensor
int sensorValue;
int sensorLeft;
int sensorRight;
int sensorKiri =    0b11000000000000;
int sensorKanan =   0b00000000000011;
int sensorTengah =  0b00000111100000;
#define s1  1
#define s2  2
#define s3  3
#define s4  4
#define s5  5
#define s6  6
#define s7  7
#define s8  8
#define s9  9
#define s10 10
#define s11 11
#define s12 12
#define s13 13
#define s14 14

#define fl  15
#define fr  16
#define lr  17
#define rl  18

//pid
int rate, error, lastError, powerLeft, powerRight;
int runningSpeed = 50;

//mode sensor
#define sensorTanpaGaris  0b00000000000000
#define tanpaGaris  0
#define garisPutus  0
#define dimanapun   1

//running
/*int followLineMode;
  #define followLeft    0
  #define antiLeft      1
  #define followRight   2
  #define antiRight     3
  #define antiLeftRight 4 */

//gripper
#define pick  0
#define drop  1
int gripperState = 0;

//global
#define kiri        0
#define kanan       1
#define lurus       2
#define tanpaPutar  3
