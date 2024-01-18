#include<iostream>
#include<armadillo>
#include<cmath>
#include<iomanip>
#include "time.h"

using namespace std;
using namespace arma;
ofstream ofile;

// Forward substitution
void Forward(double *b, double *g, double *g_tilde, double *a, double *c, int n, double *x, double h){
  g_tilde[1] = g[1];
  for (int i=2; i < n; i++){
    // Rewriting b to b_tilde
    b[i] = b[i] - c[i-1]*a[i]/b[i-1];
    g_tilde[i] = g[i] - g_tilde[i-1]*a[i]/b[i-1];
  }
}

void Backward(double *b, double *g_tilde, double *c, double *v, int n){
  for (int i = n; i >= 1; i--){
    v[i] = (g_tilde[i] - c[i]*v[i+1])/b[i];
  }
}

void MaxError(double *v, double *u, int n){
  double *ComputeError = new double[n];
  
  for (int i = 1; i < n; i++){
      ComputeError[i] = (double) abs(log10(abs(v[i] - u[i])/u[i]));
  }
  cout << "The maximum error is: " << *max_element(ComputeError, ComputeError + n) << endl;
}

int main(int argc, char* argv[]){
  // Declaring vectors
  int n = atoi(argv[1]);
  double *b, *a, *c, *g, *g_tilde, *v, *x, *u;
  // Declaring diagonal, subdiagonal and superdiagonal:
  b = new double[n+1];
  a = new double[n+1];
  c = new double[n+1];
  // Descrete interval between [0,1]:
  x = new double[n+1];
  // Source term
  g = new double[n+1];
  g_tilde = new double[n+1];
  // Numerical solution:
  v = new double[n+2];
  // Analytic solution:
  u = new double[n+1];
  double h = 1.0/(n+1);

  //For our case:
  for (int i = 0; i< n+1; i++){
    x[i] = i*h;
    g[i] = 100*exp(-10*x[i])*(h*h); //Since g = h^2f
    // Exact solution:
    u[i] = 1-(1-exp(-10))*x[i]-exp(-10*x[i]);
  }
  // Filling the diagonals:
  fill_n(b, n+1, 2);
  fill_n(a, n+1, -1);
  fill_n(c, n+1, -1);
  c[-1] = 0.0;
  // For the special case v[n] = g_tilde[n]:
  v[n+1] = 0.0;

  //Starting timer
  clock_t start, finish;
  start = clock();

  // Running the forward and backward substitution with pointers to change global variable
  Forward(b, g, g_tilde, a, c, n, x, h);
  Backward(b, g_tilde, c, v, n);


  //Calculating time used
  finish = clock();
  double timeused = (double) (finish - start)/(CLOCKS_PER_SEC );
  cout << setprecision(3) << scientific << "Time used: " << timeused <<endl;
  MaxError(v, u, n);

  // Writing to file
  ofile.open("dataproj1.txt");
  ofile << "  x:     v:   u:  " << endl;
  for (int i = 0; i < n; i++){
    ofile << setw(15) << setprecision(8) << x[i];
    ofile << setw(15) << setprecision(8) << v[i];
    ofile << setw(15) << setprecision(8) << u[i] << endl;
  }

  ofile.close();

  // Deleting allocated memory
  delete[] b;
  delete[] a;
  delete[] c;
  delete[] x;
  delete[] g;
  delete[] g_tilde;
  delete[] v;

  return 0;
}
