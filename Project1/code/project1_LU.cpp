#include<iostream>
#include<armadillo>
#include<cmath>
#include<iomanip>
#include "time.h"

using namespace std;
ofstream ofile;

int main(int argc, char* argv[]){
  int n = atoi(argv[1]);
  double h = 1.0/(n+1);

  //Making and filling matrix:
  arma::mat A(n,n);
  arma::mat L(n,n);
  arma::mat U(n,n);
  arma::vec x(n);
  arma::vec g(n);
  arma::vec u(n);
  arma::vec v(n);

  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      if (j == i){
        A(i,j) = 2;
      }
      else if(i == j+1 && j <= n){
        A(i,j) = -1;
      }
      else if(i == j-1 && j >= 1){
        A(i,j) = -1;
      }
      else{
        A(i,j) = 0;
      }
    }
  }
  //cout << A <<endl;

  //Solving
  for (int i = 0; i < n; i++){
    x[i] = i*h;
    g[i] = 100*exp(-10*x[i])*(h*h); //Since g = h^2f
    // Exact solution:
    u[i] = 1-(1-exp(-10))*x[i]-exp(-10*x[i]);
  }

  //Starting timer
  clock_t start, finish;
  start = clock();

  //Solving Av = g
  v = arma::solve(A,g);

  //LU-decomposition
  arma::lu(L,U,A);

  //Calculating time used
  finish = clock();
  double timeused = (double) (finish - start)/(CLOCKS_PER_SEC );
  cout << setprecision(3) << scientific << "Time used: " << timeused <<endl;

  ofile.open("dataproj1.txt");
  ofile << "  x:        v:       u:     " << endl;
  for (int i = 0; i < n; i++){
    ofile << setw(15) << setprecision(8) << x[i];
    ofile << setw(15) << setprecision(8) << v[i];
    ofile << setw(15) << setprecision(8) << u[i] << endl;
  }

  ofile.close();

  return 0;
}
