#include"solver.hpp"


double solver::TEST_circular(planet *planet){
  double rad = 1.0;
  double err = planet->position.length() - rad;
  return fabs(err);
}

bool solver::TEST_kepler(double current, double last) {
  double tolerance = 1e-10;
  if (fabs(current-last) > tolerance) { return 0; }
  else { return 1; }
}

/*
double solver::TEST_AtPerihelion(planet *Mercury, planet otherPlanet){
    double accepted_perihelion = 0.307499;
    double tol = 1E-1;
    double rel_distance = (Mercury->position - otherPlanet.position).length();
    
    if (fabs(rel_distance-accepted_perihelion) < tol) {return Mercury->position[1]/Mercury->position[0];}
    else {return 0;}
}
*/
