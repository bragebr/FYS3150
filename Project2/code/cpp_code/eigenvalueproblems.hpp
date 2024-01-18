#ifndef EigenValueSolver_HPP
#define EigenValueSolver_HPP
#include<armadillo>
#include<fstream>

using namespace std;
using namespace arma;



class EigenValueSolver{
protected:
    mat R, A;
    vec D;
    int n, k, l;
    ofstream ofile;
    int min_index;
    double principalmin;

    mat I, RT;
    double tolerance;

public:
    void initialize(int m_n);

    //Jacobi method is in superclass since both BucklingBeamSolver and SLSolver uses the excact same functions
    void jacobi_rotation();
    void jacobi_method();
    double maxoffdiag();
    void write_to_file(string filename);

    void TEST_orthogonality();
    void TEST_symmetry();
    void TEST_toeplitz();
    void TEST_maxoffdiag();
    void TEST_jacobi();
    void TEST_orthogonal();
    void TEST_eigval();
};


class BucklingBeamSolver : public EigenValueSolver{
private:
  vec AnalyticEigenval;
  mat AnalyticEigenvec;
  double hh;

public:
  void init(int n);
  void solve();
  void AnalyticalSolution();

};


class SLSolver : public EigenValueSolver{
private:
  vec AnalyticEigenval;
  mat AnalyticEigenvec;
  double hh;

public:
  void init(double &rho_lower, double &rho_upper, int n, bool two_electrons, double frequency);
  void solve();
  void AnalyticalSolution();

};


#endif
