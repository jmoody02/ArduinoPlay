
#include "sun_spotter.hpp"
#include <iostream>
#include <math.h>
#include <Servo.h>

SunSpotter sunSpotter;
Servo myservo2;
Servo myservo6;

void setup() {
  myservo2.attach(2);
  myservo6.attach(6);
}

void loop() {
  sunSpotter.calculate();
  myservo2.write(round( sunSpotter.getAzimuth() ));
  myservo6.write(round( sunSpotter.getAltitude() ));
  delay(1000);
}
