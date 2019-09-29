#include <SunSpotter.h>
#include <math.h>
#include <Servo.h>
#include <RTClib.h>

SunSpotter sunSpotter;
Servo myservo2;
Servo myservo16;
RTC_PCF8523 rtc;

void setup() {
  Serial.begin(115200);
  myservo2.attach(2);
  myservo16.attach(16);
  pinMode(0, OUTPUT);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  Serial.println("Setup Complete");
}

void loop() {

  DateTime nowobj = rtc.now();
  time_t now = nowobj.unixtime()-14400;
  Serial.println(asctime(localtime(&now)));
  
  sunSpotter.calculate(now);
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
