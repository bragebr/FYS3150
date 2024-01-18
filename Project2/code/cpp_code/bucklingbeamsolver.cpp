#include "eigenvalueproblems.hpp"
#include<armadillo>
#include<cmath>

using namespace std;
using namespace arma;

void BucklingBeamSolver::init(int n){
  initialize(n);
  //Making matrix A:
  double lower_boundary, upper_boundary, h;

  /*
  Hard-coding boundary conditions
  */

  lower_boundary = 0.0;
  upper_boundary = 1.0;

  h = (upper_boundary - lower_boundary)/(n+1);
  hh = h*h;

  double d, e;
  d = 2/hh;
  e = -1/hh;

  //mat A(n,n);
    for (int i = 0; i < n; i++){
      A(i,i) = d;
        if (i < n-1)
        {
          A(i,i+1) = e;
          A(i+1,i) = e;
        }
    }
}

void BucklingBeamSolver::solve(){
  TEST_symmetry();
  TEST_toeplitz();

  jacobi_method();
  /*
  AnalyticalSolution();
  mat arma_mat = diagmat(A);
  cout << arma_mat << endl;*/
  //Since we only need the values on the main diagonal from A:
  for (int i = 0; i < n; i++){
    D(i) = A(i,i);
  }
  //cout << D <<endl;
  tolerance = 1E-10;
  TEST_eigval();
  TEST_orthogonality();
}
/*
void BucklingBeamSolver::AnalyticalSolution(){
  AnalyticEigenval = vec(n);
  AnalyticEigenvec = mat(n,n);

  for (int i = 1; i <= n; i++){
    //Analytic eigenvalue with d = 2/h^2 and a = -1/h^2 for our case
    AnalyticEigenval(i-1) = d + 2*a*cos(i*M_PI/(n+1));
    for (int j = 1; j <= n; j++){
      AnalyticEigenvec(i-1,j-1) = sin(j*i*M_PI/(n+1));
    }

  }
  cout << "Analytic eigenval: \n"<<AnalyticEigenval << endl;
  cout << "Analytic eigenvec: \n"<< AnalyticEigenvec << endl;
}
*/
