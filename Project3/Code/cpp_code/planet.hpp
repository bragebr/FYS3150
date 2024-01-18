#ifndef planet_HPP
#define planet_HPP

#include "vec3.h"
#include<cmath>

class planet{

public:
  vec3 position;
  vec3 velocity;
  vec3 force;
  double mass;
  double PotEn;

  planet(double init_x, double init_y, double init_z, double init_vx, double init_vy, double init_vz, double init_mass);
  planet(vec3 pos_init, vec3 vel_init, double mass_init);
  void resetForce();
  void updatePosition(vec3 rhs);
  void updateVelocity(vec3 rhs);
  double distance(planet otherPlanet);
  vec3 GravitationalForce(planet otherPlanet, double beta);
  vec3 Relativistic(planet otherPlanet);
  vec3 Acceleration(planet otherPlanet, double beta);
  double PotentialEnergy(planet otherPlanet, double beta);
  double KineticEnergy();

};


#endif
