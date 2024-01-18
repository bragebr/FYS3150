#include "eigenvalueproblems.hpp"
#include<armadillo>

using namespace std;
using namespace arma;

// Constructing the matrix A for solving the QM problem
mat construct_QM(double &rho_lower, double &rho_upper, int n, bool two_electrons, double frequency) {

  // Step size h given by numbers of mesh points n
  double h = (rho_upper - rho_lower)/(n+1);
  double hh = h*h;

  // Constructing an empty matrix A and
  mat A_temp(n,n); A_temp.zeros();

  // Declaring sub-, super- and main diagonal elements
  double d = 2.0/hh; // main diagonal elements
  double e = -1.0/hh; // sub - and super diagonal elements

  // Declaring the variable potential V
  double V = 0.0;

  // Filling in diagonals
  for (int i=0; i<n; i++) {
    double rho = rho_lower + (i+1)*h;

    // Is the quantum system interacting or not?
    // OBS! Need to fix infinity problem in 1/rho for rho = 0
    // Use ifelse statement?
    if (two_electrons) {
        V = frequency*frequency*rho*rho + 1/rho;
    } else {
      V = rho*rho;
    }

    // filling main diagonal for varying potential V
    A_temp(i,i) = d + V;

    // filling sub- and super diagonals up to n
    if (i < n-1) {
      A_temp(i,i+1) = e;
        A_temp(i+1,i) = e;
    }
  }
  return A_temp;
}

void SLSolver::init(double &rho_lower, double &rho_upper, int n, bool two_electrons, double frequency){
  initialize(n);
  A = construct_QM(rho_lower,rho_upper,n,two_electrons,frequency);
}

void SLSolver::solve(){
  TEST_symmetry();

  jacobi_method();
  //Analytic
  AnalyticalSolution();
  mat arma_mat = diagmat(A);
  cout << arma_mat << endl;
  //Since we only need the values on the main diagonal from A:
  for (int i = 0; i < n; i++){
    D(i) = A(i,i);
  }
  //cout << "Computed eigenvalues: \n"<< D <<endl;
  //cout << "Computed eigenvectors: \n" << R <<endl;


//-----------
  for (int i = 0; i < n; i++){
    D(i) = A(i,i);
  }
  uword min_index_arma = D.index_min();
  cout << min_index_arma << endl;

  tolerance = 1E-8;
  TEST_orthogonality();
  TEST_eigval();
}


void SLSolver::AnalyticalSolution(){
  AnalyticEigenval = vec(n);
  AnalyticEigenvec = mat(n,n);

  vec d = vec(n);
  vec a = vec(n);
  for (int i = 0; i < n; i++){
    d(i) = A(i,i);
    if (i < n-1) {
      a(i) = A(i,i+1);
      a(i) = A(i+1,i);
    }
  }

  for (int i = 1; i <= n; i++){
    //Analytic eigenvalue
    AnalyticEigenval(i-1) = d(i-1) + 2*a(i-1)*cos(i*M_PI/(n+1));
    for (int j = 1; j <= n; j++){
      AnalyticEigenvec(i-1,j-1) = sin(j*i*M_PI/(n+1));
    }

  }
  //cout << "Analytic eigenval: \n"<<AnalyticEigenval << endl;
  //cout << "Analytic eigenvec: \n"<< AnalyticEigenvec << endl;
}
