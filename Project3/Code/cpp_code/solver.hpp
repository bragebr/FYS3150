#ifndef solver_HPP
#define solver_HPP

#include"system.hpp"
#include"vec3.h"


class solver{
public:
  friend class solarsystem;

  //initialize
  solver();

  void VelocityVerlet(solarsystem solarsystem, int n, double time, bool fixedPos, double beta);
  void VelocityVerletRel(solarsystem solarsystem, int n, double time, bool fixedPos, bool addCorretionTerm);
  void EulerForward(solarsystem solarsystem, int n, double time, bool fixedPos);
  void EulerCromer(solarsystem solarsystem, int n, double time, bool fixedPos);

  //TESTS
  double TEST_circular(planet *planet);
  bool TEST_kepler(double current, double last);
  //double TEST_AtPerihelion(planet *Mercury, planet otherPlanet);
};

#endif
