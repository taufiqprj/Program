// Playing a digital WAV recording repeatadly using the XTronical DAC Audio library
// prints out to the serial monitor numbers counting up showing that the sound plays
// independently of the main loop
// See www.xtronical.com for write ups on sound, the hardware required and how to make
// the wav files and include them in your code

#include "SoundData.h"
#include "XT_DAC_Audio.h"

#include <Arduino.h>

// Fungsi yang akan dijalankan pada core 0
void taskCore0(void *parameter) {
  for (;;) {
    Serial.println("Core 0 is running");
    delay(1000);
  }
}

const int potPin = 34;

int value = 0;
int lastvalue = 0;

XT_Wav_Class Sample(Bass1);
XT_Wav_Class Sample2(Bass2);
// XT_Wav_Class Cymbal(Cym1);

XT_DAC_Audio_Class DacAudio(25, 0);  // Create the main player class object.
                                     // Use GPIO 25, one of the 2 DAC pins and timer 0

uint32_t DemoCounter = 0;  // Just a counter to use in the serial monitor
                           // not essential to playing the sound

void setup() {
  Serial.begin(115200);  // Not needed for sound, just to demo printing to the serial
                         // Monitor whilst the sound plays, ensure your serial monitor
                         // speed is set to this speed also.
  xTaskCreatePinnedToCore(
    taskCore0,    // Fungsi yang akan dijalankan pada core 0
    "TaskCore0",  // Nama task
    10000,        // Ukuran tumpukan task (bytes)
    NULL,         // Argumen yang akan diteruskan ke fungsi
    1,            // Prioritas task
    NULL,         // Handle task (opsional)
    0             // Nomor core (0 untuk core 0)
  );
}


void loop() {
  DacAudio.FillBuffer();  // Fill the sound buffer with data
                          // if(ForceWithYou.Playing==false)       // if not playing,
  // DacAudio.Play(&ForceWithYou);  // play it, this will cause it to repeat and repeat...
  // delay(1000);
  value = 0;
  for (int i = 0; i < 5; i++) {
    value += analogRead(potPin);
    delay(1);
  }
  Serial.println(value);
  if (value > 100 and lastvalue == 0) {
    DacAudio.Play(&Sample2);
    // delay(50);

    while (1) {
      value = 0;
      for (int a = 0; a < 5; a++) {
        value += analogRead(potPin);
        delay(1);
      }
      if (value == 0) {
        // delay(100);
        lastvalue = 1;
        break;
      }
    }
  } else {
    lastvalue = 0;
  }


  // Serial.println(DemoCounter++);        // Showing that the sound will play as well as your code running here.
}
