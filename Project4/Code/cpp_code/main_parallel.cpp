#include"mpi.h"
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

// declarations
void Initialize(double &M, double &E, imat& lattice, int lattice_dim, double temperature);
void Metropolis(double &E, double &M, imat &ilattice, dvec w, int num);
int periodic_boundary_conditions(int x, int latticeDim, int add);
void WriteToFile(dvec average_total, int numCycles, int lattice_dim, double temperature, int run_cycles_total);

int main(int argc, char* argv[]){
  // menu

  int dim = 80;
  double temp_min = 2.0;
  double temp_max = 2.6;
  double temp_step = 0.005;
  int num_cycles = 10000000;

  dim = atoi(argv[1]);
  num_cycles = atoi(argv[2]);
  temp_min = atof(argv[3]);
  temp_max = atof(argv[4]);
  temp_step = atof(argv[5]);


  double E; double M;

  //MPI declarations
  int my_rank, numprocs;
  dvec average(5);
  dvec average_total(5);

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

  // Open file for storing expectation values
  if (my_rank == 0){
  myfile.open("Averages.txt");
  myfile << "Temperature, Emean, Cv, Mabsmean, X" << endl;
  cout << endl;
  }

  //Initialize "random" (=time) seed
  srand((unsigned)time(NULL));

  int no_intervalls = (double) (num_cycles/numprocs);
  int myloop_begins = my_rank*no_intervalls + 1;
  int myloop_end = (my_rank+1)*no_intervalls;
  if ( (my_rank == numprocs - 1) && (myloop_end < num_cycles)) myloop_end = num_cycles;

  MPI_Bcast(&dim, 1, MPI_INT, 0, MPI_COMM_WORLD);
  MPI_Bcast(&temp_min, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(&temp_max, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  MPI_Bcast(&temp_step, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  double rtime = MPI_Wtime();
  int run_cycles = 0;
  int run_cycles_total;

  //Monte-Carlo iterations

  for (double temperature = temp_min; temperature <= temp_max; temperature+=temp_step){
    E = M = 0;
    run_cycles = 0;
    run_cycles_total = 0;
    imat lattice(dim, dim); //Matrix with integers
    dvec w(17, fill::zeros);
    Initialize(M, E, lattice, dim, temperature);
    //Possible energy changes
    for (int dE = -8; dE <= 8; dE+=4) w(dE+8) = exp(-dE/(temperature));
    for (int i = 0; i < 5; i++){
      average(i) = 0.0;
      average_total(i) = 0.0;
    }

    for (int cycle = myloop_begins; cycle <= myloop_end; cycle++){
      Metropolis(E, M, lattice, w, dim);

      if (cycle > 10000){
      average(0) += E; average(1) += E*E;
      average(2) += M;
      average(3) += M*M;
      average(4) += fabs(M);
      run_cycles += 1;
      }
    }
    for (int i = 0; i < 5; i++){
      MPI_Reduce(&average(i), &average_total(i),
      1, MPI_DOUBLE , MPI_SUM, 0, MPI_COMM_WORLD);
    }
    MPI_Reduce(&run_cycles, &run_cycles_total,
      1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (my_rank == 0){
      if (temperature == temp_min){
        ofstream lonefile;
        lonefile.open("Lattice_Init.txt");
        for (int i = 0; i < dim; i++){
          for (int j = 0; j < dim; j++){
              lonefile << lattice(i,j) << ",";
          }
          lonefile << endl;
        }
        lonefile.close();
      }
      else if (temperature > temp_max-temp_step) {
        ofstream ltwofile;
        ltwofile.open("Lattice_Final.txt");
        for (int i = 0; i < dim; i++){
          for (int j = 0; j < dim; j++){
              ltwofile << lattice(i,j) << ",";
          }
          ltwofile << endl;
        }
        ltwofile.close();
      }
      else if (2.2-temp_step < temperature < 2.2+temp_step) {
        ofstream ltcfile;
        ltcfile.open("Lattice_Tc.txt");
        for (int i = 0; i < dim; i++){
          for (int j = 0; j < dim; j++){
              ltcfile << lattice(i,j) << ",";
          }
          ltcfile << endl;
        }
        ltcfile.close();
      }
      WriteToFile(average_total, num_cycles, dim, temperature, run_cycles_total);
      //Progress bar
      double myProgress = (temperature + temp_step - temp_min)/(temp_max-temp_min);
      if (myProgress < 1.0){
        int barWidth = 70;
        cout << "[";
        int pos = barWidth*myProgress;
        for (int i = 0; i < barWidth; i++){
          if (i < pos) cout << "=";
          else if (i==pos) cout << ">";
          else cout << " ";
        }
        cout << "]" << int(myProgress * 100.0) << " %\r";
        cout.flush();
      }
      else {
        int barWidth = 70;
        cout << "[";
        int pos = barWidth*myProgress;
        for (int i = 0; i < barWidth; i++){
          if (i < pos) cout << "=";
          else if (i==pos) cout << ">";
          else cout << " ";
        }
        cout << "] " << int(myProgress * 100.0) << "%\r";
        cout.flush();
        cout << endl;
      }

    }
  }
  rtime = MPI_Wtime() - rtime;
  if (my_rank == 0){
    cout << endl;
  cout << "Runtime: " << rtime << "s with " << numprocs << " cores"<< endl;
  myfile.close();
  cout << "\a" << endl;
  }
  MPI_Finalize();
  return 0;
}

void Initialize(double& M, double& E, imat& lattice, int lattice_dim,
  double temperature){
  //Initializing the lattice
  for (int i = 0; i < lattice_dim; i++){
    for (int j = 0; j < lattice_dim; j++){
      if (temperature < 1.5){
        lattice(i,j) = 1.0;
      }
      else{
        // Random number between 0 and 1; -1 if 0<x<0.5 , 1 if 0.5<x<1
        lattice(i,j) = int((double(rand())/(RAND_MAX)) > 0.5 ? 1: -1);
      }
    M += (double) lattice(i,j);
    }
  }

  for (int i = 0; i < lattice_dim; i++){
    for (int j = 0; j < lattice_dim; j++){
      E -= (double) lattice(i,j) *
      (lattice(periodic_boundary_conditions(i, lattice_dim, -1),j)
       + lattice(i,periodic_boundary_conditions(j, lattice_dim, -1)));
    }
  }
}

//One step in MC
void Metropolis(double &E, double &M, imat &ilattice, dvec w, int num){
  //Looping over spins (2 in our case)
  for (int i = 0; i < num; i++){
    for (int j = 0; j < num; j++){
      //Random values
      int rx = (int) (rand() % (num));
      int ry = (int) (rand() % (num));
      int deltaE = 2*ilattice(rx,ry)*
      (ilattice(rx,periodic_boundary_conditions(ry, num, -1)) +
       ilattice(periodic_boundary_conditions(rx, num, -1),ry) +
       ilattice(rx,periodic_boundary_conditions(ry, num, 1))  +
       ilattice(periodic_boundary_conditions(rx, num, 1),ry)  );

      //Metropolis test
      if ((double(rand())/RAND_MAX) <= w(deltaE+8)){
        ilattice(rx,ry) *= -1;
        E += (double) deltaE;
        M += (double) 2*ilattice(rx,ry);
      }
    }
  }
}

//From example code
int periodic_boundary_conditions(int x, int latticeDim, int add){
  return (int) (x+latticeDim+add) % (latticeDim);
}

void WriteToFile(dvec average_total, int numCycles, int lattice_dim,
  double temperature, int run_cycles_total){
  int num_spins = lattice_dim*lattice_dim;
  double norm = 1.0/((double) run_cycles_total);
  double Emean = average_total(0)*norm;
  double E2mean = average_total(1)*norm;
  double Mmean = average_total(2)*norm;
  double M2mean = average_total(3)*norm;
  double Mabsmean = average_total(4)*norm;

  double Evar = (E2mean - (Emean * Emean));
  double Mvar = (M2mean - (Mabsmean * Mabsmean));
  double CV = (1.0/(temperature*temperature))*Evar;
  double X = (1.0/(temperature))*Mvar;

  myfile << setprecision(8) << scientific << temperature << ",";
  myfile << setprecision(8) << scientific << Emean/num_spins << ",";
  myfile << setprecision(8) << scientific << CV/num_spins << ",";
  myfile << setprecision(8) << scientific << Mabsmean/num_spins  << ",";
  myfile << setprecision(8) << scientific << X/num_spins << endl;
}
