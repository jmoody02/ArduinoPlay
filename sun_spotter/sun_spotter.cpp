#include "sun_spotter.hpp"
#include <time.h>
#include <math.h>
//#include <iostream>
#include <iomanip>

SunSpotter::SunSpotter () {
    time_zone = -4;
    longitude = -81.4412;
    latitude = 41.3898;
}

void SunSpotter::set_time_zone(int time_zone_param){
    time_zone = time_zone_param;
}
void SunSpotter::set_latitude(int latitude_param){
    latitude = latitude_param;
}
void SunSpotter::set_longitude(int longitude_param){
    longitude = longitude_param;
}
void SunSpotter::calculate(){
    time_t now = time(0);
    int time_zone = -4;
    double longitude = -81.4412;
    double latitude = 41.3898;
    
    double julian_day = ( now / 86400.0 ) + 2440587.5;
    double julian_century = (julian_day-2451545)/36525;
    double mean_obliq_ecliptic = 23+(26+((21.448-julian_century*(46.815+julian_century*(0.00059-julian_century*0.001813))))/60)/60;
    double obliq_corr_deg = mean_obliq_ecliptic+0.00256*cos((125.04-1934.136*julian_century)*M_PI/180);
    double y = tan((obliq_corr_deg/2)*M_PI/180)*tan((obliq_corr_deg/2)*M_PI/180);
    double geom_mean_long_sun = fmod((280.46646+julian_century*(36000.76983+julian_century*0.0003032)), 180);
    double geom_mean_anom_sun =357.52911+julian_century*(35999.05029-0.0001537*julian_century);
    double eccent_earth_orbit =0.016708634-julian_century*(0.000042037+0.0000001267*julian_century);
    double eq_of_time = 4*(y*sin(2*(geom_mean_long_sun*M_PI/180))-2*eccent_earth_orbit*sin((geom_mean_anom_sun*M_PI/180))+4*eccent_earth_orbit*y*sin((geom_mean_anom_sun*M_PI/180))*cos(2*(geom_mean_long_sun*M_PI/180))-0.5*y*y*sin(4*(geom_mean_long_sun*M_PI/180))-1.25*eccent_earth_orbit*eccent_earth_orbit*sin(2*(geom_mean_anom_sun*M_PI/180)))*180/M_PI;
    int minutes_of_day = (localtime(&now)->tm_hour*60) + std::localtime(&now)->tm_min;
    double true_solar_time = fmod(minutes_of_day+eq_of_time+4*longitude-60*time_zone,1440);
    double hour_angle;
    if (true_solar_time / 4 < 0) {
        hour_angle = true_solar_time/4+180;
    } else {
        hour_angle = true_solar_time/4-180;
    }
    double sun_eq_of_center = sin((geom_mean_anom_sun*M_PI/180))*(1.914602-julian_century*(0.004817+0.000014*julian_century))+sin((2*geom_mean_anom_sun*M_PI/180))*(0.019993-0.000101*julian_century)+sin((3*geom_mean_anom_sun*M_PI/180))*0.000289;
    double sun_true_long = geom_mean_long_sun+sun_eq_of_center;
    double sun_app_long = sun_true_long-0.00569-0.00478*sin(125.04-1934.136*julian_century*M_PI/180);
    double sun_declin = (asin(sin((obliq_corr_deg*M_PI/180))*sin((sun_app_long*M_PI/180))))*180/M_PI;
    double solar_zenith_angle = (acos(sin((latitude*M_PI/180))*sin((sun_declin*M_PI/180))+cos((latitude*M_PI/180))*cos((sun_declin *M_PI/180))*cos((hour_angle *M_PI/180)))) * 180/M_PI;
    //double solar_azimuth_angle;
    if (hour_angle>0) {
        solar_azimuth_angle = fmod((acos(((sin((latitude*M_PI/180))*cos((solar_zenith_angle*M_PI/180)))-sin((sun_declin*M_PI/180)))/(cos((latitude*M_PI/180))*sin((solar_zenith_angle*M_PI/180)))))+180*180/M_PI,360);
    } else {
        solar_azimuth_angle = fmod(540-(acos(((sin((latitude*M_PI/180))*cos((solar_zenith_angle*M_PI/180)))-sin((sun_declin*M_PI/180)))/(cos((latitude*M_PI/180))*sin(solar_zenith_angle*M_PI/180))))*180/M_PI,360);
    }
    double solar_elevation_angle = 90-solar_zenith_angle;
    double atmospheric_refraction;
    if (solar_elevation_angle>85) {
        atmospheric_refraction = 0.00;
    } else if(solar_elevation_angle > 5) {
        atmospheric_refraction = 58.1/tan(solar_elevation_angle*M_PI/180)-0.07/pow(tan(solar_elevation_angle*M_PI/180),3)+0.000086/pow(tan(solar_elevation_angle*M_PI/180),5);
    } else if (solar_elevation_angle > -0.575){
        atmospheric_refraction = 1735+solar_elevation_angle*(-518.2+solar_elevation_angle*(103.4+solar_elevation_angle*(-12.79+solar_elevation_angle*0.711)));
    } else {
        atmospheric_refraction = -20.772/tan(solar_elevation_angle*M_PI/180)/3600;
    }
    atmospheric_refraction = atmospheric_refraction /3600;
    solar_adjusted_elevation_angle = solar_elevation_angle+atmospheric_refraction;
}

double SunSpotter::getAltitude() {
    return solar_adjusted_elevation_angle;
}

double SunSpotter::getAzimuth() {
    return solar_azimuth_angle;
}
