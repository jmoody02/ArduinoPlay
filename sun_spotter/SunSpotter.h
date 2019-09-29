//
//  SunSpotter.h
//  ArduinoTest
//
//  Created by Jonathan Moody on 9/9/19.
//  Copyright © 2019 Jonathan Moody. All rights reserved.
//
#include <time.h>

#ifndef SunSpotter_h
#define SunSpotter_h

class SunSpotter {
private:
    double solar_azimuth_angle;
    double solar_adjusted_elevation_angle;
    int time_zone;
    double longitude;
    double latitude;
public:
    SunSpotter();
    void set_time_zone(int);
    void set_latitude(int);
    void set_longitude(int);
    void calculate(time_t);
    double getAltitude();
    double getAzimuth();
};

#endif /* SunSpotter_h */
