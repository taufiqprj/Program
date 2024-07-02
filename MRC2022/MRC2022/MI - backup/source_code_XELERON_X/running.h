void gripperAction(int mode) {
  setMotor(0, 0);
  lcd.clear();
  switch (mode) {
    case pick:
      lcd.setCursor(0, 0); lcd.print("Picking...");
      servoGrip.write(gripOn);
      delay(1000);
      servoLift.write(liftUp);
      delay(1000);
      gripperState = 1;
      break;
    case drop:
      lcd.setCursor(0, 0); lcd.print("Dropping..");
      servoLift.write(liftDown);
      delay(1000);
      servoGrip.write(gripOff);
      delay(1000);
      gripperState = 0;
      break;
  }
}

//void followLine(int modeFollow) {
void followLine() {
  switch (sensorValue) {
    case 0b100000000000 : error = -31;    break;
    case 0b110000000000 : error = -27;    break;
    case 0b010000000000 : error = -25;    break;
    case 0b011000000000 : error = -21;    break;
    case 0b001000000000 : error = -17;    break;
    case 0b001100000000 : error = -15;    break;
    case 0b000100000000 : error = -11;    break;
    //case 0b011011000000 : error=-7;     break;
    case 0b000110000000 : error = -7;     break;
    case 0b000010000000 : error = -5;     break;
    //case 0b001101100000 : error=-3;     break;
    case 0b000011000000 : error = -3;     break;
    //case 0b000110110000 : error=-1;     break;
    case 0b000001000000 : error = -1;     break;
    case 0b000001100000 : error = 0;      break;
    case 0b000000100000 : error = 1;      break;
    //case 0b000011011000 : error=1;      break;
    case 0b000000110000 : error = 3;      break;
    //case 0b000001101100 : error=3;      break;
    case 0b000000010000 : error = 5;      break;
    case 0b000000011000 : error = 7;      break;
    //case 0b000000110110 : error=7;      break;
    case 0b000000001000 : error = 11;     break;
    case 0b000000001100 : error = 15;     break;
    case 0b000000000100 : error = 17;     break;
    case 0b000000000110 : error = 21;     break;
    case 0b000000000010 : error = 25;     break;
    case 0b000000000011 : error = 27;     break;
    case 0b000000000001 : error = 31;     break;

    //case 0b111100000000 : error=-11;    break;
    //case 0b111110000000 : error=-5;     break;
    //case 0b111111000000 : error=-1;     break;
    //case 0b111111100000 : error=0;      break;
    //case 0b111111110000 : error=1;      break;
    //case 0b111111111000 : error=5;      break;
    //case 0b111111111100 : error=11;     break;

    //case 0b001111111111 : error=-11;    break;
    //case 0b000111111111 : error=-5;     break;
    //case 0b000011111111 : error=-1;     break;
    //case 0b000001111111 : error=0;      break;
    //case 0b000000111111 : error=1;      break;
    //case 0b000000011111 : error=5;      break;
    //case 0b000000001111 : error=11;     break;

    case 0b111000000000 : error = -25;    break;
    case 0b011100000000 : error = -17;    break;
    case 0b001110000000 : error = -11;    break;
    case 0b000111000000 : error = -5;     break;
    case 0b000011100000 : error = -1;     break;
    case 0b000001110000 : error = 1;      break;
    case 0b000000111000 : error = 5;      break;
    case 0b000000011100 : error = 11;     break;
    case 0b000000001110 : error = 17;     break;
    case 0b000000000111 : error = 25;     break;
  }
  /*
    sensorLeft = (sensorValue & 0b1111110000000000) >> 10;
    sensorRight = (sensorValue & 0b0000000000111111);
    if (modeFollow == followLeft) {
    switch (sensorLeft) {
      case 0b100000:  error = -20;  break;
      case 0b110000:  error = -13;  break;
      case 0b010000:  error = -7;   break;
      case 0b011000:  error = -3;   break;
      case 0b001000:  error = -1;   break;
      case 0b001100:  error = 0;    break;
      case 0b000100:  error = 1;    break;
      case 0b000110:  error = 3;    break;
      case 0b000010:  error = 7;    break;
      case 0b000011:  error = 13;   break;
      case 0b000001:  error = 20;   break;
      case 0b000000:  break;
    }
    }
    else if (modeFollow == antiLeft) {
    switch (sensorLeft) {
      case 0b000000:  error = -20;  break;
      case 0b100000:  error = -5;   break;
      case 0b110000:  error = 0;    break;
      case 0b010000:  error = 1;    break;
      case 0b011000:  error = 3;    break;
      case 0b001000:  error = 5;    break;
      case 0b001100:  error = 8;    break;
      case 0b000100:  error = 12;   break;
      case 0b000110:  error = 16;   break;
      case 0b000010:  error = 20;   break;
      case 0b000011:  error = 25;   break;
      case 0b000001:  error = 30;   break;
    }
    }
    else if (modeFollow == followRight) {
    switch (sensorRight) {
      case 0b100000:  error = -20;  break;
      case 0b110000:  error = -13;  break;
      case 0b010000:  error = -7;   break;
      case 0b011000:  error = -3;   break;
      case 0b001000:  error = -1;   break;
      case 0b001100:  error = 0;    break;
      case 0b000100:  error = 1;    break;
      case 0b000110:  error = 3;    break;
      case 0b000010:  error = 7;    break;
      case 0b000011:  error = 13;   break;
      case 0b000001:  error = 20;   break;
      case 0b000000:  break;
    }
    }
    else if (modeFollow == antiRight) {
    switch (sensorRight) {
      case 0b100000:  error = -30;  break;
      case 0b110000:  error = -25;  break;
      case 0b010000:  error = -20;  break;
      case 0b011000:  error = -16;  break;
      case 0b001000:  error = -12;  break;
      case 0b001100:  error = -8;   break;
      case 0b000100:  error = -5;   break;
      case 0b000110:  error = -3;   break;
      case 0b000010:  error = -1;   break;
      case 0b000011:  error = 0;    break;
      case 0b000001:  error = 5;    break;
      case 0b000000:  error = 20;   break;
    }
    }
    else if (modeFollow == antiLeftRight) {
    if (sensorLeft && !sensorRight) error = 20;
    else if (!sensorLeft && sensorRight) error = -20;
    else error = 0;
    }
  */

  rate = error - lastError;
  powerLeft = (int)((runningSpeed + (error * kp)) + (rate * kd));
  powerRight = (int)((runningSpeed + (-error * kp)) - (rate * kd));
  constrain(powerLeft, minSpeed, maxSpeed);
  constrain(powerRight, minSpeed, maxSpeed);
  setMotor(powerLeft, powerRight);
  lastError = error;
}

