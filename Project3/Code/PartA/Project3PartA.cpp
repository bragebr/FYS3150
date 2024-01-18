// Solving the earth-sun system without classes for later reference
#include<iostream>
#include<armadillo>


//Include Mortens vector class?

/*
c++ -c -Wall Project3PartA.cpp
c++ -o Project3PartA.exe  Project3PartA.o
*/

using namespace std;
using namespace arma;
ofstream ofile;


void EulerForward(mat& Earth_pos, mat& Earth_vel, double& Earth_mass, double& Sun_mass, int n, double h, double G){
  double Forcex;
  double Forcey;
  for (int i = 0; i < n; i++){
    //Force
    Forcex = -G*Sun_mass*Earth_mass*Earth_pos(0,i)/(pow((Earth_pos(0,i)*Earth_pos(0,i) + Earth_pos(1,i)*Earth_pos(1,i)), 3/2));
    Forcey = -G*Sun_mass*Earth_mass*Earth_pos(1,i)/(pow((Earth_pos(0,i)*Earth_pos(0,i) + Earth_pos(1,i)*Earth_pos(1,i)), 3/2));

    //Velocity
    Earth_vel(0,i+1) = Earth_vel(0,i) + h*Forcex/Earth_mass;
    Earth_vel(1,i+1) = Earth_vel(1,i) + h*Forcey/Earth_mass;

    //Position
    Earth_pos(0,i+1) = Earth_pos(0,i) + h*Earth_vel(0,i);
    Earth_pos(1,i+1) = Earth_pos(1,i) + h*Earth_vel(1,i);
  }
}

void calcForce(double& Earth_pos_x, double& Earth_pos_y, double& F_x, double& F_y, double Earth_mass, double Sun_mass, double G){
  F_x = -G*Sun_mass*Earth_mass*Earth_pos_x/(pow((Earth_pos_x*Earth_pos_x + Earth_pos_y*Earth_pos_y), 3/2));
  F_y = -G*Sun_mass*Earth_mass*Earth_pos_y/(pow((Earth_pos_x*Earth_pos_x + Earth_pos_y*Earth_pos_y), 3/2));
}

void VelocityVerlet(mat& Earth_pos, mat& Earth_vel, double& Earth_mass, double& Sun_mass, int n, double h, double G){
  vec accel(2);
  vec accel_new(2);
  vec Earth_pos_cache(2);
  double F_x, F_y, F_new_x, F_new_y;
  F_x = F_y = F_new_x = F_new_y = 0.0;

  for (int i = 0; i < n; i++){
    calcForce(Earth_pos(0,i), Earth_pos(1,i), F_x, F_y, Earth_mass, Sun_mass, G);

    //Calc earth pos
    Earth_pos(0, i+1) = Earth_pos(0, i) + h*Earth_vel(0,i) + h*h/2*F_x/Earth_mass;
    Earth_pos(1, i+1) = Earth_pos(1, i) + h*Earth_vel(1,i) + h*h/2*F_y/Earth_mass;

    //calc new force
    calcForce(Earth_pos(0,i+1), Earth_pos(1,i+1), F_new_x, F_new_y, Earth_mass, Sun_mass, G);

    //Calc new earth vel
    Earth_vel(0, i+1) = Earth_vel(0, i) + h/2*(F_x/Earth_mass + F_new_x/Earth_mass);
    Earth_vel(1, i+1) = Earth_vel(1, i) + h/2*(F_y/Earth_mass + F_new_y/Earth_mass);
  }


}


int main(){
  int n = 100000;
  double tid = 100; //Years
  double G = 4*datum::pi*datum::pi;
  mat Earth_pos(2,n+1);
  mat Earth_vel(2,n+1);

  //Stepsize
  double h = tid/(n);

  double Earth_mass = 3e-6;
  double Sun_mass = 1.0;

  Earth_pos(0,0) = 1;
  Earth_pos(1,0) = 0;
  Earth_vel(0,0) = 0;
  Earth_vel(1,0) = 2*datum::pi;


  EulerForward(Earth_pos, Earth_vel, Earth_mass, Sun_mass, n, h, G);
  //VelocityVerlet(Earth_pos, Earth_vel, Earth_mass, Sun_mass, n, h, G);

  ofile.open("E_S_Sys.txt");
  ofile << "  x:     y:  " << endl;
  for (int i = 0; i < n; i++){
    ofile << setw(15) << setprecision(8) << Earth_pos(0,i);
    ofile << setw(15) << setprecision(8) << Earth_pos(1,i) << endl;
  }

  ofile.close();

  return 0;
}
