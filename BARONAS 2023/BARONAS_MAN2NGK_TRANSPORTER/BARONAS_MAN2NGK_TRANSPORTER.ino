/*
Project : BARONAS 2024 MAN 2 NGANJUK
          TRANSPORTER ROBOT MECHANUM WHEELS
Authors : - Wildan Taufiqie D.
*/
#include <Arduino.h>
#include <Ps3Controller.h>

//Pin Servvo
#define pinGripKubus 25
#define pinUpKubus 26
#define pinUpBola 33
#define pinGripBola 32
#define pinGripBola2 23

//Global Variable
static bool gripKubus = false;
static bool upKubus = false;
static bool upBola = false;
static bool gripBola = false;
static bool gripBola2 = false;

int jumlahTekanSquare = 0;
int jumlahTekanUpBola = 0;

//Posisi Awal gripper ketika connect
int nilaiKubus = 45;
int nilaiUpKubus = 180;
int nilaiUpBola = 60;
int nilaiBola = 33;
int nilaiBola2 = 80;

//Inisialisasi pin Motor Driver
//Motor Depan
const int ENA_F = 19;
const int IN1_F = 18;
const int IN2_F = 5;
const int IN3_F = 17;
const int IN4_F = 16;
const int ENB_F = 4;

//Motor Belakang
const int ENA_R = 0;
const int IN1_R = 2;
const int IN2_R = 27;
const int IN3_R = 14;
const int IN4_R = 12;  //12 ; 21
const int ENB_R = 13;

//Atur Speed
int run = 0;
int speed = 200;
int speed_lose = 80;
int speed_basic = 0;

int player = 0;
int battery = 0;
int state = 0;
int starting = 0;

/*RODA MECANUM

|| RODA 1    RODA 2 ||


|| RODA 3    RODA 4 ||
*/

// Fungsi deadband
int apply_deadband(int value, int deadband_width) {
  if (abs(value) <= deadband_width) {
    return 0;
  } else {
    return value;
  }
}

void onConnect() {
  Serial.println("Connected.");
}

void jalan() {
  if (battery != Ps3.data.status.battery) {
    battery = Ps3.data.status.battery;
    Serial.print("The controller battery is ");
    if (battery == ps3_status_battery_charging) Serial.println("charging");
    else if (battery == ps3_status_battery_full) Serial.println("FULL");
    else if (battery == ps3_status_battery_high) Serial.println("HIGH");
    else if (battery == ps3_status_battery_low) Serial.println("LOW");
    else if (battery == ps3_status_battery_dying) Serial.println("DYING");
    else if (battery == ps3_status_battery_shutdown) Serial.println("SHUTDOWN");
    else Serial.println("UNDEFINED");
  }
}

void setup() {
  Serial.begin(9600);
  speed_basic = speed;

  //Inisialisasi pin servo
  pinMode(pinGripKubus, OUTPUT);
  pinMode(pinUpKubus, OUTPUT);
  pinMode(pinUpBola, OUTPUT);
  pinMode(pinGripBola, OUTPUT);
  pinMode(pinGripBola2, OUTPUT);

  // Inisialisasi LEDC channels
  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  ledcSetup(2, 5000, 8);
  ledcSetup(3, 5000, 8);

  // Assign LEDC channels to GPIO pins
  ledcAttachPin(ENA_F, 0);
  ledcAttachPin(ENB_F, 1);
  ledcAttachPin(ENA_R, 2);
  ledcAttachPin(ENB_R, 3);

  pinMode(IN1_F, OUTPUT);
  pinMode(IN2_F, OUTPUT);
  pinMode(IN3_F, OUTPUT);
  pinMode(IN4_F, OUTPUT);

  pinMode(IN1_R, OUTPUT);
  pinMode(IN2_R, OUTPUT);
  pinMode(IN3_R, OUTPUT);
  pinMode(IN4_R, OUTPUT);

  Ps3.attach(jalan);
  Ps3.attachOnConnect(onConnect);
  // Ps3.begin("5c:6d:20:5b:c0:c7");  // stik hitam
  Ps3.begin("f0:f0:02:c2:c5:cf"); // stik merah
  //  Ps3.begin("f0:f0:02:c3:c6:cf"); // stik merah pak haris

  Serial.println("Ready.");
}

