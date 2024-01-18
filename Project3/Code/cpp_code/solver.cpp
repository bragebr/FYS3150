#include"solver.hpp"
#include<vector>
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cmath>


using namespace std;

solver::solver(){

}


void solver::VelocityVerlet(solarsystem solarsystem, int n, double time, bool fixedPos, double beta){
  double h = time/n;
  double hh = h*h;
  ofstream ofile;
  ofstream efile;
  vector<double> distances;

  double err_max = 0;
  ofile.open("positionVerlet.csv");
  efile.open("energyVerlet.csv");
  efile << h << "\n";

  double currentarea = 0;
  double r1 = 0; double r2 = 0; double r3 = 0;
  double lastarea = 0;
  bool angularconservation = true;


    for (int i = 0; i < n; i++){
      lastarea = currentarea;
      for (int planet_index = 0; planet_index < solarsystem.totalPlanets; planet_index++){
        planet* planet = &solarsystem.allPlanets[planet_index];
        vec3 Force(0,0,0);
        vec3 Force2(0,0,0);
        double PotEn = 0.0;

        if (solarsystem.totalPlanets == 2 && planet_index == 1) {
           r1 = planet->distance(solarsystem.allPlanets[0]);
        }
        for (int otherPlanet_index = 0; otherPlanet_index <= solarsystem.totalPlanets-1; otherPlanet_index++){

          Force += planet->GravitationalForce(solarsystem.allPlanets[otherPlanet_index], beta);
          PotEn += planet->PotentialEnergy(solarsystem.allPlanets[otherPlanet_index], beta);

          if (planet_index == 1 && otherPlanet_index == 0) {
            distances.push_back(planet->distance(solarsystem.allPlanets[otherPlanet_index]));
          }



        }
        if (fixedPos && planet_index == 0){
          planet->position = planet->position;
        }
        else{
          planet->position += h*planet->velocity + hh/2*Force/planet->mass;
          if (planet_index == 1) {
            vec3 dist = h*planet->velocity + hh/2*Force/planet->mass;
            r3 = dist.length();
            r2 = planet->distance(solarsystem.allPlanets[0]);
          }
        }
        currentarea = (r1*r2*r3)/2;
        if (i != 0 && solarsystem.totalPlanets == 2 && planet_index == 1) { angularconservation = TEST_kepler(currentarea, lastarea); }

        //Calc new force
        for (int otherPlanet2_index = 0; otherPlanet2_index <= solarsystem.totalPlanets-1; otherPlanet2_index++){
          Force2 += planet->GravitationalForce(solarsystem.allPlanets[otherPlanet2_index], beta);
        }

        planet->velocity += h/2*(Force/planet->mass + Force2/planet->mass);
        ofile << planet->position[0]  << "," << planet->position[1] << "," << planet->position[2] << ",";
        efile << PotEn << "," << planet->KineticEnergy() << ",";
          //Testing if earths orbit is circular
          if (planet_index == 1 && err_max <= TEST_circular(planet)){
            err_max = TEST_circular(planet);
          }
        }
        ofile << endl;
        efile << endl;
    }
    cout << "Maximum error for given N Verlet:"<< scientific << setprecision(5) << err_max << endl;
    ofile.close();
    efile.close();
    if (solarsystem.totalPlanets == 2) { cout << "Is angular momentum conserved? " << angularconservation << endl; }

double largest = 0; double lowest = 10;
for (int i = 0; i < n; i++) {
  if (distances[i] > largest) { largest = distances[i]; }
  if (distances[i] < lowest) { lowest = distances[i]; }
}
cout << "Største avstand: " << largest << endl << "Minste avstand: " << lowest << endl;

}


