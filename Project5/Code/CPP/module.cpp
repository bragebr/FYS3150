#include "module.h"

using namespace std;
using namespace arma;

double trans(double t, dvec params, bool addseasonalvar){
  if (addseasonalvar == 1){
      return (double) params(6)*cos(params(7)*t)+params(8);
  }
  else {
    return params(0);
  }
}


//Uncomment as needed to switch between pulse vaccination and exponential vaccination
double vax(double t, bool vaxvar){
  //Pulse vaccination
  if (vaxvar == 1){
    if (cos(t) > 0 && t > 1)  return 4.;
    else return 0;
  }
  //Exponential vaccination
  // if (vaxvar == 1 && t > 15) {
  //   return exp((t-15)*0.3);
  // }
  else {
    return 0;
  }
}

// Single time step MC simulation
void SIRSIM(dvec &SIR,dvec &params,double &dt, dvec &probmoves, bool vitalparams,
bool addseasonalvar, bool vaxvar, double t)
{
  double S_I, I_R, R_S, D_S, D_I_INF, D_I, D_R, S_S, S_R;
  int N;

  // Network size N
  N = SIR(0) + SIR(1) + SIR(2);


      // Initialize the seed and call the Mersienne algo
      random_device seed;
      mt19937_64 gen(seed());

      // Set up the uniform distribution for x \in [[0, 1]
      uniform_real_distribution<double> RNG(0.0,1.0);

      params(0) = trans(t, params, addseasonalvar); //seasonalvar

      probmoves(0) = (params(0)*SIR(0)*SIR(1)/N)*dt; // P(S -> I)
      probmoves(1) = params(1)*SIR(1)*dt;   // P(I -> R)
      probmoves(2) = params(2)*SIR(2)*dt;   // P(R -> S)

      if (vitalparams == 1)
      {
        probmoves(3) = params(3)*SIR(0)*dt;   // P(S -> Dead from S)
        probmoves(4) = params(4)*SIR(1)*dt;   // P(I -> Dead from Infection)
        probmoves(5) = params(3)*SIR(1)*dt;   // P(I -> Dead from natural cause)
        probmoves(6) = params(3)*SIR(2)*dt;   // P(R -> Dead from natural cause)
        probmoves(7) = params(5)*N*dt;        // P(Born into S -> S)
      }
      if (vaxvar == 1){
        probmoves(8) =  vax(t, vaxvar)*dt; //P(S -> R) vaccination
      }
      else probmoves(8) = 0;

      S_I = probmoves(0);
      cout << "S_I : " << S_I << endl;
      I_R = probmoves(1);
      cout << "I_R : " << I_R << endl;
      R_S = probmoves(2);
      cout << "R_S : " << R_S << endl;
      D_S = probmoves(3);
      D_I_INF = probmoves(4);
      D_I = probmoves(5);
      D_R = probmoves(6);
      S_S = probmoves(7);
      S_R = probmoves(8); //vaccination

      if (RNG(gen) < S_I && SIR(0) > 0) // Transition only if a node in S exists
      {
        SIR(0) --; // A node in S becomes infected and is moved to S
        SIR(1) ++;
      }
      if (RNG(gen) < I_R && SIR(1) > 0)
      {
        SIR(1) --; // An infected node is moved to R
        SIR(2) ++;
      }
      if (RNG(gen) < R_S && SIR(2) > 0)
      {
        SIR(2) --; // A recovered/removed node is moved to S
        SIR(0) ++;
      }
      if (vitalparams == 1)
      {
        if (RNG(gen) < D_S && SIR(0) > 0) // A node in S dies
        {
          SIR(0) --;
        }
        if (RNG(gen) < D_I_INF && SIR(1) > 0) // A node in I dies from infection
        {
          SIR(1) --;
        }
        if (RNG(gen) < D_I && SIR(1) > 0) // A node in I dies
        {
          SIR(1) --;
        }
        if (RNG(gen) < D_R && SIR(2) > 0) // A node in R dies
        {
          SIR(2) --;
        }
        // It is possible to add a cap on how many that may be born into S
        // in the if - statement by S(0) < cap

        if (RNG(gen) < S_S) // A node is born and added to S
        {
          SIR(0) ++;
        }
      }
      if (RNG(gen) < S_R && SIR(0) > 0) // A node in S is vaccinated
      {
        SIR(0) --;
        SIR(2) ++;
        // Update rate of loss of immunity to hinder vaccinated nodes from
        // transitioning back into S
        params(2) = params(2) - (params(2)/(2*N));

      }

}

