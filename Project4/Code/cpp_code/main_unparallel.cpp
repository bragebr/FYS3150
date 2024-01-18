#include<stdlib.h> //rand
#include<cmath>
#include<random>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<iomanip>
#include<armadillo>

using namespace std;
using namespace arma;
ofstream myfile;

void Initialize(double &M, double &E, imat& lattice, int lattice_dim, double temperature);
void Metropolis(double &E, double &M, imat &ilattice, dvec w, int num, int &accepted_states);
int periodic_boundary_conditions(int x, int latticeDim, int add);
void WriteToFile(dvec average_total, int numCycles, int lattice_dim, double temperature, int accepted_states_total);
void UnitTests();

int main(int argc, char* argv[]){
  UnitTests();

  int dim = 20;
  double temperature = 2.4;
  int num_cycles = 1000000;
  int run_cycles = 0;
  double E = 0; double M = 0;
  int accepted_states = 0;
  int accepted_states_total = 0;

  dvec average(5);

  // Open file
  myfile.open("Averages24.dat");
  myfile << "Temperature, Emean, Cv, Mabsmean, X, No accepted states" << endl;

  srand((unsigned)time(NULL));

  imat lattice(dim, dim); //Matrix with integers
  dvec w(17, fill::zeros);
  Initialize(M, E, lattice, dim, temperature);
  //Possible energy changes
  for (int dE = -8; dE <= 8; dE+=4) w(dE+8) = exp(-dE/(temperature));


  for (int cycle = 1; cycle <= num_cycles; cycle++){
    accepted_states = 0;
    Metropolis(E, M, lattice, w, dim, accepted_states);
    if (cycle > num_cycles*0){
      average(0) += E;
      average(1) += E*E;
      average(2) += M;
      average(3) += M*M;
      average(4) += fabs(M);
      accepted_states_total += accepted_states;
      run_cycles += 1;
      WriteToFile(average, run_cycles, dim, cycle, accepted_states_total);
    }
  }

  cout << "Mcs: " << num_cycles << endl << "Accepted states: " << accepted_states_total << endl;


  //cout << endl;
  //cout << accepted_states << endl;
  //cout << "Runtime: " << rtime << "s with " << numprocs << " cores"<< endl;
  myfile.close();

  return 0;
}

void Initialize(double& M, double& E, imat& lattice, int lattice_dim, double temperature){
  //Initializing the lattice
  for (int i = 0; i < lattice_dim; i++){
    for (int j = 0; j < lattice_dim; j++){
      if (temperature < 0.5){
        lattice(i,j) = 1.0;
      }
      else{
        lattice(i,j) = int((double(rand())/(RAND_MAX)) > 0.5 ? 1: -1);  //Random number between 0 and 1; -1 if 0<x<0.5 , 1 if 0.5<x<1
      }
    M += (double) lattice(i,j);
    }
  }

  for (int i = 0; i < lattice_dim; i++){
    for (int j = 0; j < lattice_dim; j++){
      E -= (double) lattice(i,j) * (lattice(periodic_boundary_conditions(i, lattice_dim, -1),j) + lattice(i,periodic_boundary_conditions(j, lattice_dim, -1)));
    }
  }
}

//One step in MC
void Metropolis(double &E, double &M, imat &ilattice, dvec w, int num, int &accepted_states){
  //Looping over spins (2 in our case)
  for (int i = 0; i < num; i++){
    for (int j = 0; j < num; j++){
      //Random values
      int rx = (int) (rand() % (num));
      int ry = (int) (rand() % (num));
      int deltaE = 2*ilattice(rx,ry)*(ilattice(rx,periodic_boundary_conditions(ry, num, -1)) +
                                          ilattice(periodic_boundary_conditions(rx, num, -1),ry) +
                                          ilattice(rx,periodic_boundary_conditions(ry, num, 1))  +
                                          ilattice(periodic_boundary_conditions(rx, num, 1),ry)  );

      //Metropolis test
      if ((double(rand())/RAND_MAX) <= w(deltaE+8)){
        ilattice(rx,ry) *= -1;
        E += (double) deltaE;
        M += (double) 2*ilattice(rx,ry);
        accepted_states += 1;
      }
    }
  }
}

//From example code
int periodic_boundary_conditions(int x, int latticeDim, int add){
  return (int) (x+latticeDim+add) % (latticeDim);
}

void WriteToFile(dvec average_total, int numCycles, int lattice_dim, double temperature, int accepted_states_total){
  //cout << run_cycles_total << endl;
  int num_spins = lattice_dim*lattice_dim;
  double norm = 1.0 /((double) numCycles);
  double Emean = average_total(0)*norm;
  double E2mean = average_total(1)*norm;
  double Mmean = average_total(2)*norm;
  double M2mean = average_total(3)*norm;
  double Mabsmean = average_total(4)*norm;

  double Evar = (E2mean - Emean * Emean);
  double Mvar = (M2mean - Mabsmean * Mabsmean);
  double CV = (1.0/(temperature*temperature))*Evar;
  double X = (1.0/temperature)*Mvar;

  myfile << setprecision(8) << scientific << temperature << ",";
  myfile << setprecision(8) << scientific << Emean/num_spins << ",";
  myfile << setprecision(8) << scientific << CV/num_spins << ",";
  myfile << setprecision(8) << scientific << Mabsmean/num_spins  << ",";
  myfile << setprecision(8) << scientific << X/num_spins << ",";
  myfile << accepted_states_total << endl;
}

void UnitTests() {

  //Check function Initialize()
  double E_test = 0; double M_test = 0;
  int accepted_states = 0;
  arma::imat lattice_test(1,1);
  Initialize(M_test, E_test, lattice_test, 1, 1.);
  //Check if matrix is constructed properly
  if (lattice_test(0,0) != 1 && lattice_test(0,0) != -1) {
    cout << "Unit Test failed!\n Function \"Initialize()\" does not behave as expected\n";
  }
  //Check if magnetization is calculated correctly
  if (M_test != 1 && M_test != -1) {
    cout << "Unit Test failed!\n Function \"Initialize()\" does not behave as expected\n";
  }
  //Check if energy is calculated correctly. Should be -2 for either value in 1x1 matrix
  if (E_test != -2) {
    cout << "Unit Test failed!\n Function \"Initialize()\" does not behave as expected\n";
  }

  //Check function periodic_boundary_conditions()
  if (periodic_boundary_conditions(1,1,1) != 0 || periodic_boundary_conditions(2,2,1) != 1) {
    cout << "Unit Test failed!\n Function \"periodic_boundary_conditions()\" does not behave as expected\n";
  }

  //Check function Metropolis()
  E_test = 0; M_test = 0;
  arma::imat lattice_test2(2,2);
  Initialize(M_test, E_test, lattice_test2, 2, 1.);
  //lattice_test(0,0) = -1;
  dvec w_test(17, fill::zeros);
  for (int dE = -8; dE <= 8; dE+=4) w_test(dE+8) = exp(-dE/(1.));
  //Do 100 cycles
  for (int i = 0; i < 100; i++) {
      Metropolis(E_test, M_test, lattice_test2, w_test, 2, accepted_states);
  }
  //Check that Metropolis() never does anything other than flip spins
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      if (lattice_test2(i,j) != 1 && lattice_test2(i,j) != -1) {
        cout << "Unit Test failed!\n Function \"Metropolis()\" does not behave as expected\n";
      }
    }
  }
}
