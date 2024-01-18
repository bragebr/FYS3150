#include "../vec3.h"
#include "../planet.hpp"
#include "../system.hpp"

double mass_sun = 1.988500*1E30;
double mass_earth = 5.97219*1E24/mass_sun;
double mass_jupiter = 1.89813*1E28/mass_sun;

double j = 365.25;

/*
SUN DATA
X =-6.129737383707927E-03 Y = 6.405371281081122E-03 Z = 8.959139263600595E-05
 VX=-7.260672606291386E-06 VY=-5.115343779622854E-06 VZ= 2.179205533471483E-07
*/

planet sun(-6.13*1E-3,6.41*1E-3, 8.96*1E-5, -7.26*1E-6*j, -5.12*1E-6*j, 2.18*1E-7*j, 1.0);

/*
EARTH DATA
X = 8.907825486734252E-01 Y = 4.396506241573193E-01 Z = 6.565015058670386E-05
VX=-7.776615948578309E-03 VY= 1.542644409377417E-02 VZ= 1.263167140692514E-07
*/
planet earth(8.91*1E-1, 4.40*1E-1, 6.57*1E-5, -7.78*1E-3*j, 1.54*1E-2*j, 1.26*1E-7*j, mass_earth);

/*
JUPITER DATA
X = 2.575956863567940E+00 Y =-4.416159673726113E+00 Z =-3.931176078837768E-02
 VX= 6.425396334484731E-03 VY= 4.160219877822326E-03 VZ=-1.609910003540274E-04
*/

planet jupiter(2.56, -4.42, -3.93*1E-2, 6.43*1E-3*j, 4.16*1E-3*j, -1.61*1E-4*j, mass_jupiter);


SolarSystem.add(&sun);
SolarSystem.add(&earth);
SolarSystem.add(&jupiter);
