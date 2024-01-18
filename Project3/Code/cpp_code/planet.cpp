#include "system.hpp"
#include<iostream>

planet::planet(double init_x, double init_y, double init_z, double init_vx, double init_vy, double init_vz, double init_mass){
  mass = init_mass;
  position = vec3(init_x, init_y, init_z);
  velocity = vec3(init_vx, init_vy, init_vz);
}

void planet::resetForce(){
  force.zeros();
}

double planet::distance(planet otherPlanet){
  vec3 dx;
  dx = this->position - otherPlanet.position;
  return dx.length();
}


vec3 planet::GravitationalForce(planet otherPlanet, double beta){
  double G = 4*M_PI*M_PI;
  double r = this-> distance(otherPlanet);
  vec3 rel_pos = this-> position - otherPlanet.position;
    if (r != 0) return {-G*this->mass*otherPlanet.mass*rel_pos.normalized()/(pow(r, beta))}; //(r*r*r);

  else return vec3(0,0,0);
}

vec3 planet::Relativistic(planet otherPlanet) {
    double G = 4*M_PI*M_PI;
    double r = this -> distance(otherPlanet);
    double c = 63239.7263; // AU/yr
    vec3 rel_pos = this->position - otherPlanet.position;
    double r_squared = rel_pos.lengthSquared();
    vec3 vel = this -> velocity;
    vec3 l = rel_pos.cross(vel);
    double ll = l.lengthSquared();
    if (r != 0) return {(-G*this->mass*otherPlanet.mass*rel_pos.normalized()/r_squared)*(1+(3.0*ll)/(r_squared*c*c))};
    else return vec3(0,0,0);
}


vec3 planet::Acceleration(planet otherPlanet, double beta){
  double r = this-> distance(otherPlanet);
  if (r != 0) return this->GravitationalForce(otherPlanet, beta)/(this->mass);
  else return vec3(0,0,0);
}

double planet::PotentialEnergy(planet otherPlanet, double beta){
  double potEn;
  potEn = -this->GravitationalForce(otherPlanet, beta).length()*this->distance(otherPlanet);
  return potEn;
}

double planet::KineticEnergy(){
  double kinEn;
  kinEn = 0.5*this->mass*this->velocity.lengthSquared();
  return kinEn;
}

void planet::updatePosition(vec3 rhs){
  this->position += rhs;
}

void planet::updateVelocity(vec3 rhs){
  this->velocity += rhs;
}
