#include"system.hpp"
#include<iostream>

solarsystem::solarsystem(){
  totalPlanets = 0;
  totalMass = 0.0;
}

void solarsystem::add(planet* newplanet){
  totalPlanets += 1;
  totalMass += newplanet->mass;
  allPlanets.push_back(*newplanet);
}
