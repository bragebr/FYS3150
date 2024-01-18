#ifndef MODULE_H_INCLUDED
#define MODULE_H_INCLUDED

#include<armadillo>
#include<iostream>
#include<iomanip>
#include<stdlib.h>
#include<cmath>
#include<random>
#include<cstdlib>
#include<ctime>
#include<string>

using namespace std;
using namespace arma;

// Call to make menu with simulation steps, simulation time etc.
void Menu(double &, int &, int &, double &);
// Call to return variable parameter a
double trans(double t,dvec params, bool addseasonalvar);
// Call to make initial conditions on vector form
void InitialConditions(int&network,int&ininf,dvec&params,bool&vitalparams,
bool &addseasonalvar,bool &vaxvar,int &testcase, dvec &probmoves, double &dt, dvec SIR, double t);
// Call to compute initial derivatives
void get_derivatives(double &t, dvec &SIR, dvec &dSIR, dvec&params, int &network, bool &vitalparams, bool &addseasonalvar, bool vaxvar, int &testcase);
// Call to perform one time step RK4 approximation
void RK4(double& t,double& h,dvec& SIR,dvec& dSIR,dvec& sol,dvec params,int network,bool& vitalparams,bool& addseasonalvar,bool vaxvar, int& testcase);
// Call to perform one temporal MC step
void SIRSIM(dvec &SIR,dvec &params,double &dt, dvec &probmoves, bool vitalparams, bool addseasonalvar, bool vaxvar, double t);
// Call to write data to file
void writetofile(double&,dvec&,ofstream&);
// Call to run Runge-Kutta solver
void RK4SIM(double& t,double& h,dvec& RK4SIR,dvec& dSIR,dvec& sol,dvec params,int network,bool& vitalparams,bool& addseasonalvar, bool vaxvar, int& testcase);
// Call to return vaccination variable
double vax(double t, bool vaxvar);
// Call to run UnitTests
void UnitTests(dvec &params, bool&vitalparams, bool&addseasonalvar, bool&vaxvar, double t, dvec&SIR, dvec&probmoves, dvec&dSIR, dvec&sol);

#endif
