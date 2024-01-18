# Project 3: Model of the solar system
Building a model for the solar system using ordinary differential equations

## Article
In this folder we have collected all of the files related to the report. Here you will find the pdf and tex file among other files for the report.

## Code
In this folder we have collected all of the files related to the program. Here you will find a folder containing all of the c++ code that should be compiled together amongst scripts that plots the results. To run the program you can do the following:

### How to run the program:

Run "main.py x" from the Code folder with x being which problem you want to run. x for the different problems are:

x = 1: Circular binary Earth-Sun system with plots for the different solvers, cout of the maximum error that the solvers differ from a perfect circular orbit with r = 1AU and boolean value if the angular momentum is conserved.

x = 2: Plot of kinetic and potential energy for the same binary system as over as well as the maximum error and boolean value of conservation of angular momentum.

x = 3: CPU timings will be printed to the terminal.

x = 4: Testing forms of the force for the circular binary system with input for different beta.

x = 5: Testing forms of the force for the elliptical binary system with input for different beta.

x = 6: Testing escape velocity.

x = 7: Three body problem, the Sun, Earth and Jupiter, where the sun is fixed to the center.

x = 8: The three body system where to Sun is unfixed.

x = 9: Multi body system

x = 10. The perihelion precession of Mercury.

main.py will then compile and execute all the files within the cpp_code folder with g++, -std=c++11 and -O3. The program generates different files for different calculations. The VelocityVerlet() function will generate "positionVerlet.csv" and "energyVerlet.csv", VelocityVerletRel() generates "perihelionMercury.csv", EulerForward() generates "positonEuler.csv" and EulerCromer() generates "positionEulerCromer.csv". The files are structured in this way:
positonX.csv: [planet1x, planet1y, planet1z, planet2x, planet2y, planet2z, ...] with iterations on the rows.
energyVerlet.csv: [planet1Potential, planet1Kinetic, planet2Potential, planet2Kinetic] with iterations on the rows.

Then main.py will then run the plot.py or plotEnergy.py script with the number of planets, size of the axis for the plot and filename as the command line arguments; "plot.py NumberOfPlanets SizeOfAxis Filename.csv".
