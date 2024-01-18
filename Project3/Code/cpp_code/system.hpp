#ifndef system_HPP
#define system_HPP

#include "vec3.h"
#include"planet.hpp"
#include<cmath>
#include<vector>

using namespace std;

class solarsystem{
private:

public:
  friend class planet;
  double totalMass;
  int totalPlanets;
  vector<planet> allPlanets;

  solarsystem();
  void add(planet* newplanet);


};



#endif
