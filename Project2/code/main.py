import os
import sys


all_cpp_codes = "./cpp_code/*.cpp"
compiler_flags = "-larmadillo -llapack -lblas"
optimization = "-O3"

os.system("echo Compiling...")
os.system("g++ " + optimization + " -o main.out" + " " + all_cpp_codes + " " + compiler_flags)

os.system("echo Executing...")
os.system("./main.out")