void Menu(double &tmax, int &steps, int &simmax, double &h){

  cout << "Number of integration points: ";
  cin >> steps;
  cout << "Simulation time: ";
  cin >> tmax;
  simmax = 100; // How many stochastic simulations to perform. Change as needed.
  h = tmax/steps; // Compute a temporal resolution, used for ODEs only
}


void InitialConditions(int&network,int&ininf,dvec&params,bool&vitalparams,
bool &addseasonalvar, bool &vaxvar, int &testcase, dvec &probmoves, double &dt,
dvec SIR, double t)
{
    if (testcase == 1 && vitalparams == 0 && addseasonalvar == 0)
    {
      params.ones();
    }

    double a,b,c; // superior parameters (transmission,recovery,immunity loss)
    double d,di,e; // vital parameters (death (natural or infection), birth)
    double a0,omega,capa; // seasonal variation parameters

    if (testcase == 0)
    {
      cout << "Do you wish to add vital dynamics? [Y=1/N=0]: ";
      cin >> vitalparams; // Read in an integer value for studying vital dynamics
      cout << "Do you wish to add seasonal variation? [Y=1/N=0]: ";
      cin >> addseasonalvar; // Read in a boolean value for studying seasonal changes
      cout << "Do you wish to add vaccination? [Y = 1/N = 0]: ";
      cin >> vaxvar; // Read in a boolean value for studying vaccination

      if (addseasonalvar == 1)
      {
        cout << "Average transmission rate: ";
        cin >> a0; // Read in average rate of transmission
        cout << "Maximum deviation from average transmission rate: ";
        cin >> capa; // Read in largest deviation from average rate of transmission
        cout << "Frequency of change: ";
        cin >> omega; // Read in how frequently the nodes are unusually susceptible
        params(6) = capa; params(7) = omega; params(8) = a0;
      }
      cout << "Network size (integer): ";
      cin >> network; // Read in size of network.
      cout << "Number of initially infected agents (integer): ";
      cin >> ininf; // Read in NO. of initially infected nodes
      cout << "Rate of transmission: ";
      cin >> a; // Read in rate of transmission - project description uses 4.0
      cout << "Rate of recovery: ";
      cin >> b; // Read in rate of recovery - project description uses 1.0 - 4.0
      cout << "Rate of loss of immunity: ";
      cin >> c; // Read in immunity loss rate - project description uses 0.5

      // Make a basis list of parameters with each rate on sequential indices
      params(0) = a; params(1) = b; params(2) = c;

      int N = network;
      params(0) = trans(t, params, addseasonalvar);

      // Temporal resolution computed by the least likely transition
      dt = min({4./(params(0)*N), 1./(params(1)*N), 1./(params(2)*N)});

      //Make a basis list of the different probability moves
      probmoves(0) = (params(0)*SIR(0)*SIR(1)/N)*dt; // P(S -> I)
      probmoves(1) = params(1)*SIR(1)*dt; // P(I -> R)
      probmoves(2) = params(2)*SIR(2)*dt; // P(R -> S
    }

    if (testcase == 0 && vitalparams == 1) {
      cout << "Death rate due to natural causes: ";
      cin >> d; // Read in death rate
      cout << "Death rate due to infection: ";
      cin >> di; // Read in death rate due to infection
      cout << "Birth rate: ";
      cin >> e; // Read in birth rate

      params(3) = d; params(4) = di; params(5) = e;
      int N = network;
      dt = min({4./(params(0)*N), 1./(params(1)*N), 1./(params(2)*N),
        1./(params(3)*N), 1./((params(4)+params(3))*N)});
    }

}

