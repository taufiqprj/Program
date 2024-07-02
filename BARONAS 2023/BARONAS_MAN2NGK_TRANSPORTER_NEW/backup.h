// /*
// PROJECT : BARONAS MAN 2 NGANJUK 2024 TRANSPORTER ROBOT MECHANUM WHEELS
// AUTHORS : 1. M. RIFA'I ALI
//           2. WILDAN TAUFIQIE D.
// */

// //ATUR SPEED DISINI
// int speed = 200;
// int speedAnalogKanan = 170;
// int speedAnalogKiri = 160;
// int speedTurbo = 230;
// int speed_basic = 0;

// //ATUR NILAI SUDUT SERVO DISINI
// int nilaiKubusTutup = 40;
// int nilaiKubusBuka = 5;

// int nilaiBola1Buka = 65;
// int nilaiBola1Tutup = 0;

// int nilaiBola2Buka = 120;
// int nilaiBola2Tutup = 50;

// /*
// KUBUS ANGKAT
// | = ANGKAT 1 ^^ / = ANGKAT 2 ^^ _ = TURUN
// */
// int nilaiKubusAngkat1 = 50;
// int nilaiKubusAngkat2 = 5;
// int nilaiKubusTurun = 170;

// /*
// BOLA ANGKAT
// | = ANGKAT 1 ^^ / = ANGKAT 2 ^^ _ = TURUN
// */
// int nilaiBolaAngkat1 = 60;
// int nilaiBolaAngkat2 = 15;
// int nilaiBola1Turun = 140;


// ////////////////////////////////>>>>>>>> JANGAN DIUBAH TANPA SEIZIN AUTHORS <<<<<<<</////////////////////
// //JOYSTICK
// #include <Ps3Controller.h>

// #define keyStart (Ps3.data.button.start)
// #define keySelect (Ps3.data.button.select)
// #define keyUp (Ps3.data.button.up)
// #define keyRight (Ps3.data.button.right)
// #define keyLeft (Ps3.data.button.left)
// #define keyDown (Ps3.data.button.down)
// #define keyL3 (Ps3.data.button.l3)
// #define keyR3 (Ps3.data.button.r3)
// #define keyL1 (Ps3.data.button.l1)
// #define keyR1 (Ps3.data.button.r1)
// #define keyL2 (Ps3.data.button.l2)
// #define keyR2 (Ps3.data.button.r2)
// #define keyTriangle (Ps3.event.button_up.triangle)
// #define keyCircle (Ps3.event.button_up.circle)
// #define keyCross (Ps3.event.button_up.cross)
// #define keySquare (Ps3.event.button_up.square)
// #define keyAnalogrx (Ps3.data.analog.stick.rx)
// #define keyAnalogry (Ps3.data.analog.stick.ry)
// #define keyAnaloglx (Ps3.data.analog.stick.lx)
// #define keyAnalogly (Ps3.data.analog.stick.ly)

// int player = 0;
// int battery = 0;

// //SERVO
// #define pinGripKubus 25
// #define pinUpKubus 26
// #define pinUpBola 33
// #define pinGripBola 32
// #define pinGripBola2 23

// static bool gripKubus = false;
// static bool upKubus = false;
// static bool upBola = false;
// static bool gripBola = false;
// static bool gripBola2 = false;

// int jumlahTekanSquare = 0;
// int jumlahTekanUpBola = 0;

// int nilaiKubus;
// int nilaiBola;
// int nilaiBola2;
// int nilaiUpKubus;
// int nilaiUpBola;

// //MOTOR DRIVER
// //DEPAN
// const int ENA_F = 19;
// const int IN1_F = 18;
// const int IN2_F = 5;
// const int IN3_F = 17;
// const int IN4_F = 16;
// const int ENB_F = 4;

// //BELAKANG
// const int ENA_R = 0;
// const int IN1_R = 2;
// const int IN2_R = 27;
// const int IN3_R = 14;
// const int IN4_R = 21;  //12
// const int ENB_R = 13;

// //POSISI START
// int starting = 0;

// /*RODA MECANUM

// || RODA 1    RODA 2 ||
//           ^^

// || RODA 3    RODA 4 ||
// */

