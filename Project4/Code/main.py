import os
import sys
import numpy as np

"""
FOR LINUX DOWNLOAD
sudo apt-get install libopenmpi-dev
sudo apt-get install openmpi-bin

FOR mac DOWNLOAD
brew install open-mpi
"""

print("Run with or without parallelization? [1/0]")
arg = int(input("\n>>> "))




if (arg == 1):
    print("Number of cores to run with (example: 4)?")
    num_procs = input("\n>>> ")
    print("Lattice dimension (example: 2, 20, 40, 80, 100)?")
    dim = input("\n>>> ")
    print("Monte Carlo Cycles (example: 1000000)?")
    mcs = input("\n>>> ")
    print("Temperature interval lower limit (example: 2.0)?")
    tmin = input("\n>>> ")
    print("Temperature interval upper limit (example: 2.4)?")
    tmax = input("\n>>> ")
    print("Temperate step (example: 0.05)?")
    tstep = input("\n>>> ")
    cpp_code = "./cpp_code/main_parallel.cpp"
    compiler_flags = ""
    optimization = "-O3"
    args = dim + " " + mcs + " " + tmin + " " + tmax + " " + tstep
    #num_procs = "4"

    os.system("echo Compiling...")
    os.system("mpic++ " + "--std=c++11 " + optimization + " -o main.out " + cpp_code + compiler_flags)
    os.system("echo Executing...")
    os.system("mpirun -n "+ num_procs +" ./main.out " + args)
    os.system("python3 plot_parallel_basic.py")

elif (arg == 0):

    """
    print("Lattice dimension (example: 2, 20, 40, 80, 100)?")
    dim = input("\n>>> ")
    """
    print("Monte Carlo Cycles (example: 10000 (should be run with minimum 1E5))?")
    mcs = input("\n>>> ")

    print("Temperature (example: 2.4)?")
    temp = input("\n>>> ")

    #args = dim + " " + mcs + " " + temp
    args = str(20) + " " + mcs + " " + str(2.4)

    cpp_code = "./cpp_code/main_unparallel.cpp"
    optimization = "-O3"
    os.system("echo Compiling...")
    os.system("g++ " + "--std=c++11 " + optimization + " -o main.out " + cpp_code)
    os.system("echo Executing...")
    os.system("./main.out " + args)


