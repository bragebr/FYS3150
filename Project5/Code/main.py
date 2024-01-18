import os
import sys

cpp_code  = "./CPP/*.cpp"
compiler_flags = "-larmadillo -llapack -lblas"
optimization = "-O3"

os.system("echo Compiling...")
os.system("g++ " + "--std=c++11 " + optimization + " -o main.out" +\
 " " + cpp_code + " " + compiler_flags)
os.system("echo Executing...")
os.system("./main.out")
os.system("python3 plots.py")
