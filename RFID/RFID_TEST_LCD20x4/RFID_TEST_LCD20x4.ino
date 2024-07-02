#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN     5          // RST pin
#define SS_PIN      4        // SDA pin

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

// Inisialisasi alamat I2C untuk LCD
#define LCD_ADDR 0x27 // Sesuaikan alamat LCD sesuai dengan perangkat Anda

// Ukuran LCD (20x4)
#define LCD_COLUMNS 20
#define LCD_ROWS 4

// Inisialisasi objek LCD
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLUMNS, LCD_ROWS);

void setup() {
  Serial.begin(9600);           // Initialize serial communication
  SPI.begin();                  // Init SPI bus
  mfrc522.PCD_Init();           // Init MFRC522

  Wire.begin();                 // Init I2C bus for LCD
  lcd.begin(); // Init LCD
  lcd.backlight();              // Turn on backlight

  lcd.setCursor(2, 1);
  lcd.print("Tempelkan kartu");
  lcd.setCursor(6, 2);
  lcd.print("RFID Anda");
}

void loop() {
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Print UID of the card
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RFID Tag UID:");
  lcd.setCursor(0, 1);
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      lcd.print("0");
    }
    lcd.print(mfrc522.uid.uidByte[i], HEX);
    lcd.print(" ");
  }
  delay(2000); // Tunggu sebentar sebelum kembali ke tampilan awal
  lcd.clear();
  lcd.setCursor(2, 1);
  lcd.print("Tempelkan kartu");
  lcd.setCursor(5, 2);
  lcd.print("RFID Anda");
}
