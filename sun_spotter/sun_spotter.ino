#include <ArduinoSTL.h>

#include "sun_spotter.hpp"

SunSpotter sunSpotter;

void setup() {
  // put your setup code here, to run once:
  printf("hello, world");
  sunSpotter.getSomething();
  sunSpotter.printVars();
}

void loop() {
  // put your main code here, to run repeatedly:
  EquitorialCoordinate ec;
  ec = sunSpotter.getEquitorialCoordinates();
  std::cout << "x:" << ec.x << " y:" << ec.y << " z:" << ec.z << std::endl;
}
