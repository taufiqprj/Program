void welcomeScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("XELERON X   rev0");
  lcd.setCursor(0, 1);
  lcd.print("Arduino Mode    ");
  delay(500);
  lcd.clear();
}

void homeScreen() {

  while (1) {
    digitalWrite(motorEnable, 1);
    digitalWrite(lcdBackLight, 1);
    setMotor(0, 0);
    readSensor();
    lcd.setCursor(0, 1);
    lcd.print("Run         Scan");
    if (!digitalRead(buttonBack)) scanSensor();
    if (!digitalRead(buttonOk)) break;
  }
  lcd.clear();
  delay(300);
  digitalWrite(motorEnable, 0);
  delay(200);
}
