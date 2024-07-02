void setMotor(int speed1, int speed2, int speed3, int speed4) {
  if (speed1 < 0) {
    speed1 = 255 + speed1;
    digitalWrite(dir1Pin, 1);
  } 
  else digitalWrite(dir1Pin, 0);
  if (speed2 < 0) {
    speed2 = 255 + speed2;
    digitalWrite(dir2Pin, 1);
  } 
  else digitalWrite(dir2Pin, 0);
  if (speed3 < 0) {
    speed3 = 255 + speed3;
    digitalWrite(dir3Pin, 1);
  } 
  else digitalWrite(dir3Pin, 0);
  if (speed4 < 0) {
    speed4 = 255 + speed4;
    digitalWrite(dir4Pin, 1);
  } 
  else digitalWrite(dir4Pin, 0);
  if (speed1 > 255) speed1 = 255;
  if (speed2 > 255) speed2 = 255;
  if (speed3 > 255) speed3 = 255;
  if (speed4 > 255) speed4 = 255;
  analogWrite(pwm1Pin, speed1);
  analogWrite(pwm2Pin, speed2);
  analogWrite(pwm3Pin, speed3);
  analogWrite(pwm4Pin, speed4);
}

void omniDrive(int vx, int vy, int v_phi) {
  int m1 = vx + (-(vy)) + (-(v_phi * 0.8));
  int m2 = vx + vy + (-(v_phi * 0.8));
  int m3 = vx + (-(vy)) + (v_phi * 0.8);
  int m4 = vx + vy + (v_phi * 0.8);
  setMotor(m1, m2, m3, m4);
}
