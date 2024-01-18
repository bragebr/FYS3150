#include "module.h"

ofstream ofile;
ofstream rfile;

int main(){
    string outfilename;
    outfilename = "trial";
    int steps, network, ininf, simmax, testcase; // NO. of steps, size of network, NO. of infected
    double tmax,t,h,a,b,c,dt; // max simulation time, initial time, res, params
    dvec SIR(3,fill::zeros), dSIR(3,fill::zeros), sol(3,fill::zeros);
    dvec params(11,fill::zeros);
    dvec probmoves(9, fill::zeros);
    dvec RK4SIR(3,fill::zeros);
    bool vitalparams, addseasonalvar, vaxvar;

    cout << "Perform a precision test run? [1/0]: "; cin >> testcase;

    if (testcase != 2) {
      Menu(tmax,steps,simmax,h);
      InitialConditions(network,ininf,params,vitalparams,addseasonalvar,vaxvar,testcase,probmoves,dt,SIR,t);

      if (testcase == 1) {SIR(0) = 1.; SIR(1) = 2.; SIR(2) = 3.;}

      else
      {
        SIR(0) = network-ininf;
        SIR(1) = ininf;
        SIR(2) = 0;
      }

    //Monte Carlo
    c = params(2);
    auto timestartMC = chrono::high_resolution_clock::now();
    //For-loop runs for Monte Carlo Simulations
    for (int sim = 0; sim <= simmax; sim++)
    {
      SIR(0) = network-ininf;
      SIR(1) = ininf;
      SIR(2) = 0;

      t = 0.0;
      ofile.open("Data/" + outfilename + to_string(sim) + ".dat");
      ofile << "Time" << " " << "S" << " " << "I" << " " << "R" << endl;

      while (t <= tmax){
        SIRSIM(SIR,params,dt, probmoves, vitalparams, addseasonalvar, vaxvar, t);
        writetofile(t, SIR, ofile);
        t += dt;
      }
      params(2) = c;

      ofile.close();
    }

    auto timefinishMC = chrono::high_resolution_clock::now();
    cout << "Run time for average MC method: " << chrono::duration_cast<chrono::nanoseconds>(timefinishMC - timestartMC).count()/(pow(10,9)*simmax) << endl;
    cout << "Run time for total MC method: " << chrono::duration_cast<chrono::nanoseconds>(timefinishMC - timestartMC).count()/pow(10,9) << endl;
    rfile.open("Data/RK4.dat");
    rfile << "Time" << " " << "S" << " " << "I" << " " << "R" << endl;

    //Runge-Kutta
    t = 0.0;
    RK4SIR(0) = network-ininf;
    RK4SIR(1) = ininf;
    RK4SIR(2) = 0;
    auto timestartRK4 = chrono::high_resolution_clock::now();
    while (t <= tmax){
      RK4SIM(t,h,RK4SIR,dSIR,sol,params,network,vitalparams,addseasonalvar,vaxvar,testcase);
      writetofile(t, RK4SIR, rfile);
      t += h;
    }

    rfile.close();
    auto timefinishRK4 = chrono::high_resolution_clock::now();
    cout << "Run time for RK4 method: " << chrono::duration_cast<chrono::nanoseconds>(timefinishRK4 - timestartRK4).count()/pow(10,9) << endl;

  }
  else if (testcase == 2) {
    UnitTests(params, vitalparams, addseasonalvar, vaxvar, t, SIR, probmoves, dSIR, sol);
  }

  return 0;
}