void get_derivatives(double &t, dvec &SIR, dvec &dSIR, dvec&params, int &network,
  bool &vitalparams, bool &addseasonalvar, bool vaxvar, int &testcase)
  {

  if (vitalparams == 0)
  {
    dSIR(0) = params(2)*SIR(2) - (trans(t,params,addseasonalvar)*SIR(0)*SIR(1))/network - vax(t, vaxvar);
    dSIR(1) = (trans(t, params, addseasonalvar)*SIR(0)*SIR(1)/network) - params(1)*SIR(1);
    dSIR(2) = params(1)*SIR(1) - params(2)*SIR(2) + vax(t, vaxvar);
  }

  else if (vitalparams == 1)
  {
    dSIR(0) = params(2)*SIR(2) - (trans(t,params,addseasonalvar)*SIR(0)*SIR(1))/network
     - params(3)*SIR(0) + params(5)*network;
    dSIR(1) = (trans(t, params, addseasonalvar)*SIR(0)*SIR(1)/network) - params(1)*SIR(1)
     - params(3)*SIR(1) - params(4)*SIR(1);
    dSIR(2) = params(1)*SIR(1) - params(2)*SIR(2) - params(3)*SIR(2);
  }

  if (testcase == 1 && vitalparams == 0 && addseasonalvar == 0)
  {
    dSIR(0) = 2.*SIR(0) + 3.;
    dSIR(1) = 2.*SIR(1) + 3.;
    dSIR(2) = 2.*SIR(2) + 3.;
  }

}

void RK4(double &t, double &h, dvec &SIR, dvec &dSIR, dvec &sol, dvec params,
int network, bool &vitalparams, bool &addseasonalvar, bool vaxvar, int&testcase)
{
  dvec k1(3),k2(3),k3(3),k4(3),y_local(3);
  double h2 = h*0.5;
  double h6 = h/6.;
  double th2 = t + h2;
  double th = t + h;
  get_derivatives(t,SIR,dSIR,params,network,vitalparams,addseasonalvar,vaxvar,testcase);
  for (int i=0; i<3; i++){
    k1(i) = dSIR(i)*h2; // calculation of k1
    y_local(i) = SIR(i) + k1(i);
  }
  get_derivatives(th2,y_local, dSIR, params,network,vitalparams,addseasonalvar,vaxvar,testcase);
  for (int i=0; i<3; i++){
    k2(i) = dSIR(i)*h2; // calculation of k2
    y_local(i) = SIR(i) + k2(i);
  }
  get_derivatives(th2,y_local,dSIR,params,network,vitalparams,addseasonalvar,vaxvar,testcase);
  for (int i = 0; i<3; i++){
    k3(i) = dSIR(i)*h2*2; // calculation of k3
    y_local(i) = SIR(i) + k3(i);
  }
  get_derivatives(th,y_local,dSIR,params,network,vitalparams,addseasonalvar,vaxvar,testcase);
  for (int i=0; i<3; i++){
    k4(i) = dSIR(i)*h2*2; // calculation of k4
  }
  for (int i=0; i<3; i++){
    sol(i) = SIR(i) + 1./6.*(k1(i) + 2*k2(i) + 2*k3(i) + k4(i));
  }
}