void loop() {
  if (!Ps3.isConnected())
    return;
  int rx = Ps3.data.analog.stick.rx;
  int ry = Ps3.data.analog.stick.ry;
  int ly = Ps3.data.analog.stick.ly;
  int lx = Ps3.data.analog.stick.lx;
  rx = apply_deadband(rx, 50);   // Deadband dengan lebar
  ry = apply_deadband(ry, 50);   // Deadband dengan lebar
  ly = apply_deadband(ly, 50);   // Deadband dengan lebar
  lx = apply_deadband(lx, 100);  // Deadband dengan lebar

  //servo
  //gripper

  if (Ps3.data.button.triangle) {  //atur gripper kubus
    if (gripKubus) {
      nilaiKubus = 48;
      Serial.println("buka belakang");
      gripKubus = false;
    } else {
      nilaiKubus = 5;
      Serial.println("tutup belakang");
      gripKubus = true;
    }
    delay(250);
  }

  if (Ps3.data.button.circle) {  //atur gripper bola 1
    if (gripBola) {
      nilaiBola = 65;
      moveServoUp(pinGripBola, nilaiBola);
      Serial.println("tutup bola");
      gripBola = false;
    } else {
      nilaiBola = 0;
      moveServoUp(pinGripBola, nilaiBola);
      Serial.println("buka bola");
      gripBola = true;
    }
    delay(250);
  }

  if (Ps3.data.button.cross) {  //atur gripper bola 2
    if (gripBola2) {
      nilaiBola2 = 120;
      moveServoUp(pinGripBola2, nilaiBola2);
      Serial.println("buka bola2");
      gripBola2 = false;
    } else {
      nilaiBola2 = 50;  //tutup
      moveServoUp(pinGripBola2, nilaiBola2);
      Serial.println("tutup bola2");
      gripBola2 = true;
    }
    delay(250);
  }

  // Definisikan variabel global untuk melacak jumlah kali tombol kotak ditekan

  if (Ps3.data.button.square && !(Ps3.data.button.r2 || Ps3.data.button.l1)) {
    // Tambahkan 1 ke jumlahTekanSquare setiap kali tombol kotak ditekan
    jumlahTekanSquare++;

    // Atur sudut servo berdasarkan jumlahTekanSquare
    if (jumlahTekanSquare == 1) {
      nilaiUpKubus = 180;
      moveServoUp(pinUpKubus, nilaiUpKubus);
      // moveServo(pinUpKubus, nilaiUpKubus);
      // Serial.println("Servo bergerak ke sudut 180");
    } else if (jumlahTekanSquare == 2) {
      // while (nilaiUpKubus > 8) {
      //   nilaiUpKubus = nilaiUpKubus - 45;  //jika terlalu lambat ubah nilai
      //   moveServoUp(pinUpKubus, nilaiUpKubus);
      // }

      nilaiUpKubus = 0;
      moveServoUp(pinUpKubus, nilaiUpKubus);
      // moveServo(pinUpKubus, nilaiUpKubus);
      Serial.println("Servo bergerak ke sudut 5");
      // Set jumlahTekanSquare kembali ke 0 setelah mencapai ketiga kali
    } else if (jumlahTekanSquare == 3) {
      nilaiUpKubus = 50;
      moveServoUp(pinUpKubus, nilaiUpKubus);
      // moveServo(pinUpKubus, nilaiUpKubus);
      // delay(1000);
      // Serial.println("Servo bergerak ke sudut 100");11111
      jumlahTekanSquare = 0;
    }
    delay(250);
  }

  if (Ps3.data.button.square && (!Ps3.data.button.r2 || Ps3.data.button.l1)) {
    while (nilaiUpKubus < 180) {
      nilaiUpKubus = nilaiUpKubus + 10;
      moveServoUp2(pinUpKubus, nilaiUpKubus);
      // moveServo(pinUpKubus, nilaiUpKubus);
    }
    delay(250);
  }

  if (Ps3.data.button.square && (Ps3.data.button.r2 || !Ps3.data.button.l1)) {
    
    jumlahTekanUpBola++;

    if (jumlahTekanUpBola == 1) {
      nilaiUpBola = 140;  //turun
      moveServoUp(pinUpBola, nilaiUpBola);
    } else if (jumlahTekanUpBola == 2) {
      nilaiUpBola = 15;  //naik
      moveServoUp(pinUpBola, nilaiUpBola);
    } else if (jumlahTekanUpBola == 3) {
      nilaiUpBola = 60;  //naik
      moveServoUp(pinUpBola, nilaiUpBola);
      
      jumlahTekanUpBola = 0;
    }
    delay(250);
  }

  //jalan dengan tombol
  if (Ps3.data.button.up) {  //maju
    set_motor(speed, speed, speed, speed);
    delay(100);
    Serial.println("maju");
  } else if (Ps3.data.button.down) {  //mundur
    set_motor(-speed + 1, -speed + 1, -speed + 1, -speed + 1);
    delay(100);
    Serial.println("mundur");
  } else if (Ps3.data.button.right) {  //geser kanan
    set_motor(speed, -speed, -speed, speed);
    delay(100);
    // Serial.println("geskan");
  } else if (Ps3.data.button.left) {  //geser kiri
    set_motor(-speed, speed+10, speed, -speed);
    delay(100);
    // Serial.println("geski");
  } else {
    set_motor(0, 0, 0, 0);
  }

  //putar dengan analog
  if (rx < -2) {  //putar kiri
    set_motor(-160, 160, -160, 160);
    delay(100);
    Serial.println("putar kiri");
  } else if (rx > 2) {  //putar kanan
    set_motor(160, -160, 160, -160);
    delay(100);
    Serial.println("putar kanan");
  } else {
    set_motor(0, 0, 0, 0);
  }

  //maju pelan dengan analog
  if (ly < -2) {  //maju pelan
    set_motor(170, 170, 170, 170);
    delay(100);
    Serial.println("maju pelan");
  }
  if (ly > 2) {  //mundur pelan
    set_motor(-170, -170, -170, -170);
    delay(100);
    Serial.println("mundur pelan");
  } else {
    set_motor(0, 0, 0, 0);
  }

  //geser pelan dengan analog
  if (lx > 2) {  //geser kanan pelan
    set_motor(170, -170, -170, 170);
    delay(100);
    Serial.println("maju pelan");
  }
  if (lx < -2) {  //geser kiri pelan
    set_motor(-170, 170, 170, -170);
    delay(100);
    Serial.println("mundur pelan");
  } else {
    set_motor(0, 0, 0, 0);
  }

  //speed turbo
  if (Ps3.data.button.r1) {  //turbo
    speed = speed_basic + 20;
  } else {
    speed = speed_basic;
  }
}

