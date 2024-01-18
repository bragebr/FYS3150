import numpy as np
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties
import ast
"""
-----------------
font for plots
-----------------
"""

font = FontProperties()
font.set_family('monospace')

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

"""
-----------------------------------------------------------------------------
Plotting convergence towards steady state (exp.values VS NO. of MCS)
SS1GS = data for T = 1, ground state config
SS1UO = data for T = 1, random (unordered) config
SS24GS = data for T = 2.4, ground state config
SS24UO = data for T = 2.4, random (unordered) config
-----------------------------------------------------------------------------
"""
"""
SS1GS = readfile("Steady_20x20_1.0_ordered.dat")
SS1UO = readfile("Steady_20x20_1.0_unordered.dat")
SS24GS = readfile("Steady_20x20_2.4_ordered.dat")
SS24UO = readfile("Steady_20x20_2.4_unordered.dat")
"""
AVERAGE_DIM40 = readfile("Data/Averages_40_0.005_10M.dat")
AVERAGE_DIM60 = readfile("Data/Averages_60_0.005_10M.dat")
AVERAGE_DIM80 = readfile("Data/Averages_80_0.005_10M.dat")
AVERAGE_DIM100 = readfile("Data/Averages_100_dT0_005_10M.dat")

fig, ((ax1,ax2),(ax3,ax4)) = plt.subplots(2,2, figsize = (16,8), tight_layout = True)



ax1.set_title("Mean Energy as a Function of Temperature", fontproperties = font)
ax1.plot(AVERAGE_DIM40[0], AVERAGE_DIM40[1], 'r.', label = "40x40")
ax1.plot(AVERAGE_DIM60[0], AVERAGE_DIM60[1], '.',color="black", label = "60x60")
ax1.plot(AVERAGE_DIM80[0], AVERAGE_DIM80[1], 'r--', label = "80x80")
ax1.plot(AVERAGE_DIM100[0], AVERAGE_DIM100[1], '--',color="black",label = "100x100")

ax1.set_ylabel("E/J", fontproperties = font)
ax1.legend(loc = "best")


ax2.set_title("Heat Capacity as a Function of Temperature", fontproperties = font)
ax2.plot(AVERAGE_DIM40[0], AVERAGE_DIM40[2], 'r.', label = "40x40")
ax2.plot(AVERAGE_DIM60[0], AVERAGE_DIM60[2], '.', color = "black", label = "60x60")
ax2.plot(AVERAGE_DIM80[0], AVERAGE_DIM80[2], 'r--',label = "80x80")
ax2.plot(AVERAGE_DIM100[0], AVERAGE_DIM100[2], '--', color = "black", label = "100x100")
ax2.set_ylabel(r"$C_V\ /\ Jk_B$", fontproperties = font)
ax2.legend(loc = "best")

ax3.set_title("Absolute Magnetization as a Function of Temperature", \
fontproperties = font)
ax3.plot(AVERAGE_DIM40[0], AVERAGE_DIM40[3], 'r.', label = "40x40")
ax3.plot(AVERAGE_DIM60[0], AVERAGE_DIM60[3], '.', color = "black", label = "60x60")
ax3.plot(AVERAGE_DIM80[0], AVERAGE_DIM80[3], 'r--', label = "80x80")
ax3.plot(AVERAGE_DIM100[0], AVERAGE_DIM100[3], '--', color = "black", label = "100x100")
ax3.set_xlabel(r"$k_B T$", fontproperties = font)
ax3.set_ylabel(r"$\langle |M| \rangle$", fontproperties = font)
ax3.legend(loc = "best")

ax4.set_title("Magnetic Susceptibility as a Function of Temperature", fontproperties = font)
ax4.plot(AVERAGE_DIM40[0], AVERAGE_DIM40[4], 'r.',label = "40x40")
ax4.plot(AVERAGE_DIM60[0], AVERAGE_DIM60[4], '.', color = "black",label = "60x60")
ax4.plot(AVERAGE_DIM80[0], AVERAGE_DIM80[4], 'r--',label = "80x80")
ax4.plot(AVERAGE_DIM100[0], AVERAGE_DIM100[4], '--', color = "black",label = "100x100")
ax4.set_xlabel(r"$k_B T$", fontproperties = font)
ax4.set_ylabel(r"$\mathcal{X}$", fontproperties = font)
ax4.legend(loc = "best")
plt.savefig("expvalsplot.png")
plt.show()

"""
----------------------------------------------------------------------------
make_grid() defines a function which takes in data about the orientation of
each spin point in a spint lattice. This data is produced here for the initial
temperature T = 2.0, the within a short range of the critical temperature Tc
and the final temperature T = 2.6. Such data for a 80x80 grid and a 100x100
grid may be found under "Data" in the "Code" folder on our GITHUB
----------------------------------------------------------------------------
"""

"""
def make_grid(file):
    lines = open(file, "r").readlines()
    Grid = []
    for line in lines:
        new_line = ast.literal_eval(line)
        row = []

        for i in range(len(new_line)):
            row.append((float(new_line[i])))
        Grid.append(row)

    return Grid


Grid = make_grid("Data/Lattice_100_Init.dat")
Grid2 = make_grid("Data/Lattice_100_Tc.dat")
Grid3 = make_grid("Data/Lattice_100_Final.dat")

def plot_grid(ax, grid):
    for i in range(len(grid[0])):
        for j in range(len(grid[0])):
            if grid[i][j] < 0:
                ax.plot(i,j, marker = "s", color = "red")
            else:
                ax.plot(i,j, marker = "s", color = "black")


fig, ((ax1,ax2, ax3)) = plt.subplots(1,3, figsize=(16,8))

fig.suptitle("Plot of Magnetic Domains for Initial and Final States")

plot_grid(ax1,Grid)

plot_grid(ax2,Grid2)

plot_grid(ax3,Grid3)

plt.show()
"""

"""
infile = open("Averages.dat", "r")

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


plt.plot(temperatures, Xs)
plt.show()
"""
