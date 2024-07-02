#include <Wire.h>
#include <MechaQMC5883.h>

MechaQMC5883 qmc;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  qmc.init();
  //qmc.setMode(Mode_Continuous,ODR_200Hz,RNG_2G,OSR_256);
}

void loop() {
  int x, y, z;
  float azimuth;

  // qmc.read(&x, &y, &z);
  // azimuth = qmc.azimuth(&x,&z);
  // int x, y, z, a;
  qmc.read(&x, &y, &z);
  float angle = atan2(y, x);

  // Convert azimuth to heading
  float heading = angle;  // Ensure heading is within [0, 360] degrees

  azimuth = qmc.azimuth(&y, &x);
  Serial.print("Azimuth: ");
  Serial.print(azimuth);
  Serial.print(" degrees, Heading: ");
  Serial.print(heading);
  Serial.println(" degrees, Direction: ");
  // Serial.println(direction);

  delay(100);
}
