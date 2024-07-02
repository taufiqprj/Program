/*
  Project : Xeleron X - PC coding
  Author  : Helda Pratama
  Year    : 2022
  Event   : MRC 2022 - MI
*/

#include "variable.h"
#include "hardware.h"
#include "button.h"
#include "motor.h"
#include "sensor.h"
#include "panel.h"
#include "running.h"

void setup() {
  hardwareInit();
  EEPROM.get(0, ee);
  welcomeScreen();
}

void loop() {
  homeScreen();

  mainProgram();      //untuk menjalankan seluruh isi program utama

  stopMotor();
}

//isi program
void mainProgram() {
  //petunjuk program

  /*
    run(speedAwal, modeSensor, motorKiri, motorKanan, delayBelok, speedTimer, timer)
    pilihan mode sensor:
      1. fl (tengah & kiri)
      2. fr (tengah & kanan)
      3. lr atau rl (kanan & kiri)
      4. s1, s2, ... , s14 (nomor sensor)
      5. dimanapun

    contoh:
    run(80, fl, -80, 100, 300, 80, 30);  //belok kiri setelah pertigaan kiri dan jalan dgn timer 30
    run(80, fr, 100, -80, 300, 80, 30);  //belok kanan setelah pertigaan kanan dan jalan dgn timer 30
  */

  //gripperAction(pick)     untuk ambil
  //gripperAction(drop)     untuk taruh
  //lontar()    untuk melontar bola

  //===========>>>PANDUAN PROGRAM<<<===========
  // run(speedAwal, modeSensor, motorKiri, motorKanan, delayBelok, speedTimer, timer)
  // Start/maju    => run(100, dimanapun, 100, 100, 100, 100, 50); timer menyesuaikan kondisi track
  // mundur        => run(100, dimanapun, -100, -100, 100, 100, 0); delay menyesuaikan kondisi track
  // belok kiri    => run(100, fl, -150, 100, 180, 100, 50); timer menyesuaikan kondisi track
  // belok kanan   => run(100, fr, 100, -150, 180, 100, 50); timer menyesuaikan kondisi track
  // putar balik   => run(100, fr, 100, -150, 280, 100, 0);


  //masukkan program utama disini====================================================================
  

  //gripperAction(drop);

  //ending program utama
}
