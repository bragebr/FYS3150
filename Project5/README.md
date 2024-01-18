Repository for Project 5 - Disease Modelling
============================================

The collaborators for this project has been

*Lars Kristian Skaar*

*Brage Brevig*

*Håkon Lindholm*

## COMPILING AND RUNNING
To compile the main program, run the file main.py found in ./Code/ with
~~~
python3 main.py
~~~
This will compile and execute the C++ program, and make relevant plots in Python after. The C++ program has been structured with a main.cpp file with the main function, and a module.h/.cpp which contains all functions the program needs. The C++ program will ask for relevant information in console. A brief explanation of the different arguments is given below:

| Prompt             | Accepted values        | Comment  |
| ------------------ | ---------------------- | ---------|
| Perform a precision test run? [1/0]: | 0/1/2, integer | **0**: Program will run "normally" and ask for needed values. **1**: Program will run with specific values for and make a file with the total error for the RK4-solver. **2**: UnitTests will be run, see description below|
| Number of integration points: | 1-<img src="https://render.githubusercontent.com/render/math?math=\infty">, integer | The number of integration points for the Runge-Kutta solver to use. |
| Simulation time: | 1-<img src="https://render.githubusercontent.com/render/math?math=\infty">, integer | This will specify (in arbitraty units) the time interval for both the Runge-Kutta solver and Monte-Carlo simulation |
| Do you wish to add vital dynamics? [Y=1/N=0] | 0/1, integer | Should vital dynamics be added? |
| Do you wish to add seasonal variation? [Y=1/N=0] | 0/1, integer | Should seasonal variation be added? |
| Do you wish to add vaccination? [Y=1/N=1] | 0/1, integer | Should vaccination be added? |
| Network size (integer) | 1-<img src="https://render.githubusercontent.com/render/math?math=\infty">, integer | **N**, total amount of population in S, I and R. (Most simulations have been run with 400)|
| Number of initially infected agents (integer): | 1-<img src="https://render.githubusercontent.com/render/math?math=\infty">, integer | Initial amount of infected population, I. (Most simulation have been run with 100 |
| Rate of transmission: | double | Variable **a**. Most simulations have been run with 4 |
| Rate of recovery: | double | Variable **b**. Most simulations have been run with b = 1,2,3,4 |
| Rate of loss of immunity: | double | Variable **c**. Most simulations have been run with 0.5 |
| Death rate due to natural causes | double | Prompted when vital dynamics are added. Variable **d** |
| Death rate due to infetion | double | Prompted when vital dynamics are added. Variable **<img src="https://render.githubusercontent.com/render/math?math=\textbf{d}_1">** |
| Birth rate: | double | Prompted when vital dynamics are added. Variable **e** |
| Average transmission rate: | double | Prompted when seasonal variation is added. Variable **<img src="https://render.githubusercontent.com/render/math?math=\textbf{a}_0">** |
| Maximum deviation from average transmission rate: | double | Prompted when seasonal variation is added. Variable **A** |
| Frequency of change: | double | Prompted when seasonal variation is added. Variable **<img src="https://render.githubusercontent.com/render/math?math=\omega">** |

To compile and run program without main.py, compile using
~~~
g++ --std=c++11 -O3 -o main.out ./CPP/*.cpp -larmadillo -llapack -lblas
~~~
and run main.out without any command line arguments.

### Output and datafiles
Program will automatically create datafiles "Data/RK4.dat" for Runge-Kutta simulation, and files "Data/trialX.dat" for Monte Carlo simulation number X. These files are handled by the python script plots.py for plotting.

### Report 
The report written for this project can be found in ./Article/. In the subfolders /Article/Figur and /Article/Oppsett are all the .tex files and pictures used in the report.

### Unit Tests
A custom function "UnitTests(args)" contained in module.cpp have been written to test the functions used by main. This function can be run by inputting "2" when prompted with "Perform a precision test run? [1/0]". A console output with tests passed/failed is given. All functions relevant to the simulations have been tested to ensure they work properly.
