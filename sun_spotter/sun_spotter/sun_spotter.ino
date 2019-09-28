#include <SunSpotter.h>
#include <math.h>
#include <Servo.h>

SunSpotter sunSpotter;
Servo myservo2;
Servo myservo16;

void setup() {
  Serial.begin(115200);
  myservo2.attach(2);
  myservo16.attach(16);
  pinMode(0, OUTPUT);
  Serial.println("Setup Complete");
}

void loop() {
  time_t now = 1569093961-14400;
  time_t now_machine = time(0)-14400;
  Serial.println(asctime(localtime(&now)));
  Serial.println(asctime(localtime(&now_machine)));
  
  sunSpotter.calculate();
  double azimuth = round( sunSpotter.getAzimuth() );
  if (azimuth > 180) {
    azimuth = azimuth - 180;
  }
  Serial.println(azimuth);
  myservo16.write(azimuth);
  Serial.println(sunSpotter.getAltitude());
  double altitude = round( sunSpotter.getAltitude() );
  if (altitude > 180) {
    altitude = altitude - 180;
  }
  Serial.println(altitude);
  myservo2.write(altitude);
  for (int i=0; i<altitude; i++) {
    digitalWrite(0, HIGH);
    delay(200);
    digitalWrite(0, LOW);
    delay(200);
  }
  delay(2000);
}
