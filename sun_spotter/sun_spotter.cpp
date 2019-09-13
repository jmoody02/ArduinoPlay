#include <ArduinoSTL.h>
#include "sun_spotter.hpp"
#include <time.h>
#include <math.h>

SunSpotter::SunSpotter () {
    time_t now = time(0);
    std::cout << "The local date and time is: " << now << std::endl;
    double JDN = ( now / 86400.0 ) + 2440587.5;
    std::cout << "JDN: " << JDN << std::endl;

    n = JDN-2451545.0;
    L = 280.460+0.9856474*n;
    while (L > 360) {
        L = L - 360;
    }
    g = 357.528+0.9856003*n;
    while (g > 360) {
        g = g - 360;
    }
    lambda = L + 1.915 * sin(g) + 0.020 * sin(2*g);
    beta = 0;
    R = 1.00014 - (0.01671 * cos(g)) - (0.00014 * cos(2*g));
}

void SunSpotter::printVars() {
    std::cout << "n:" << n << std::endl;
    std::cout << "L:" << L << std::endl;
    std::cout << "g:" << g << std::endl;
    std::cout << "lambda:" << lambda << std::endl;
    std::cout << "beta:" << beta << std::endl;
    std::cout << "R:" << R << std::endl;
    return;
}

int SunSpotter::getSomething() {
    return 1;
}

EquitorialCoordinate SunSpotter::getEquitorialCoordinates() {
    EquitorialCoordinate returnCoordinate;
    returnCoordinate.x = 0;
    returnCoordinate.y = 0;
    returnCoordinate.z = 0;
    
    double epsilon = 23.439-0.0000004*n;
    
    returnCoordinate.x = R * cos(epsilon) * cos(lambda);
    returnCoordinate.y = R * cos(epsilon) * sin(lambda);
    returnCoordinate.z = R * sin(epsilon);
    
    return returnCoordinate;
}