void solver::VelocityVerletRel(solarsystem solarsystem, int n, double time, bool fixedPos, bool addCorrectionTerm){

  double h = time/n;
  double hh = h*h;
  ofstream perihelionfile;
  perihelionfile.open("perihelionMercury.csv");
  ofstream ofile;

  ofile.open("positionVerlet.csv");

  double XM,YM = 0;
  double r = 0;
  vector<double> distances;
  double orbit_counter = 1;
  double tol = 1E-12;


    for (int i = 0; i < n; i++){
      for (int planet_index = 0; planet_index < solarsystem.totalPlanets; planet_index++){
        planet* planet = &solarsystem.allPlanets[planet_index];
        vec3 Force(0,0,0);
        vec3 Force2(0,0,0);


        for (int otherPlanet_index = 0; otherPlanet_index <= solarsystem.totalPlanets-1; otherPlanet_index++){

            if (addCorrectionTerm){
                Force+= planet->Relativistic(solarsystem.allPlanets[otherPlanet_index]);
            }
            else {

                Force += planet->GravitationalForce(solarsystem.allPlanets[otherPlanet_index],2.0);
            }
            if (planet_index == 1 && otherPlanet_index == 0) {
              distances.push_back(planet->distance(solarsystem.allPlanets[otherPlanet_index]));
            }


        }
        if (fixedPos && planet_index == 0){
          planet->position = planet->position;
        }
        else{
          planet->position += h*planet->velocity + hh/2*Force/planet->mass;

        }


        //Calc new force
        for (int otherPlanet2_index = 0; otherPlanet2_index <= solarsystem.totalPlanets-1; otherPlanet2_index++){
            if (addCorrectionTerm) {
                Force2 += planet->Relativistic(solarsystem.allPlanets[otherPlanet2_index]);
            }
            else {
                Force2 += planet->GravitationalForce(solarsystem.allPlanets[otherPlanet2_index], 2.0);
            }

        }

        planet->velocity += h/2*(Force/planet->mass + Force2/planet->mass);
        if (i == 9990363) {
          cout << "x: " << planet->position[0] << endl << "y: " << planet->position[1] << endl;
        }
        ofile << planet->position[0]  << "," << planet->position[1] << "," << planet->position[2] << "," << endl;

        /*
         jeg tror vi skal legge til addCorrectionTerm som bool, og så kunne regne på presseseringen ved klassisk og relativistisk kraft
         Det skal være sånn at forskjellen mellom den klassiske verdien for pressesjonen og den relativistiske skal være 43" / 100 year, ikke at
         det er den observerte verdien

         Håkon - når du er ferdig med funksjonen som finner peri- og aphelion, så legger du den til under slik at vi kan skrive ut x - og y - posisjonen
         til Merkur til fil. Helst sånn det står nå, at vi skriver arctan(y/x) til fil - da er det lett å plotte det.
         */


      }

    }

    double mercury_years = time/0.24;
    int timesteps = n/mercury_years;
    int index_lowest = 0;

    double largest = 0; double lowest = 10;
    for (int i = (n-timesteps); i < n; i++) {
      if (distances[i] > largest) { largest = distances[i]; }
      if (distances[i] < lowest) { lowest = distances[i]; index_lowest = i; }
    }
    cout << "Største avstand: " << largest << endl << "Minste avstand: " << lowest << endl << "Index for perihelion: " << index_lowest << endl;
    perihelionfile.close();
    ofile.close();
}


void solver::EulerForward(solarsystem solarsystem, int n, double time, bool fixedPos) {

      double h = time/n;
      double hh = h*h;
      double err_max = 0;
      ofstream ofile;
      ofstream efile;
      efile.open("energyEuler-Forward.csv");
      efile << h << "\n";
      ofile.open("positionEuler.csv");

      for (int i = 0; i < n; i++){
        for (int planet_index = 0; planet_index < solarsystem.totalPlanets; planet_index++){
          planet* planet = &solarsystem.allPlanets[planet_index];
          vec3 Force(0,0,0);
          double PotEn = 0.0;

          for (int otherPlanet_index = 0; otherPlanet_index <= solarsystem.totalPlanets-1; otherPlanet_index++){
            Force += planet->GravitationalForce(solarsystem.allPlanets[otherPlanet_index], 2.);
            PotEn += planet->PotentialEnergy(solarsystem.allPlanets[otherPlanet_index], 2.);
          }
            planet->position += h*planet->velocity;
            planet->velocity += h*Force/planet->mass;

            ofile << planet->position[0] << "," << planet->position[1] << "," << planet->position[2] << ",";
            efile << PotEn << "," << planet->KineticEnergy() << ",";

            //Testing if earths orbit is circular
            if (planet_index == 1 && err_max <= TEST_circular(planet)){
              err_max = TEST_circular(planet);
            }
        }
        ofile << endl;
        efile << endl;
      }
      cout << "Maximum error for given N Euler-Forward:"<< scientific << setprecision(5) <<  err_max << endl;
      ofile.close();
      efile.close();
}
void solver::EulerCromer(solarsystem solarsystem, int n, double time, bool fixedPos){
  double h = time/n;
  double hh = h*h;
  double err_max = 0;
  ofstream ofile;
  ofile.open("positionEulerCromer.csv");

  for (int i = 0; i < n; i++){
    for (int planet_index = 0; planet_index < solarsystem.totalPlanets; planet_index++){
      planet* planet = &solarsystem.allPlanets[planet_index];
      vec3 Force(0,0,0);

      for (int otherPlanet_index = 0; otherPlanet_index <= solarsystem.totalPlanets-1; otherPlanet_index++){
        Force += planet->GravitationalForce(solarsystem.allPlanets[otherPlanet_index], 2.);
      }
        planet->velocity += h*Force/planet->mass;
        planet->position += h*planet->velocity;

        ofile << planet->position[0] << "," << planet->position[1] << "," << planet->position[2] << ",";

        //Testing if earths orbit is circular
        if (planet_index == 1 && err_max <= TEST_circular(planet)){
          err_max = TEST_circular(planet);
        }
    }
    ofile << endl;
  }
  cout << "Maximum error for given N Euler-Cromer:" << scientific << setprecision(5) << err_max << endl;
  ofile.close();
}