// //DEADBAND
// int apply_deadband(int value, int deadband_width) {
//   if (abs(value) <= deadband_width) {
//     return 0;
//   } else {
//     return value;
//   }
// }

// void setup() {
//   Serial.begin(9600);
//   speed_basic = speed;

//   //SERVO
//   pinMode(pinGripKubus, OUTPUT);
//   pinMode(pinUpKubus, OUTPUT);
//   pinMode(pinUpBola, OUTPUT);
//   pinMode(pinGripBola, OUTPUT);
//   pinMode(pinGripBola2, OUTPUT);

//   //MOTOR DRIVER
//   //LEDC CHANNELS
//   ledcSetup(0, 5000, 8);
//   ledcSetup(1, 5000, 8);
//   ledcSetup(2, 5000, 8);
//   ledcSetup(3, 5000, 8);

//   //ASSIGN LEDC CHANNELS TO GPIO PINS
//   ledcAttachPin(ENA_F, 0);
//   ledcAttachPin(ENB_F, 1);
//   ledcAttachPin(ENA_R, 2);
//   ledcAttachPin(ENB_R, 3);

//   pinMode(IN1_F, OUTPUT);
//   pinMode(IN2_F, OUTPUT);
//   pinMode(IN3_F, OUTPUT);
//   pinMode(IN4_F, OUTPUT);

//   pinMode(IN1_R, OUTPUT);
//   pinMode(IN2_R, OUTPUT);
//   pinMode(IN3_R, OUTPUT);
//   pinMode(IN4_R, OUTPUT);

//   //JOYSTICK
//   Ps3.attach(jalan);
//   Ps3.attachOnConnect(onConnect);
//   Ps3.begin("5c:6d:20:5b:c0:c7");  // stik hitam
//   // Ps3.begin("f0:f0:02:c2:c5:cf");  // stik merah
//   //  Ps3.begin("f0:f0:02:c3:c6:cf"); // stik merah pak haris

//   //READY
//   Serial.println("Ready.");
// }

// void loop() {
//   if (!Ps3.isConnected())
//     return;

//   int rx = keyAnalogrx;
//   int ry = keyAnalogry;
//   int lx = keyAnaloglx;
//   int ly = keyAnalogly;

//   rx = apply_deadband(rx, 50);   // Deadband dengan lebar
//   ry = apply_deadband(ry, 50);   // Deadband dengan lebar
//   ly = apply_deadband(ly, 50);   // Deadband dengan lebar
//   lx = apply_deadband(lx, 100);  // Deadband dengan lebar
//   //JALAN DENGAN TOMBOL
//   if (keyUp) {  //maju
//     set_motor(speed, speed, speed, speed);
//     delay(100);
//   } else if (keyDown) {  //mundur
//     set_motor(-speed + 1, -speed + 1, -speed + 1, -speed + 1);
//     delay(100);
//   } else if (keyRight) {  //geser kanan
//     set_motor(speed, -speed, -speed, speed);
//     delay(100);
//   } else if (keyLeft) {  //geser kiri
//     set_motor(-speed, speed, speed, -speed);
//     delay(100);
//   } else {
//     set_motor(0, 0, 0, 0);
//   }

//   //PUTAR DENGAN ANALOG
//   if (rx < -2) {  //putar kiri
//     set_motor(-speedAnalogKanan, speedAnalogKanan, -speedAnalogKanan, speedAnalogKanan);
//     delay(100);
//   } else if (rx > 2) {  //putar kanan
//     set_motor(speedAnalogKanan, -speedAnalogKanan, speedAnalogKanan, -speedAnalogKanan);
//     delay(100);
//   } else {
//     set_motor(0, 0, 0, 0);
//   }

//   //MAJU PELAN DENGAN ANALOG
//   if (ly < -2) {  //maju pelan
//     set_motor(speedAnalogKiri, speedAnalogKiri, speedAnalogKiri, speedAnalogKiri);
//     delay(100);
//   }
//   if (ly > 2) {  //mundur pelan
//     set_motor(-speedAnalogKiri, -speedAnalogKiri, -speedAnalogKiri, -speedAnalogKiri);
//     delay(100);
//   } else {
//     set_motor(0, 0, 0, 0);
//   }

