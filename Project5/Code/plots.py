import numpy as np
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties

"""
-----------------
font for plots
-----------------
"""

font = FontProperties()
font.set_family('monospace')
fontsize = 18

"""
-------------------------------------------------------------------------------
File reading function readfile(xfile) takes in filename for data with format
col 1 - col2 - col3 ... - col n
-------------------------------------------------------------------------------
"""
#This variable sets the xlim. Change as needed.
xlimit = 70

def readfile(xfile):
    infile = open(xfile, "r")
    first_line = infile.readline().split()

    lines = infile.readlines()
    values = [[] for j in range(len(first_line))]
    for line in lines:
        row = line.split(",")
        for i in range(len(row)-1):
            values[i].append(float(row[i]))
    return values, len(lines)

def plotfiles(simmax):
    firstfile, lenlines1 = readfile("Data/trial"+str(0)+".dat")
    averages = np.zeros([3,lenlines1])
    S = np.zeros([simmax,lenlines1])
    I = np.zeros([simmax,lenlines1])
    R = np.zeros([simmax,lenlines1])
    S[0] = firstfile[1]
    I[0] = firstfile[2]
    R[0] = firstfile[3]

    for i in range(3):
        averages[i] += firstfile[i+1]
    plt.plot(firstfile[0], firstfile[1], color = "r", label = "S", alpha = 0.4)
    plt.plot(firstfile[0], firstfile[2], color = "b",label = "I", alpha = 0.4)
    plt.plot(firstfile[0], firstfile[3], color = "g", label = "R", alpha = 0.4)
    for i in range(simmax-1):
        infile, lenlines = readfile("Data/trial" + str(i+1) + ".dat")

        S[i+1] = infile[1]
        I[i+1] = infile[2]
        R[i+1] = infile[3]

        for i in range(3):
            averages[i] += infile[i+1]
        plt.plot(infile[0], infile[1], color = "r", alpha = 0.1)
        plt.plot(infile[0], infile[2], color = "b", alpha = 0.1)
        plt.plot(infile[0], infile[3], color = "g", alpha = 0.1)

    plt.plot(firstfile[0], averages[0]/no_simulations, "--", color = "black", label="Mean(S)")
    plt.plot(firstfile[0], averages[1]/no_simulations, "--", color = "darkred", label="Mean(I)")
    plt.plot(firstfile[0], averages[2]/no_simulations, "--", color = "cyan", label="Mean(R)")

    print("Averages for S, I, R: " , averages[0][-1]/no_simulations, averages[1][-1]/no_simulations, averages[2][-1]/no_simulations)

    #Plott RK4
    infile, lenlines = readfile("Data/RK4.dat")
    plt.plot(infile[0], infile[1], label = "RK4 (S)", color = "deeppink")
    plt.plot(infile[0], infile[2], label = "RK4 (I)", color = "turquoise")
    plt.plot(infile[0], infile[3], label = "RK4 (R)", color = "chartreuse")
    plt.legend(loc="upper right", ncol=3)#, bbox_to_anchor=(1,0.6))
    print("Last value for RK4 S, I, R: ", infile[1][-1], infile[2][-1], infile[3][-1])
    plt.grid()
    plt.xlabel("Time (arbitrary units)", fontproperties = font, fontsize=fontsize)
    plt.ylabel("NO. of Nodes", fontproperties = font, fontsize=fontsize)
    plt.xlim([0,xlimit])
    plt.ylim([-20,360])
    plt.figure()

    #Standard deviations
    plt.title("Standard Deviation in S, I and R for Multiple Simualtions",\
    fontproperties = font)
    std_s = np.zeros(lenlines1)
    std_i = np.zeros(lenlines1)
    std_r = np.zeros(lenlines1)
    for i in range(lenlines1):
        temp_s = np.zeros(simmax)
        temp_i = np.zeros(simmax)
        temp_r = np.zeros(simmax)
        for j in range(simmax):
            temp_s[j] = S[j][i]
            temp_i[j] = I[j][i]
            temp_r[j] = R[j][i]
        std_s[i] = np.std(temp_s)
        std_i[i] = np.std(temp_i)
        std_r[i] = np.std(temp_r)

    print("Final standard deviation for S, I, R: " + str(std_s[-1]) + ", " + str(std_i[-1]) + ", " + str(std_r[-1]))
    plt.plot(firstfile[0], std_s, label="S")
    plt.plot(firstfile[0], std_i, label="I")
    plt.plot(firstfile[0], std_r, label="R")
    plt.grid()

no_simulations = 100
plotfiles(no_simulations)
plt.legend()
plt.xlabel("Time (arbitrary units)", fontproperties = font, fontsize=fontsize)
plt.ylabel("Diviation $\sigma$", fontproperties = font, fontsize=fontsize)
plt.xlim([0,xlimit])
plt.show()
