#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../cpp_code/system.hpp"
#include "../cpp_code/planet.hpp"
#include "../cpp_code/solver.hpp"
#include "../cpp_code/vec3.h"



TEST_CASE("Does the solarsystem class constructor work properly?", "[solver]") {
  solarsystem solarsystem1;
  REQUIRE ( solarsystem1.totalPlanets == 0 );
  REQUIRE ( solarsystem1.totalMass == 0 );
}


TEST_CASE("Does the planet class contructor work properly?", "[planet]") {
  planet planet1(1,1,1,1,1,1,1);
  CHECK ( planet1.mass == 1);
  CHECK ( planet1.position[0] == 1);
  CHECK ( planet1.position[1] == 1);
  CHECK ( planet1.position[2] == 1);
  CHECK ( planet1.velocity[0] == 1);
  CHECK ( planet1.velocity[1] == 1);
  CHECK ( planet1.velocity[2] == 1);
}

TEST_CASE("Does the solarsystem::add() add planets correctly?", "[add]") {
  solarsystem solarsystem1;
  planet planet1(1,1,1,1,1,1,1);
  solarsystem1.add(&planet1);
  CHECK ( solarsystem1.totalPlanets == 1);
  CHECK ( solarsystem1.totalMass == 1);
}

TEST_CASE("Does resetForce() work properly?", "[resetForce]") {
  planet planet1(1,1,1,1,1,1,1);
  planet1.force[0] = 1;
  CHECK ( planet1.force[0] == 1);
  planet1.resetForce();
  CHECK ( planet1.force[0] == 0);
}

TEST_CASE("Does distance compute distances between planets correctly?", "[distance]") {
  planet planet1(0.5,0.5,0.5,1,1,1,1);
  planet planet2(0.,0.,0.,1,1,1,1);
  double computed = planet1.distance(planet2);
  double distance = 0.866025;
  CHECK ( fabs(computed - distance) < 1e-5);
}

TEST_CASE("Does GravitationalForce(planet otherPlanet) compute force correctly?", "[GravitationalForce]") {
  planet planet1(0.5,0.5,0.5,1,1,1,1);
  planet planet2(0.,0.,0.,1,1,1,1);
  vec3 force_computed = planet1.GravitationalForce(planet2);
  double forcex = -30.3905; double forcey = -30.3905; double forcez = -30.3905;
  double tolerance = 1e-5;
  CHECK ( fabs(force_computed[0] - forcex) < tolerance);
  CHECK ( fabs(force_computed[1] - forcey) < tolerance);
  CHECK ( fabs(force_computed[2] - forcez) < tolerance);
}

TEST_CASE("Does solver::VelocityVerlet calculate motion correclty?", "[VelocityVerlet]") {
  planet planet1(0.,0.,0.,0.,0.,0.,1);
  planet planet2(1.,0.,0.,0.,1.,0.,10);
  solarsystem system1;
  system1.add(&planet1);
  system1.add(&planet2);
  solver solver1;
  solver1.VelocityVerlet(system1, 100, 1, false);
  cout << planet1.position << endl << planet1.velocity <<  endl;
}