//   //GESER PELAN DENGAN ANALOG
//   if (lx > 2) {  //geser kanan pelan
//     set_motor(speedAnalogKanan, -speedAnalogKanan, -speedAnalogKanan, speedAnalogKanan);
//     delay(100);
//   }
//   if (lx < -2) {  //geser kiri pelan
//     set_motor(-speedAnalogKanan, speedAnalogKanan, speedAnalogKanan, -speedAnalogKanan);
//     delay(100);
//   } else {
//     set_motor(0, 0, 0, 0);
//   }

//   //TURBO
//   if (keyL1) {  //turbo
//     speed = speedTurbo;
//   } else {
//     speed = speed_basic;
//   }

//   //SERVO
//   //GRIPPER
//   if (keyTriangle) {  //atur gripper kubus
//     if (gripKubus) {
//       nilaiKubus = nilaiKubusTutup;
//       gripKubus = false;
//     } else {
//       nilaiKubus = nilaiKubusBuka;
//       gripKubus = true;
//     }
//     delay(250);
//   }

//   if (keyCircle) {  //atur gripper bola 1
//     if (gripBola) {
//       nilaiBola = nilaiBola1Buka;
//       moveServoUp(pinGripBola, nilaiBola);
//       Serial.println("buka bola");
//       gripBola = false;
//     } else {
//       nilaiBola = nilaiBola1Tutup;
//       moveServoUp(pinGripBola, nilaiBola);
//       Serial.println("tutup bola");
//       gripBola = true;
//     }
//     delay(250);
//   }

//   if (keyCross) {  //atur gripper bola 2
//     if (gripBola2) {
//       nilaiBola2 = nilaiBola2Buka;
//       moveServoUp(pinGripBola2, nilaiBola2);
//       Serial.println("buka bola2");
//       gripBola2 = false;
//     } else {
//       nilaiBola2 = nilaiBola2Tutup;  //tutup
//       moveServoUp(pinGripBola2, nilaiBola2);
//       Serial.println("tutup bola2");
//       gripBola2 = true;
//     }
//     delay(250);
//   }

//   if (keySquare && !(keyR2 || keyL1)) {
//     jumlahTekanSquare++;

//     if (jumlahTekanSquare == 1) {
//       nilaiUpKubus = nilaiKubusTurun;
//       moveServoUp(pinUpKubus, nilaiUpKubus);
//     } else if (jumlahTekanSquare == 2) {
//       nilaiUpKubus = nilaiKubusAngkat2;
//       moveServoUp(pinUpKubus, nilaiUpKubus);
//     } else if (jumlahTekanSquare == 3) {
//       nilaiUpKubus = nilaiKubusAngkat1;
//       moveServoUp(pinUpKubus, nilaiUpKubus);
//       delay(1000);
//       jumlahTekanSquare = 0;
//     }
//     delay(250);
//   }

//   if (keySquare && (!keyR2 || keyL1)) {
//     while (nilaiUpKubus < nilaiKubusTurun) {
//       nilaiUpKubus = nilaiUpKubus + 15;
//       moveServoUp2(pinUpKubus, nilaiUpKubus);
//     }
//     delay(250);
//   }

//   if (keySquare && (keyR2 || !keyL1)) {
//     jumlahTekanUpBola++;

//     if (jumlahTekanUpBola == 1) {
//       nilaiUpBola = nilaiBola1Turun;  //turun
//       moveServoUp(pinUpBola, nilaiUpBola);
//     } else if (jumlahTekanUpBola == 2) {
//       nilaiUpBola = nilaiBolaAngkat2;  //naik
//       moveServoUp(pinUpBola, nilaiUpBola);
//     } else if (jumlahTekanUpBola == 3) {
//       nilaiUpBola = nilaiBolaAngkat1;  //naik
//       moveServoUp(pinUpBola, nilaiUpBola);
//       jumlahTekanUpBola = 0;
//     }
//     delay(250);
//   }
// }

// //FUNGSI SET MOTOR
// void set_motor(int speed_kiri_depan, int speed_kanan_depan, int speed_kiri_belakang, int speed_kanan_belakang) {

