import numpy as np
import matplotlib.pyplot as plt

infile = open("Averages.txt", "r")

first_line = infile.readline()

lines = infile.readlines()


energies = []
Cvs = []
Mabs = []
Xs = []
temperatures = []
for line in lines:
    row = line.split(",")
    temperatures.append(float(row[0]))
    energies.append(float(row[1]))
    Cvs.append(float(row[2]))
    Mabs.append(float(row[3]))
    Xs.append(float(row[4]))


plt.plot(temperatures, Mabs)
plt.show()