void RK4SIM(double& t,double& h,dvec& RK4SIR,dvec& dSIR,dvec& sol,dvec params,
  int network,bool& vitalparams,bool& addseasonalvar, bool vaxvar, int& testcase){

    network = RK4SIR(0) + RK4SIR(1) + RK4SIR(2);
    get_derivatives(t,RK4SIR,dSIR,params,network,vitalparams,addseasonalvar,vaxvar,testcase);
    RK4(t,h,RK4SIR,dSIR,sol,params,network,vitalparams,addseasonalvar,vaxvar,testcase);
    for (int i=0;i<3;i++){
      RK4SIR(i) = sol(i);
    }
}


void writetofile(double &t, dvec &SIR, ofstream &wfile){
  wfile << setiosflags(ios::showbase | ios::uppercase);
  wfile << setw(15) << setprecision(10) << t << ",";
  wfile << setw(15) << setprecision(10) << SIR(0) << ",";
  wfile << setw(15) << setprecision(10) << SIR(1) << ",";
  wfile << setw(15) << setprecision(10) << SIR(2) << ",";
  wfile << endl;
}

void UnitTests(dvec &params, bool&vitalparams, bool&addseasonalvar, bool&vaxvar, double t, dvec&SIR, dvec&probmoves, dvec&dSIR, dvec&sol) {
  int Testspassed = 0;
  int Testsfailed = 0;
  params(0) = 1;
  params(6) = 1;
  params(7) = 0;
  params(8) = 0;

  //Trans-function tests
  //Expect function to return cos(0) = 0
  if (trans(1,params,1) != 1) {
    cout << "Function \"Trans\" is behaving unexpectedly!\n";
    cout << endl << trans(1,params,1);
    Testsfailed++;
  }
  else { Testspassed++; }
  //Expect function to return params(0)
  if (trans(1,params,0) != 1) {
    cout << "\nFunction \"Trans\" is behaving unexpectedly!\n";
    Testsfailed++;
  }
  else { Testspassed++; }

  //Vax-function tests
  if (vax(1,1) != 0) {
    cout << "Function \"vax\" is behaving unexpectedly!\n";
    Testsfailed++;
  }
  else { Testspassed++; }
  if (vax(11,1) != 22) {
    cout << "Function \"vax\" is behaving unexpectedly!\n";
    Testsfailed++;
  }
  else { Testspassed++; }

  //SIRSIM testing
  vitalparams = 0; addseasonalvar = 0; vaxvar = 0; t = 1;
  double dt = 1.;
  SIR(0) = 1; SIR(1) = 1;
  params(1) = params(2) = 0; params(0) = 2;
  SIRSIM(SIR, params, dt, probmoves, vitalparams, addseasonalvar, vaxvar, t);
  //With variables above, one person should jump from S->I
  if (SIR(0) != 0 && SIR(1) != 2 && SIR(2) != 0) {
    cout << "Function \"SIRSIM\" is behaving unexpectedly!\n";
    Testsfailed++;
  }
  else { Testspassed++; }
  params(0) = 0; params(1) = 2;
  //Now expect one person to jump from I->R
  SIRSIM(SIR, params, dt, probmoves, vitalparams, addseasonalvar, vaxvar, t);
  if (SIR(0) != 0 && SIR(1) != 1 && SIR(2) != 1) {
    cout << "Function \"SIRSIM\" is behaving unexpectedly!\n";
    Testsfailed++;
  }
  else { Testspassed++; }

  //RK4 testing
  SIR(0) = 1; SIR(1) = 0; SIR(2) = 0;
  double h = 0.1; int testcase = 1; t = 0.1;
  RK4(t, h, SIR, dSIR, sol, params, 2, vitalparams, addseasonalvar, vaxvar, testcase);
  //These inital values should return sol(0) = 1.42017
  if (fabs(sol(0)-1.4201700000) > 1E-5)  {
    cout << "Function\"RK4\" is behaving unexpectedly!\n";
    cout << endl << sol(0) << endl;
    Testsfailed++;
  }
  else { Testspassed++; }

  cout << endl << Testspassed << " tests passed!\n" << Testsfailed << " tests failed.\n";
}