//   // Atur Kecepatan Motor Kiri Depan
//   if (speed_kiri_depan >= 0) {
//     ledcWrite(0, speed_kiri_depan);
//     digitalWrite(IN1_F, HIGH);
//     digitalWrite(IN2_F, LOW);
//   } else {
//     ledcWrite(0, -speed_kiri_depan);
//     digitalWrite(IN1_F, LOW);
//     digitalWrite(IN2_F, HIGH);
//   }

//   // Atur Kecepatan Motor Kanan Depan
//   if (speed_kanan_depan >= 0) {
//     ledcWrite(1, speed_kanan_depan);
//     digitalWrite(IN3_F, HIGH);
//     digitalWrite(IN4_F, LOW);
//   } else {
//     ledcWrite(1, -speed_kanan_depan);
//     digitalWrite(IN3_F, LOW);
//     digitalWrite(IN4_F, HIGH);
//   }

//   // Atur Kecepatan Motor Kiri Belakang
//   if (speed_kiri_belakang >= 0) {
//     ledcWrite(2, speed_kiri_belakang);
//     digitalWrite(IN1_R, HIGH);
//     digitalWrite(IN2_R, LOW);
//   } else {
//     ledcWrite(2, -speed_kiri_belakang);
//     digitalWrite(IN1_R, LOW);
//     digitalWrite(IN2_R, HIGH);
//   }

//   // Atur Kecepatan Motor Kanan Belakang
//   if (speed_kanan_belakang >= 0) {
//     ledcWrite(3, speed_kanan_belakang);
//     digitalWrite(IN3_R, HIGH);
//     digitalWrite(IN4_R, LOW);
//   } else {
//     ledcWrite(3, -speed_kanan_belakang);
//     digitalWrite(IN3_R, LOW);
//     digitalWrite(IN4_R, HIGH);
//   }

//   //PROGRAM SERVO U/ TAHAN POSISI
//   moveServo(pinGripKubus, nilaiKubus);
//   // moveServoUp2(pinUpKubus, nilaiUpKubus);
//   moveServo(pinUpBola, nilaiUpBola);
// }

// //FUNGSI UNTUK MENGGERAKKAN MOTOR SERVO KE SUDUT TERTENTU
// void moveServo(int pin, int angle) {
//   int pulseWidth = map(angle, 0, 180, 544, 2400);
//   digitalWrite(pin, HIGH);
//   delayMicroseconds(pulseWidth);
//   digitalWrite(pin, LOW);
// }

// void moveServoUp(int pin, int angle) {
//   int pulseWidth = map(angle, 0, 180, 544, 2400);

//   for (int i = 0; i < 10; i++) {
//     digitalWrite(pin, HIGH);
//     delayMicroseconds(pulseWidth);
//     digitalWrite(pin, LOW);
//     delay(10);
//   }
// }

// void moveServoUp2(int pin, int angle) {
//   // Mengkonversi sudut ke nilai PWM (puls)
//   int pulseWidth = map(angle, 0, 180, 544, 2400);

//   // Mengirim sinyal PWM ke servo
//   for (int i = 0; i < 5; i++) {
//     digitalWrite(pin, HIGH);
//     delayMicroseconds(pulseWidth);
//     digitalWrite(pin, LOW);
//     delay(10);
//   }
// }
// //FUNGSI JALAN
// void jalan() {
//   if (battery != Ps3.data.status.battery) {
//     battery = Ps3.data.status.battery;
//     Serial.print("The controller battery is ");
//     if (battery == ps3_status_battery_charging) Serial.println("charging");
//     else if (battery == ps3_status_battery_full) Serial.println("FULL");
//     else if (battery == ps3_status_battery_high) Serial.println("HIGH");
//     else if (battery == ps3_status_battery_low) Serial.println("LOW");
//     else if (battery == ps3_status_battery_dying) Serial.println("DYING");
//     else if (battery == ps3_status_battery_shutdown) Serial.println("SHUTDOWN");
//     else Serial.println("UNDEFINED");
//   }
// }

// //FUNGSI CONNECT
// void onConnect() {
//   Serial.println("Connected.");
// }
