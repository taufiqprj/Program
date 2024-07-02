void setMotor(int speedLeft, int speedRight) {
  constrain(speedLeft, -255, 255);
  constrain(speedRight, -255, 255);
  if (speedLeft < 0) {
    analogWrite(motorPWMLeft, -speedLeft);
    digitalWrite(motorDirLeft, 0);
  }
  else {
    analogWrite(motorPWMLeft, 255 - speedLeft);
    digitalWrite(motorDirLeft, 1);
  }
  if (speedRight < 0) {
    analogWrite(motorPWMRight, -speedRight);
    digitalWrite(motorDirRight, 0);
  }
  else {
    analogWrite(motorPWMRight, 255 - speedRight);
    digitalWrite(motorDirRight, 1);
  }
}

void stopMotor() {
  analogWrite(motorPWMRight, 0);
  analogWrite(motorPWMLeft, 0);
  digitalWrite(motorDirLeft, 0);
  digitalWrite(motorDirRight, 0);
  delay(5);
  digitalWrite(motorEnable, 1);
}
