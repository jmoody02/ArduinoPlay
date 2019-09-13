//
//  sun_spotter.hpp
//  ArduinoTest
//
//  Created by Jonathan Moody on 9/9/19.
//  Copyright © 2019 Jonathan Moody. All rights reserved.
//

#ifndef sun_spotter_hpp
#define sun_spotter_hpp

#include <stdio.h>

struct EquitorialCoordinate {
    double x;
    double y;
    double z;
};

class SunSpotter {
private:
    int n;
    double L;
    double g;
    double lambda;
    int beta = 0;
    double R;
public:
    SunSpotter();
    int getSomething();
    EquitorialCoordinate getEquitorialCoordinates();
    void printVars();
};


#endif /* sun_spotter_hpp */
