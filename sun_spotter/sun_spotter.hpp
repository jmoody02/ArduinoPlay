//
//  sun_spotter.hpp
//  ArduinoTest
//
//  Created by Jonathan Moody on 9/9/19.
//  Copyright © 2019 Jonathan Moody. All rights reserved.
//

#ifndef sun_spotter_hpp
#define sun_spotter_hpp

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
    void calculate();
    double getAltitude();
    double getAzimuth();
};

#endif /* sun_spotter_hpp */
