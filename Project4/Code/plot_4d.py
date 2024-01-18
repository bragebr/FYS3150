import numpy as np
import matplotlib.pyplot as plt

n = 100

states = np.zeros(n)
mcs = np.zeros(n)

with open("4d.txt") as infile:


    for i in range(n):
        mcs[i] = infile.readline()
        states[i] = infile.readline()

plt.plot(mcs,states)
plt.show()
