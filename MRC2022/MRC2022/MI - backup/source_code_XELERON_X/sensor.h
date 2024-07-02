void setSensor(unsigned char a, unsigned char b) {
  digitalWrite(enableSensorNarrow, a);
  digitalWrite(enableSensorWide, b);
  delayMicroseconds(200);
}

void readSensor() {
  //  unsigned char xpos[12] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
  //  unsigned char adcPosNarrow[6] = {A1, A2, A3, A4, A5, A6};
  //  unsigned char adcPosWide[6] = {A1, A2, A3, A4, A5, A6};
  //  unsigned char indexPosNarrow[6] = {1, 3, 5, 6, 8, 10};
  //  unsigned char indexPosWide[6] = {0, 2, 4, 7, 9, 11};

  //unsigned char xpos[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  //unsigned char adcPos[16] = {A0, A1, A2, A3, A4, A5, A6, A7, A7, A6, A5, A4, A3, A2, A1, A0};

  unsigned char xpos[14] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
  unsigned char ypos[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  unsigned char adcPosNarrow[8] = {0, 1, 2, 3, 4, 5, 6, 7};
  unsigned char adcPosWide[6] = {0, 1, 2, 5, 6, 7};
  unsigned char indexPosNarrow[8] = {1, 3, 5, 6, 7, 8, 10, 12};
  unsigned char indexPosWide[6] = {0, 2, 4, 9, 11, 13};

  unsigned char i;
  int adc, dataSensor = 0;

  setSensor(1, 0);    //narrow
  for (i = 0; i < 8; i++) {
    adc = analogRead(adcPosNarrow[i]);
    lcd.setCursor(xpos[indexPosNarrow[i]], ypos[indexPosNarrow[i]]);
    if (adc > ee.tresholdSensor[i]) {
      dataSensor += (0b10000000000000 >> indexPosNarrow[i]);
      lcd.write(255);
    }
    else lcd.print("_");
  }
  delayMicroseconds(1);
  setSensor(0, 1);  //wide
  for (i = 0; i < 6; i++) {
    adc = analogRead(adcPosWide[i]);
    lcd.setCursor(xpos[indexPosWide[i]], ypos[indexPosWide[i]]);
    if (adc > ee.tresholdSensor[i]) {
      dataSensor += (0b10000000000000 >> indexPosWide[i]);
      lcd.write(255);
    }
    else lcd.print("_");
  }
  delayMicroseconds(1);
  setSensor(0, 0);

  sensorValue = dataSensor;

  //white line
  sensorValue = (dataSensor & 0b11111111111111);
  sensorValue = 0b11111111111111 & sensorValue;
  sensorValue = 0b11111111111111 - sensorValue;
}

void scanSensor() {
  unsigned char i;
  int tick = 0, adc, lowLevel[16], highLevel[16];
  //unsigned char adcPosNarrow[6] = {A1, A2, A3, A4, A5, A6};
  //unsigned char adcPosWide[6] = {A1, A2, A3, A4, A5, A6};
  //unsigned char indexPosNarrow[6] = {1, 3, 5, 6, 8, 10};
  //unsigned char indexPosWide[6] = {0, 2, 4, 7, 9, 11};
  unsigned char adcPos[16] = {A0, A1, A2, A3, A4, A5, A6, A7, A7, A6, A5, A4, A3, A2, A1, A0};

  waitButton();
  for (i = 0; i < 16; i++) {
    lowLevel[i] = 1023;
    highLevel[i] = 0;
  }
  while (1) {
    setSensor(1, 0);
    for (i = 0; i < 8; i++) {
      adc = analogRead(adcPos[i]);
      if (adc > highLevel[i]) highLevel[i] = adc;
      if (adc < lowLevel[i]) lowLevel[i] = adc;
    }
    delay(1);
    setSensor(0, 1);
    for (i = 8; i < 16; i++) {
      adc = analogRead(adcPos[i]);
      if (adc > highLevel[i]) highLevel[i] = adc;
      if (adc < lowLevel[i]) lowLevel[i] = adc;
    }
    //delayMicroseconds(200);
    delay(1);
    setSensor(0, 0);
    lcd.setCursor(0, 0); lcd.print("Scanning");
    lcd.setCursor(0, 1); lcd.print("Done      Cancel");
    tick++;
    if (tick < 200) {
      lcd.setCursor(8, 0);
      lcd.print(".  ");
    }
    else if (tick > 400) {
      lcd.setCursor(8, 0);
      lcd.print("...");
    }
    else {
      lcd.setCursor(8, 0);
      lcd.print(".. ");
    }
    if (tick > 600) tick = 0;
    if (!digitalRead(buttonOk)) break;
    if (!digitalRead(buttonBack)) {
      waitButton();
      lcd.setCursor(0, 0);
      lcd.print("Canceled        ");
      delay(500);
      goto exitScanSensor;
    }
  }
  waitButton();
  lcd.setCursor(0, 0);
  lcd.print("Saving Data     ");
  delay(500);
  for (i = 0; i < 16; i++) {
    //ee.tresholdSensor[i] = highLevel[i] - lowLevel[i];
    //ee.tresholdSensor[i] = ee.tresholdSensor[i] * (100 - sensorSensitivity) / 100;
    //ee.tresholdSensor[i] = ee.tresholdSensor[i] + lowLevel[i];
    ee.tresholdSensor[i] = lowLevel[i] + ((highLevel[i] - lowLevel[i]) / 2);
  }
exitScanSensor:
  EEPROM.put(0, ee);
  lcd.clear();
}
