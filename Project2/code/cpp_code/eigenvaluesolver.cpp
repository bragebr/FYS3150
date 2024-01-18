#include "eigenvalueproblems.hpp"
#include<armadillo>

using namespace std;
using namespace arma;

void EigenValueSolver::initialize(int m_n){
  n = m_n;
  R = mat(n,n);
  A = mat(n,n);
  D = vec(n);
}


void EigenValueSolver::write_to_file(string filename){
  // Writing to file
  ofile.open(filename.c_str());
  for (int i = 0; i < n; i++){
    if (i < n-1)
    {
      ofile << D(i) << ",";
    } else
    {
      ofile << D(i);
    }
  }
  ofile << "\n" << endl;
  int gs_index = min_index;
  for (int j = 0; j < n; j++){
      ofile << R(j,gs_index) << endl;
    }
  ofile.close();
}


void EigenValueSolver::jacobi_rotation() {
  // declaring sine and cosine
  double s,c;
  if (A(k,l) != 0.0) {
    double t,tau;
    tau = (A(l,l) - A(k,k))/(2*A(k,l));
    // tau can be either + or -
    if (tau > 0){
      t = 1.0/(tau + sqrt(1.0 + tau*tau));
    } else {
      t = -1.0/(-tau + sqrt(1.0 + tau*tau));
    }

    c = 1/sqrt(1+t*t);
    s = c*t;
  } else {
    c = 1.0;
    s = 0.0;
  }

  double a_kk, a_ll, a_ik, a_il, r_ik, r_il;
  a_kk = A(k,k);
  a_ll = A(l,l);

  A(k,k) = c*c*a_kk - 2.0*c*s*A(k,l) + s*s*a_ll;
  A(l,l) = s*s*a_kk + 2.0*c*s*A(k,l) + c*c*a_ll;
  A(k,l) = 0.0; // this is where zeros are hard-coded
  A(l,k) = 0.0;

  for (int i=0; i<n; i++) {
    if (i!=k && i != l) {
      a_ik = A(i,k);
      a_il = A(i,l);
      A(i,k) = c*a_ik - s*a_il;
      // symmetric matrix
      A(k,i) = A(i,k);
      A(i,l) = c*a_il + s*a_ik;
      // symmetric matrix
      A(l,i) = A(i,l);
    }
    r_ik = R(i,k);
    r_il = R(i,l);
    R(i,k) = c*r_ik - s*r_il;
    R(i,l) = c*r_il + s*r_ik;
  }
}


double EigenValueSolver::maxoffdiag() {
  double maximum_offdiag = 0.0;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {

      double aij = fabs(A(i,j));

      if (aij > maximum_offdiag) {
        maximum_offdiag = aij;

        l = i; k = j;
      }
    }
  }
  return maximum_offdiag;
}

void EigenValueSolver::jacobi_method() {

// Declaring a matrix R for storing computed eigenvectors

  for (int i=0; i < n; i++) {
    for (int j=0; j < n; j++) {
      if (i==j) {
        R(i,j) = 1.0;
      }   else {
        R(i,j) = 0.0;
      }
    }
  }

// Now declaring matrix indices, tolerance, # of iterations
  double max_itr = n * n * n;
  double tol = 1e-8;
  int iterations = 0;
  double max = maxoffdiag();
  // initializing timer
  clock_t start, finish;
  start = clock();

  while (max > tol && iterations <= max_itr) {
    max = maxoffdiag();
    jacobi_rotation();
    iterations++;
  }

  finish = clock();
  double time = (double) (finish - start)/(CLOCKS_PER_SEC);

  principalmin = A(0,0);
  min_index = 0;
  for (int i = 1; i < n; i++)
  {
    if (A(i,i) < principalmin)
    {
      principalmin = A(i,i);
      min_index = i;
    }
  }
  cout << "Number of iterations: " << iterations << endl;
  cout << setprecision(5) << scientific << "Time used: " << time << endl;
}
