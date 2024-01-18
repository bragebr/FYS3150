#include "../vec3.h"
#include "../planet.hpp"
#include "../system.hpp"


double j = 365.25;
double mass_sun = 1.988500*1E30;
double mass_earth = 5.97219*1E24/mass_sun; // giving all masses in solar masses
//double mass_mercury = 3.302*1E23/mass_sun;


//planet earth(8.91*1E-1, 4.40*1E-1, 6.57*1E-5, -7.78*1E-3*j, 1.54*1E-2*j, 1.26*1E-7*j, mass_earth);
planet sun(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
planet earth(1.0, 0.0, 0.0, 0.0, 2*M_PI, 0.0, mass_earth);

//planet mercury(0.3075,0.0,0.0,0.0,12.44,0.0,mass_mercury);

SolarSystem.add(&sun);
SolarSystem.add(&earth);
//SolarSystem.add(&mercury);