void turn(int motorLeft, int motorRight, int delayTurn) {
  if (delayTurn != 0) {
    digitalWrite(lcdBackLight, 1);
    if (motorLeft <= 0 || motorRight <= 0) {
      setMotor(-100, -100);
      delay(20);
    }
    setMotor(motorLeft, motorRight);
    delay(delayTurn);
  }
  digitalWrite(motorEnable, 1);
  delay(1);
  digitalWrite(motorEnable, 0);
}

/*void checkObs() {
  if (!digitalRead(obsPin) && gripperState == 0) {
    gripperAction(pick);
  }
  }*/

void checkObs() {
  if (!digitalRead(ext1Pin)) {
    setMotor(-runningSpeed, -runningSpeed);
    delay(100);
    setMotor(0, 0);
    delay(500);

    setMotor(120, -150);
    delay(290);
    setMotor(0, 0);
    delay(300);

    setMotor(80, 150);
    delay(1200);

    do {
      setMotor(80, 150);
      readSensor();
    }
    while (!(sensorValue & (0b10000000000000 >> 0b00000000000111)));

    setMotor(120, 0);
    delay(150);
  }
}

void run(int speedAwal, int modeSensor, int motorKiri, int motorKanan, int delayBelok, int speedTimer, int timer) {
  int tick = 0, tempTick = 0;
  runningSpeed = speedAwal;
  while (1) {
    readSensor();
    followLine();
    checkObs();
    switch (modeSensor) {
      case tanpaGaris:
        if (sensorValue == sensorTanpaGaris) {
          turn(motorKiri, motorKanan, delayBelok);
          goto exitRun;
        }
        break;
      case dimanapun:
        turn(motorKiri, motorKanan, delayBelok);
        goto exitRun;
        break;
      case fl:
        if (sensorValue & sensorTengah) {
          if (sensorValue & sensorKiri) {
            turn(motorKiri, motorKanan, delayBelok);
            goto exitRun;
          }
        }
        break;
      case fr:
        if (sensorValue & sensorTengah) {
          if (sensorValue & sensorKanan) {
            turn(motorKiri, motorKanan, delayBelok);
            goto exitRun;
          }
        }
        break;
      case lr:
      case rl:
        if (sensorValue & sensorKanan) {
          if (sensorValue & sensorKiri) {
            turn(motorKiri, motorKanan, delayBelok);
            goto exitRun;
          }
        }
        break;
      default:
        if (sensorValue & (0b10000000000000 >> (modeSensor - 1))) {
          turn(motorKiri, motorKanan, delayBelok);
          goto exitRun;
        }
        break;
    }
  }
exitRun:
  runningSpeed = 0;
  while (tempTick < 30) {
    readSensor();
    followLine();
    checkObs();
    tempTick++;
  }
  runningSpeed = speedTimer;
  while (tick < timer) {
    readSensor();
    followLine();
    checkObs();
    tick++;
  }
  digitalWrite(lcdBackLight, 0);
  digitalWrite(motorEnable, 1);
  delay(1);
  digitalWrite(motorEnable, 0);
}
