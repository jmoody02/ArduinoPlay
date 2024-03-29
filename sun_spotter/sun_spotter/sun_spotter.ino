#include <SunSpotter.h>
#include <math.h>
#include <Servo.h>
#include <RTClib.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>

SunSpotter sunSpotter;
Servo myservo2;
Servo myservo16;
RTC_PCF8523 rtc;
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);
bool generally_north;
int i;
float heading;

void setup() {
  generally_north = false;
  i = 0;
  heading = 0;
  /*Serial.begin(115200);*/
  myservo2.attach(2);
  myservo16.attach(16);
  pinMode(0, OUTPUT);
  if (! rtc.begin()) {
    /*Serial.println("Couldn't find RTC");*/
    while (1);
  }
  /*rtc.adjust(DateTime(2019, 10, 14, 11, 43, 0));*/
  /*Serial.println("Setup Complete");*/

  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    /*Serial.println("Ooops, no LSM303 detected ... Check your wiring!");*/
    while(1);
  }
  digitalWrite(0, HIGH);
}

void loop() {
  i = i + 1;
  
  
  /* Get a new sensor event 
     Identify compass heading  - check every loop until find generally north, then every 10 loops */ 
  if (!generally_north || (i % 10 == 0)) {   
    sensors_event_t event; 
    mag.getEvent(&event);
    
    float Pi = 3.14159;
    
    // Calculate the angle of the vector y,x
    heading = (atan2(event.magnetic.y,event.magnetic.x) * 180) / Pi;
    /*-8 for magnetic declination*/
    heading = heading -8;
    
    // Normalize to 0-360
    if (heading < 0)
    {
      heading = 360 + heading;
    }
    if (heading > 5 && heading < 355) {
        digitalWrite(0, LOW);
        generally_north = false;
      }
      else {
        digitalWrite(0, HIGH);
        generally_north = true;
      }
    /*Serial.print("Compass Heading: ");
    Serial.println(heading);*/
  }

  if (i % 100 == 0) {
    DateTime nowobj = rtc.now();
    time_t now = nowobj.unixtime()-14400;
    /*Serial.println(asctime(localtime(&now)));*/
    
    sunSpotter.calculate(now);
    double azimuth = round( sunSpotter.getAzimuth() );
    /*Serial.print("Initial Azimuth: ");
    Serial.println(azimuth);*/
    //adjust to my servo, which is 0 degrees for west, 180 is east
    azimuth = azimuth * -1;
    //west is coming in as -90, east as 90 now
    azimuth = azimuth - 90;
    if (azimuth > 180) {
      azimuth = azimuth - 180;
    }
    if (heading < 5) {
      azimuth = azimuth - round(heading);
    }
    if (heading > 355) { 
      azimuth = azimuth + round (360 - heading);
    }
    /*Serial.print("Azimuth: ");
    Serial.println(azimuth);*/
    myservo16.write(azimuth);
    double altitude = round( sunSpotter.getAltitude() );
    if (altitude > 180) {
      altitude = altitude - 180;
    }
    /*Serial.print("Altitude: ");
    Serial.println(altitude);*/
    myservo2.write(altitude);
    nowobj = NULL;
  }
  delay(100);
}
