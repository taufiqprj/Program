//RECEIVER

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo myservo;
Servo myservo2;

const int ENA = 5;  // Pin PWM untuk motor kiri
const int IN1 = 2;  // Pin kontrol arah motor kiri
const int IN2 = 3;  // Pin kontrol arah motor kiri
const int IN3 = 4;  // Pin kontrol arah motor kanan
const int IN4 = 9;  // Pin kontrol arah motor kanan
const int ENB = 6;  // Pin PWM untuk motor kanan

int run = 0;
int speed = 170;  /// speed dasar yang perlu di atur
int speed_lose = 80;
int speed_basic = 0;
int suduta[] = { 0, 110, 170};

RF24 radio(7, 8);  // CE, CSN
const byte address[10] = "ADDRESS1";

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Alamat I2C LCD, ukuran 16x2
int sudut = 0;
void setup() {
  Serial.begin(9600);
  myservo2.attach(A3);
  myservo2.write(0);

  speed_basic = speed;
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(A0, OUTPUT);

  radio.begin();
  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  // lcd.backlight();
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print(" ~LORD FORTUNE~");
  lcd.setCursor(0, 1);
  lcd.print("MAN 2 NGANJUK");
}

void loop() {

  if (radio.available()) {
    char text[32] = "";  // Menggunakan array yang cukup besar
    radio.read(&text, sizeof(text));

    // lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print("Pesan diterima:");
    // lcd.setCursor(0, 1);
    // lcd.print(text);

    Serial.print("Pesan diterima: ");
    Serial.println(text);
    if (String(text) == "PU") {  //maju manual
      set_motor(speed, speed);
      Serial.print("00000 ");
    }

    if (String(text) == "PD") {  /// mundur manual
      set_motor(-speed - 30, -speed);
      Serial.print("00000 ");
    }

    if (String(text) == "PR") {  ///kanan manual
      set_motor(-200, 180);
      Serial.print("00000 ");
    }

    if (String(text) == "PL") {  //// kiri manual
      set_motor(180, -200);
      Serial.print("00000 ");
    }

    if (String(text) == "R1") {  //// turbo
      speed = speed_basic + 50;
      // set_motor(200, 200);
      // set_motor(255, 230);
    }
    if (String(text) == "SELECT") {  /// stop mode otomatis
      run = 0;
      set_motor(0, 0);
    }
    if (String(text) == "R2") {  /// stop mode otomatis
      set_motor(speed, speed);
    }

    if (String(text) == "START") {  /// start mode otomatis
      run = 1;
    }
    //// naik turun gripper
    if (String(text) == "L1") {
      digitalWrite(A0, 1);
      set_motor(0, 200);
    }
    if (String(text) == "L2") {
      digitalWrite(A0, 1);
      set_motor(0, -120);
    }
    ///// PROGRAM SERVO
    if (String(text) == "A") {
      myservo.attach(A2);
      myservo.write(75);
      // myservo.detach();
    }

    if (String(text) == "O") {
      myservo.attach(A2);
      myservo.write(45);
      // myservo.detach();
    }

    if (String(text) == "X") {
    }

    if (String(text) == "D") {
     
      // myservo.detach();
    }

    //// setting kecepatan dan waktu belok analoG
    if (String(text) == "AR") {
      set_motor(-230, 230);  //kecepatan (kanan.....kiri)
      delay(200);            //waktu

    } else if (String(text) == "AL") {
      set_motor(200, -200);  //kecepatan (kanan.....kiri)
      delay(200);            //waktu
    }


    if (String(text) == "r1stop") {
      speed = speed_basic;
      digitalWrite(A0, 0);
    } else if (String(text).indexOf("stop") > 0) {
      set_motor(0, 0);
      Serial.print("Pesa ");
      digitalWrite(A0, 0);
    }
    if (String(text) == "redstop" or String(text) == "greenstop") {
      // myservo.detach();
    }
    //putar bak
    if (String(text) == "bluestop") {
      sudut = sudut + 1;
      if (sudut > 2) {
        sudut = 2;
      }
      myservo2.write(suduta[sudut]);
      // myservo.detach();
    }
    
    if (String(text) == "pinkstop") {
       sudut = sudut - 1;
      if (sudut < 0) {
        sudut = 0;
      }
      myservo2.write(suduta[sudut]);
      // myservo.detach();
    }
  }

  if (run == 1) {  //speed motor start (kanan.....kiri)
    set_motor(speed, speed);
    // set_motor(speed, speed);
    Serial.println("run run");
  }
  // Logika tambahan dapat ditambahkan di sini
}


void set_motor(int speed_kiri, int speed_kanan) {
  // Mengatur kecepatan motor kiri
  if (speed_kiri >= 0) {
    analogWrite(ENA, speed_kiri);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    analogWrite(ENA, -speed_kiri);
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }

  // Mengatur kecepatan motor kanan
  if (speed_kanan >= 0) {
    analogWrite(ENB, speed_kanan);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    analogWrite(ENB, -speed_kanan);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }
}