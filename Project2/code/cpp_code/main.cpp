// Main program that runs all of the functions
#include "eigenvalueproblems.hpp"
#include<armadillo>
#include<time.h>

using namespace arma;
using namespace std;

int main(int argc, char* argv[]){
  int algorithm, n;
  cout << "Do you want to solve for Buckling Beam or Quantum Dots? [1 = Buckling Beam, 2 = Quantum Dots]: "; cin >> algorithm;

  if (algorithm == 1){
    //Asking for user input
    cout << "Enter n: "; cin >> n;
    BucklingBeamSolver my_solver;

    //Creating A
    my_solver.init(n);
    //Checking of the matrix from init is a toeplitz matrix:

    //Solving
    my_solver.solve();

    my_solver.write_to_file("BucklingBeam.dat");

  }

  if (algorithm == 2){
    double rho_upper;
    double rho_lower = 0.0;
    bool two_electrons;
    double frequency;

    // Asking for user input
    cout << "Enter n: "; cin >> n;
    cout << "Enter rho_upper: "; cin >> rho_upper;
    cout << "Is the problem for two electrons? [1 = yes, 0 = no]: "; cin >> two_electrons;
    cout << "Enter frequency: "; cin  >> setprecision(2) >> frequency;

    SLSolver my_solver;

    // Constructing matrix A for diagonalization
    my_solver.init(rho_lower,rho_upper,n,two_electrons,frequency);
    // Test to see if A is symmetric
    my_solver.solve();
    if (two_electrons == 0){
      my_solver.write_to_file("Schroedinger_one_electron.dat");
    } else {
        my_solver.write_to_file("Schroedinger_two_electrons_"+to_string(frequency) + ".dat");
    }

  }

}
