#include "system.hpp"
#include "solver.hpp"
#include<iostream>
#include<iomanip>
#include<time.h>
#include<chrono>

using namespace std;



int main(int argc, char* argv[]){


  int n; //Integration points
  double time; //Number of Years


  bool fixedPos;
  bool addCorrectionTerm;
  bool varyBeta;
  int whichProblem = atoi(argv[1]);


  cout << "How many years? "; cin >> time;
  cout << "How many iterations, n? "; cin >> n;


  solarsystem SolarSystem;
  solver mySolver;

  if (whichProblem == 1 || whichProblem == 2) {
    #include"InitialValues/twobodysystem.cpp"
    fixedPos = 1;
    if (whichProblem == 1) {
      mySolver.EulerCromer(SolarSystem, n, time, fixedPos);
    }
    mySolver.EulerForward(SolarSystem, n, time, fixedPos);
    mySolver.VelocityVerlet(SolarSystem, n, time, fixedPos, 2.0);
  }
  //Timing of Velocity Verlet
  else if (whichProblem == 3) {
    fixedPos = 1;
    #include"InitialValues/twobodysystem.cpp"
    auto start = chrono::high_resolution_clock::now();
    mySolver.VelocityVerlet(SolarSystem, n, time, fixedPos, 2.);
    auto finish = chrono::high_resolution_clock::now();
    cout << "\nCPU-timing for earth-sun using Velocity Verlet Method: "  << chrono::duration_cast<chrono::nanoseconds>(finish-start).count()/pow(10,9) << endl;
  }
  //Varying beta
  else if (whichProblem == 4) {
    fixedPos = 1;
    #include"InitialValues/twobodysystem.cpp"
    double beta;
    cout <<  "Value of beta [2,3]: "; cin >> beta;
    mySolver.VelocityVerlet(SolarSystem, n, time, fixedPos, beta);
  }
  //Earth with initial velocity 5 AU/yr
  else if (whichProblem == 5) {
    fixedPos = 1;
    double mass_sun = 1.988500*1E30;
    double mass_earth = 5.97219*1E24/mass_sun;
    planet sun(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    planet earth(1.0, 0.0, 0.0, 0.0, 5.0, 0.0, mass_earth);
    SolarSystem.add(&sun);
    SolarSystem.add(&earth);
    double beta;
    cout << "Value of beta [2,3]: "; cin >> beta;
    mySolver.VelocityVerlet(SolarSystem, n, time, fixedPos, beta);
  }
  //Escape velocity
  else if (whichProblem == 6) {
    fixedPos = 1;
    double initvelocity = 0;
    cout << "Initial velocity?: "; cin >> initvelocity;
    double mass_sun = 1.988500*1E30;
    double mass_earth = 5.97219*1E24/mass_sun;
    planet sun(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    planet earth(1.0, 0.0, 0.0, 0.0, initvelocity, 0.0, mass_earth);
    SolarSystem.add(&sun);
    SolarSystem.add(&earth);
    mySolver.VelocityVerlet(SolarSystem, n, time, fixedPos, 2.);
  }
  //Three body problem with sun fixed to center with co-planar inititial values
  else if (whichProblem == 7){
    fixedPos = 1;
    int changeMass = 1;
    cout << "Factor of Jupiter mass: "; cin >> changeMass;
    double mass_sun = 1.988500*1E30;
    double mass_earth = 5.97219*1E24/mass_sun;
    double mass_jupiter = changeMass*1.9*1E27/mass_sun;
    planet sun(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    planet earth(1.0, 0.0, 0.0, 0.0, 2*M_PI, 0.0, mass_earth);
    planet jupiter(5.20, 0.0 , 0.0, 0.0 , 2.72, 0.0, mass_jupiter);
    SolarSystem.add(&sun);
    SolarSystem.add(&earth);
    SolarSystem.add(&jupiter);
    mySolver.VelocityVerlet(SolarSystem, n, time, fixedPos, 2.0);
  }
  //Three body problem with the sun unfixed and with use of NASA-data
  else if (whichProblem == 8){
    #include"InitialValues/threebodysystem.cpp"
    fixedPos = false;
    mySolver.VelocityVerlet(SolarSystem, n, time, fixedPos, 2.0);
  }
  //Multi Body System
  else if (whichProblem == 9){
    #include"InitialValues/multibodysystem.cpp"
    fixedPos = false;
    mySolver.VelocityVerlet(SolarSystem, n, time, fixedPos, 2.0);
  }
  //Perihelion precession
  else if (whichProblem == 10){
    double mass_sun = 1.988500*1E30;
    double mass_mercury = 3.302*1E23/mass_sun;
    planet sun(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    planet mercury(0.3075,0.0,0.0,0.0,12.44,0.0,mass_mercury);
    SolarSystem.add(&sun);
    SolarSystem.add(&mercury);
    fixedPos = false;
    cout << "Add relativistic correction term? [0 or 1] : "; cin >> addCorrectionTerm;
    mySolver.VelocityVerletRel(SolarSystem, n, time, fixedPos, addCorrectionTerm);
  }

  return 0;
}
