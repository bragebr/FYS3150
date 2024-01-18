#include "eigenvalueproblems.hpp"
#include<armadillo>

using namespace std;
using namespace arma;

void EigenValueSolver::TEST_orthogonality() {
  //cout << "Testing orthogonality of computed eigenvectors..." << endl;
  I.eye(n,n);
  RT = trans(R);
  // if the sum R^TR - I approximates zero in all entries
  // R contains orthogonal basis vectors
  if ((RT*R - I).is_zero(tolerance)) {
    cout << "[TEST]: TEST_orthogonality PASSED!" << endl;
  } else {
    cout << "[TEST]: TEST_orthogonality FAILED!" << endl;
  }
}

void EigenValueSolver::TEST_eigval(){
  vec eig_sym_eigval = eig_sym(A);
  vec sortD = sort(D);
  if ((eig_sym_eigval - sortD).is_zero(tolerance)){
    cout << "[TEST]: TEST_eigval PASSED!" << endl;
  } else {
    cout << "[TEST]: TEST_eigval FAILED!" << endl;
  }



}


void EigenValueSolver::TEST_symmetry() {
  cout << "Making sure input matrix is symmetric..." << endl;
  for (int i = 0; i < n-1; i++){
        if (A(i,i+1) == A(i+1,i)){
        } else {
          cout << "Error: given matrix is not symmetric" << endl;
        }
  }
}

// test for the matrix A in the Buckling Beam problem
// A should definitly be a Toeplitz matrix
void EigenValueSolver::TEST_toeplitz() {
  for (int i = 0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if (i!=j){
        if (A(i,i) > sum(fabs(A(i,j)))) {
          }
          else {
            cout << "[TEST]: The matrix is not a Toeplitz matrix" << endl;
        }
      }

      }
    }
  }

// Testing the maxoffdiag function with 3x3 test matrix with known
// maximum value 5 on off-diagonals
void EigenValueSolver::TEST_maxoffdiag()
{
  double max = maxoffdiag();
  if (max == 5)
  {
    cout << "[TEST]: TEST_MAXOFFDIAG PASSED!" << endl;
  } else
  {
    cout << "[TEST]: TEST_MAXOFFDIAG FAILED" << endl;
  }
}
  /*
  ----------------------
  Testing maxoffdiag
  with 3x3 test matrix
  Make actual unit test
  mat M;
  M << 3 << 1 << 0 << endr
    << 1 << 3 << 5 << endr
    << 0 << 5 << 3 << endr;
  ----------------------
  */
void EigenValueSolver::TEST_jacobi(){
  // here we will be testing how precise the method is based on the benchmark
  // of Armadillo eig_sym function. There is a great difference in the precision
  // when diagonalizing the Toeplitz matrix for the Buckling Beam and when
  // diagonalizing the non-constant matrices in the QM problems

  double tol = 1e-8;

}
