#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;

#define RST_PIN 5  // RST pin
#define SS_PIN 4   // SDA pin

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

#define LCD_ADDR 0x27  // Sesuaikan alamat LCD sesuai dengan perangkat Anda

// Ukuran LCD (20x4)
#define LCD_COLUMNS 20
#define LCD_ROWS 4

// Inisialisasi objek LCD
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLUMNS, LCD_ROWS);

// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 26;  // Connects to module's RX
static const uint8_t PIN_MP3_RX = 27;  // Connects to module's TX
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  SPI.begin();         // Init SPI bus
  mfrc522.PCD_Init();  // Init MFRC522

  Serial.println("Scan your RFID tag...");

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }

  wifiMulti.addAP("rifai", "12345678");
  Wire.begin();     // Init I2C bus for LCD
  lcd.begin();      // Init LCD
  lcd.backlight();  // Turn on backlight
  lcd.clear();

  lcd.setCursor(2, 1);
  lcd.print("Tempelkan kartu");
  lcd.setCursor(6, 2);
  lcd.print("RFID Anda");

  softwareSerial.begin(9600);
  player.begin(softwareSerial);
  player.volume(30);

}

void loop() {
  // if (player.begin(softwareSerial)) {
  //   Serial.println("OK");

  //   // Set volume to maximum (0 to 30).
  //   player.volume(30);
  //   // Play the first MP3 file on the SD card
    
  // } else {
  //   Serial.println("Connecting to DFPlayer Mini failed!");
  // }

  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Print UID of the card
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  if (content != "") {
    Serial.println();
    Serial.print("Message : ");
    content.toUpperCase();
    Serial.println(content);
    lcd.clear();
    lcd.setCursor(2, 1);
    lcd.print("Tunggu Sebentar");
    update(content);
    delay(2000);
    lcd.setCursor(2, 1);
    lcd.print("Tempelkan kartu");
    lcd.setCursor(6, 2);
    lcd.print("RFID Anda");
    content = "";
  }

  delay(1000);
}

void update(String rfid) {
  int loop = 1;
  while (loop == 1) {
    if ((wifiMulti.run() == WL_CONNECTED)) {

      HTTPClient http;

      USE_SERIAL.print("[HTTP] begin...\n");
      // configure traged server and url
      //http.begin("https://www.howsmyssl.com/a/check", ca); //HTTPS
      String link = "https://script.google.com/macros/s/AKfycbysGbAYwN_buI6FgSjGfjS5FsMYwfv7Jt7NiLKTCIlDuoreTyPzJFN4hF6Nmj4fomTeuQ/exec?action=update&a=";
      link += rfid;
      link += "&b=masuk&c=1";
      http.setFollowRedirects(HTTPC_FORCE_FOLLOW_REDIRECTS);
      http.begin(link);  //HTTP

      USE_SERIAL.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          USE_SERIAL.println(payload);
          // if (payload.indexOf("diperbarui") > 0) {
          //   loop = 0;
          //   lcd.clear();
          //   lcd.setCursor(2, 1);
          //   lcd.print("Berhasil");
          //   player.play(1);
          // } else if (payload.indexOf("tidak ditemukan") > 0) {
          //   lcd.clear();
          //   lcd.setCursor(2, 1);
          //   lcd.print("Tidak Terdaftar");
          //   player.play(2);
          //   loop = 0;
          // } else {
          //   lcd.clear();
          //   lcd.setCursor(2, 1);
          //   lcd.print("Coba Lagi");
            loop = 0;
          // }
        }

      } else {
        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        lcd.clear();
        lcd.setCursor(2, 1);
        lcd.print("internet error");
      }

      http.end();
    }

    delay(500);
  }
}
