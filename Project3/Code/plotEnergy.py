import numpy as np
import matplotlib.pyplot as plt
import sys

filename = str(sys.argv[2])
myfile = open(filename, 'r')

h = float(myfile.readline())
lines = myfile.readlines()
n = len(lines)
antall_planeter = int(sys.argv[1])

potential = np.zeros((antall_planeter, n))
kinetic = np.zeros((antall_planeter, n))

i = 0
for line in lines:
    j = 0 #planet
    k = 0 #energy
    row = line.split(",")
    planet_counter = (len(row)-1)/3
    while j < planet_counter:
        potential[j][i] = float(row[k])
        kinetic[j][i] = float(row[k+1])
        k += 2
        j += 1
    i += 1
myfile.close()

tittel = filename[6:-4]

sum  = kinetic + potential
x = np.arange(0, i-1)
plt.plot(x*h, potential[1][0:i-1], label='Potential')
plt.plot(x*h, kinetic[1][0:i-1], label='Kinetic')
plt.plot(x*h, sum[1][0:i-1], label='Total')
plt.legend()
plt.ticklabel_format(style='sci', axis='y', scilimits=(0,0))
plt.xlim(0,5)
plt.xlabel("Time [yr]")
plt.ylabel("Energy")
plt.title("Energy " + tittel)
plt.show()
