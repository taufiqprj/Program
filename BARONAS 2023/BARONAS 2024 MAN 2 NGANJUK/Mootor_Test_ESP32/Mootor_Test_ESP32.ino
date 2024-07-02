#include <Arduino.h>
#include <Ps3Controller.h>
#include <ESP32Servo.h>

Servo myservo, myservo2;

const int ENA_F = 19;
const int IN1_F = 18;
const int IN2_F = 5;
const int IN3_F = 17;
const int IN4_F = 16;
const int ENB_F = 4;

const int ENA_R = 0;
const int IN1_R = 2;
const int IN2_R = 27;
const int IN3_R = 12;
const int IN4_R = 14;
const int ENB_R = 13;

int run = 0;
int speed = 170;
int speed_lose = 80;
int speed_basic = 0;

int sudut = 0;

int player = 0;
int battery = 0;
int state = 0;

/////////////////////////////////////////

// Define variables for PID control
double error = 0.0;
int setpoint = 90;  // Desired angle

// Define variables for motor control
int speedLeft = 0;
int speedRight = 0;
String data;
////////////////////////////////

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
  Serial2.begin(9600);
  speed_basic = speed;
  // myservo.attach(servoPin);
  // myservo2.attach(servoPin2);
  // myservo.write(0);

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
  // Ps3.begin("5c:6d:20:5b:c0:c7"); // stik hitam
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
  rx = apply_deadband(rx, 50);  // Deadband dengan lebar
  ry = apply_deadband(ry, 50);  // Deadband dengan lebar
  ly = apply_deadband(ly, 50);  // Deadband dengan lebar
  lx = apply_deadband(lx, 50);  // Deadband dengan lebar

  if (Ps3.data.button.up) {
    set_motor(speed - 20, speed, speed, speed);
    // maju();
    // set_motor(230, 180, 180, 180);
    // Serial.println("maju");
  }
  if (Ps3.data.button.down) {
    set_motor(-speed + 1, -speed + 1, -speed + 1, -speed + 1);
    // set_motor(-230, -170, -170, -170);
    // Serial.println("mundur");
  }
  if (Ps3.data.button.right) {
    set_motor(speed - 5, -speed, -speed, speed);
    // set_motor(180, -180, -180, 180);
    // Serial.println("kanan");
  }
  if (Ps3.data.button.left) {
    set_motor(-speed, speed, speed, -speed);
    // set_motor(-180, 180, 180, -180);
    // Serial.println("kiri");
  }
  if (rx < -2) {  //putar kiri
    // set_motor(-speed - 50, speed, -speed+7, speed);
    // set_motor(-200, 160, -160, 160);
    set_motor(-160, 160, -160, 160);
    Serial.println("putar kiri");
    // setpoint=cek_kompas();
    // delay(1000);
    // Serial.println(setpoint);
    // delay(10);
  }
  if (rx > 2) {  //putar kanan
    // set_motor(speed + 65, -speed + 7, speed, -speed + 7);
    // set_motor(200, -160, 160, -160);
    set_motor(160, -160, 160, -160);
    Serial.println("putar kanan");
    // setpoint=cek_kompas();
    // delay(1000);
    // Serial.println(setpoint);
    // delay(10);
  }
  
  if (lx < -2) {
    // set_motor(0, 180, 180, 0);
    set_motor(180, 0, 0, 180);
    Serial.println("serong kanan depan");
  }
  if (lx > 2) {
    set_motor(0, -180, -180, 0);
    Serial.println("serong kanan belakang");
  }
  if (ly < -2) {
    // set_motor(180, 0, 0, 180);
    set_motor(0, 180, 180, 0);
    Serial.println("serong kiri depan");
    // delay(50);
  }
   if (ly > 2) {
    set_motor(-180, 0, 0, -180);
    Serial.println("serong kiri belakang");
    // delay(50);
  }
  if (Ps3.data.button.r1) {
    speed = speed_basic + 50;
    // Serial.println("turbo");
  } else {
    speed = speed_basic;
    // Serial.println("turbooff");
  }
  if (Ps3.data.button.start) {
    set_motor(0,0,0,0);
    // set_motor(180, -180, -180, 180);
    // Serial.println("kanan");
  }
  if (Ps3.data.button.select) {
    set_motor(0,0,0,0);
  }
  if (Ps3.data.button.triangle && !Ps3.data.button.r2) {
    Serial.println("buka kiri");
  }
  if (Ps3.data.button.triangle && Ps3.data.button.r2) {
    Serial.println("tutup kiri");
  }
  if (Ps3.data.button.circle && !Ps3.data.button.r2) {
    Serial.println("buka kanan");
  }
  if (Ps3.data.button.circle && Ps3.data.button.r2) {
    Serial.println("tutup kanan");
  }
  if (Ps3.data.button.l1 && !Ps3.data.button.r2) {
    Serial.println("naik depan");
  }
  if (Ps3.data.button.l1 && Ps3.data.button.r2) {
    Serial.println("turun depan");
  }
  if (Ps3.data.button.l2 && !Ps3.data.button.r2) {
    Serial.println("naik belakang");
  }
  if (Ps3.data.button.l2 && Ps3.data.button.r2) {
    Serial.println("turun belakang");
  }

  // if( abs(Ps3.event.analog_changed.stick.lx) + abs(Ps3.event.analog_changed.stick.ly) > 2 ){
  //      Serial.print("Moved the left stick:");
  //      Serial.print(" x="); Serial.print(Ps3.data.analog.stick.lx, DEC);
  //      Serial.print(" y="); Serial.print(Ps3.data.analog.stick.ly, DEC);
  //      Serial.println();
  //   }

  // if (Ps3.data.button.r2) {
  //   for (int i =0;i<10;i++){

  //   }
  // }
  // if (Ps3.event.button_down.triangle) {
  //   myservo.attach(servoPin);
  //   myservo.write(73);
  //   Serial.println("buka");
  // }
  // if (Ps3.event.button_down.circle) {
  //   myservo.attach(servoPin);
  //   myservo.write(0);
  //   Serial.println("tutup");
  // }
  // if (Ps3.event.button_down.square) {
  //   myservo2.attach(servoPin2);
  //   myservo2.write(73);
  //   Serial.println("buka");
  // }
  // if (Ps3.event.button_down.cross) {
  //   myservo2.attach(servoPin2);
  //   myservo2.write(0);
  //   Serial.println("tutup");
  // }
  if (run == 1) {
    set_motor(speed - 20, speed, speed, speed);
  }
  if (state == 0) {
    set_motor(0, 0, 0, 0);
    // Serial.println("stop");
  }`

  state = 0;
  // delay(50);
}


void set_motor(int speed_kiri_depan, int speed_kanan_depan, int speed_kiri_belakang, int speed_kanan_belakang) {
  // Atur Kecepatan Motor Kiri Depan
  if (speed_kanan_depan != 0) {
    state = 1;
  }
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
}
int cek_kompas() {
  int tampung_data = 0;
  Serial2.print("ax");
  // Serial.println("gggggg");
  while (!Serial2.available() > 0) {
  }

  while (Serial2.available() > 0) {
    // delay(10);
    data = Serial2.readStringUntil('x');
  }
  if (data.length() > 0) {
    // Serial.println(data);
    tampung_data = data.toInt();
    data = "";



  }

  return tampung_data;
}

void maju() {
  int degrees = cek_kompas();

  degrees = degrees + setpoint;
  int set = setpoint + setpoint;
  if (degrees > set + 180) {
    error = 0 - set - (360 - degrees);
    speedLeft = constrain(180 - error * 2, -255, 255);
    speedRight = constrain(180 + error * 2, -255, 255);
  } else {
    error = degrees - set;
    speedLeft = constrain(180 - error * 2, -255, 255);
    speedRight = constrain(180 + error * 2, -255, 255);
  }

  Serial.print("Angle: ");
  Serial.print(degrees - setpoint);
  Serial.print(" degrees, Speed Left: ");
  Serial.print(speedLeft);
  Serial.print(", Speed Right: ");
  Serial.println(speedRight);

  set_motor(speedLeft, speedRight, speedLeft, speedRight);
}
