import os
import sys


all_cpp_codes = "./cpp_code/*.cpp"
compiler_flags = ""
optimization = "-O3"

arg = sys.argv[1]

os.system("echo Compiling...")
os.system("g++ " + "--std=c++11 " + optimization + " -o main.out" + " " + all_cpp_codes + " " + compiler_flags)

os.system("echo Executing...")
os.system("./main.out " + arg)

int(arg)

#Kun enkel plotting av two-body system. Skriver ut error og konservering av angulærmoment.
if (int(arg) == 1):
    os.system("python3 plot.py 2 1.5 positionEuler.csv 0")
    os.system("python3 plot.py 2 1.5 positionEulerCromer.csv 0")
    os.system("python3 plot.py 2 1.5 positionVerlet.csv 0")
#Energibevaring og bevaring av angulærmoment
if (int(arg) == 2):
    os.system("python3 plotEnergy.py 2 energyVerlet.csv")
    os.system("python3 plotEnergy.py 2 energyEuler-Forward.csv")
#arg = 3: Kun CPU-timing skrives ut

#Varierende beta
if (int(arg) == 4 or int(arg) == 5):
    print("Plot result?\n")
    x = input("[y/n]:")
    if x == "y":
        os.system("python3 plot.py 2 1.2 positionVerlet.csv 0")
        os.system("python3 plotEnergy.py 2 energyVerlet.csv")
#Escape velocity
if (int(arg) == 6):
    os.system("python3 plotEnergy.py 2 energyVerlet.csv")
    os.system("python3 plot.py 2 50 positionVerlet.csv 1")

#Three-body problem
if (int(arg) == 7 or int(arg) == 8):
    os.system("python3 plot.py 3 5.2 positionVerlet.csv 0")

if (int(arg) == 9):
    os.system("python3 plot.py 10 32 positionVerlet.csv 0")

if (int(arg) == 10):
    print("Plot orbit?\n")
    x = input("[Y/N]: ")
    if x == "Y":
        os.system("python3 plot.py 2 1 positionVerlet.csv 0")
    os.system("python plot_precession.py")
