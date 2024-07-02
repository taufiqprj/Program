//TRANSMITTER

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN
const byte address[10] = "ADDRESS1";


const int buttonPin = 2;  // Pin untuk tombol

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  pinMode(buttonPin, INPUT_PULLUP);  // Mengatur pin tombol sebagai input dengan pull-up resistor

}

void loop() {
  // Jika tombol ditekan
  if (digitalRead(buttonPin) == LOW) {
    const char text[] = "TURU LEEEEE";
    radio.write(&text, sizeof(text));
    Serial.println("Pesan berhasil dikirim");
    delay(1000);  // Mencegah pengiriman berulang saat tombol ditekan
  }

  // Logika tambahan dapat ditambahkan di sini

  // Selalu kirim pesan "hello world" setiap detik
  // const char textHello[] = "hello world";
  // radio.write(&textHello, sizeof(textHello));
  // delay(1000);
}
