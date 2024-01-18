import numpy as np
import matplotlib.pyplot as plt


"""
------------------------------------------------------------------------------
func readfile reads files w/ format col 1 - col 2 - col 3 ... col n and returns
a nested list containing each column such that plotting simply becomes
plot(values[index i], values[index j]), i.e plotting the values contained in the
column i and the column j
-----------------------------------------------------------------------------
"""

def readfile(xfile):
    infile = open(xfile, "r")
    first_line = infile.readline().split(",")
    lines = infile.readlines()
    values = [[] for j in range(len(first_line))]
    for line in lines:
        row = line.split(",")
        for i in range(len(row)):
            values[i].append(float(row[i]))
    return values

#infile = readfile("Data/Steady_20x20_2.4_unordered.dat")
infile = readfile("Averages1.dat")
infile24 = readfile("Averages24.dat")
equilibration = 10000

energies = infile[1][equilibration:]
energies24 = infile24[1][equilibration:]
n1 = len(energies);
n2 = len(energies24);
counts1 = -np.asarray(energies)/(n2); counts2 = -np.asarray(energies24)/(n2)
std1 = np.std(energies)
std2 = np.std(energies24)
fig, ((ax1,ax2)) = plt.subplots(1,2, figsize = (16,8))
plt.suptitle(r"A Plot of the Energy Distribution at $k_B T = 1.0\ J$ and $k_B T = 2.4\ J$")
ax1.hist(energies, bins = 10, ec = "black", weights = counts1, label = r"$\sigma = $"+"%.6f"%std1)
ax2.hist(energies24, bins = 15, ec = "black", weights = counts2, label = r"$\sigma = $"+"%.6f"%std2)
ax1.set_xlabel("Energies"); ax2.set_xlabel("Energies")
ax1.set_ylabel("Occurence [%]")
ax1.legend()
ax2.legend()
plt.savefig("distr")
plt.show()