void set_motor(int speed_kiri_depan, int speed_kanan_depan, int speed_kiri_belakang, int speed_kanan_belakang) {

  // Atur Kecepatan Motor Kiri Depan
  if (speed_kiri_depan >= 0) {
    ledcWrite(0, speed_kiri_depan);
    digitalWrite(IN1_F, HIGH);
    digitalWrite(IN2_F, LOW);
  } else {
    ledcWrite(0, -speed_kiri_depan);
    digitalWrite(IN1_F, LOW);
    digitalWrite(IN2_F, HIGH);
  }

  // Atur Kecepatan Motor Kanan Depan
  if (speed_kanan_depan >= 0) {
    ledcWrite(1, speed_kanan_depan);
    digitalWrite(IN3_F, HIGH);
    digitalWrite(IN4_F, LOW);
  } else {
    ledcWrite(1, -speed_kanan_depan);
    digitalWrite(IN3_F, LOW);
    digitalWrite(IN4_F, HIGH);
  }

  // Atur Kecepatan Motor Kiri Belakang
  if (speed_kiri_belakang >= 0) {
    ledcWrite(2, speed_kiri_belakang);
    digitalWrite(IN1_R, HIGH);
    digitalWrite(IN2_R, LOW);
  } else {
    ledcWrite(2, -speed_kiri_belakang);
    digitalWrite(IN1_R, LOW);
    digitalWrite(IN2_R, HIGH);
  }

  // Atur Kecepatan Motor Kanan Belakang
  if (speed_kanan_belakang >= 0) {
    ledcWrite(3, speed_kanan_belakang);
    digitalWrite(IN3_R, HIGH);
    digitalWrite(IN4_R, LOW);
  } else {
    ledcWrite(3, -speed_kanan_belakang);
    digitalWrite(IN3_R, LOW);
    digitalWrite(IN4_R, HIGH);
  }
  moveServo(pinGripKubus, nilaiKubus);
  moveServo(pinUpBola, nilaiUpBola);
  // moveServo(pinUpKubus, nilaiUpKubus);
  // moveServoUp(pinGripBola, nilaiBola);
}

// Fungsi untuk menggerakkan servo ke sudut tertentu
void moveServo(int pin, int angle) {
  // Mengkonversi sudut ke nilai PWM (puls)
  int pulseWidth = map(angle, 0, 180, 544, 2400);
  digitalWrite(pin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(pin, LOW);
  // delay(20);

  // Mengirim sinyal PWM ke servo
  // for (int i = 0; i < 10; i++) {

  // }
}

void moveServoUp2(int pin, int angle) {
  // Mengkonversi sudut ke nilai PWM (puls)
  int pulseWidth = map(angle, 0, 180, 544, 2400);


  // Mengirim sinyal PWM ke servo
  for (int i = 0; i < 10; i++) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(pin, LOW);
    delay(5);
  }
}

void moveServoUp(int pin, int angle) {
  // Mengkonversi sudut ke nilai PWM (puls)
  int pulseWidth = map(angle, 0, 180, 544, 2400);


  // Mengirim sinyal PWM ke servo
  for (int i = 0; i < 10; i++) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(pin, LOW);
    delay(20);
  }
}
