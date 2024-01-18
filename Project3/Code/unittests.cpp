#define CATCH_CONFIG_MAIN
#include "system.hpp"
#include "planets.hpp"


TEST_CASE("Does the solarsystem class constructor work properly?", "[solver]") {
  solarsystem solarsystem1;
  CHECK ( solarsystem1.totalPlanets == 0 );
  CHECK ( solarsystem1.totalMass == 0 );
}

TEST_CASE("Does the planet class contructor work properly?", "[planet]") {
  planet planet1(1,1,1,1,1,1,1);
  CHECK ( planet1.mass == 1);
  CHECK ( planet1.position[0] == 1);
  CHECK ( planet1.position[1] == 1);
  CHECK ( planet1.postiton[2] == 1);
  CHECK ( planet1.velocity[0] == 1);
  CHECK ( planet1.velocity[1] == 1);
  CHECK ( planet1.velocity[2] == 1);
}

TEST_CASE("Does the solarsystem::add() add planets correctly?", "[add]") {
  solarsystem solarsystem1;
  planet planet1(1,1,1,1,1,1,1);
  solarsystem1.add(planet1);
  CHECK ( solarsystem1.totalPlanets == 1);
  CHECK ( solarsystem1.totalMass == 1);
}
