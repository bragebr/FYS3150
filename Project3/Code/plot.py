import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import sys


filename = sys.argv[3]
#myfile = open("positionVerlet.csv", 'r')
myfile = open(filename, 'r')

#first_line = myfile.readline()
# print(first_line)
lines = myfile.readlines()

n = len(lines)
antall_planeter = int(sys.argv[1])
lim = float(sys.argv[2])
circular_orbit = int(sys.argv[4])
planets = np.zeros((3, antall_planeter,n))
planetlabel = ["Sun", "Earth", "Jupiter", "Mercury", "Mars", "Venus", "Saturn", "Uranus", "Neptune", "Pluto"]


i = 0  #iteration
for line in lines:
    j = 0 #planet
    k = 0 #position
    row = line.split(",")

    planet_counter = (len(row)-1)/3
    while j < planet_counter:
        planets[0][j][i] = float(row[k])
        planets[1][j][i] = float(row[k+1])
        planets[2][j][i] = float(row[k+2])
        k += 3
        j += 1
    i += 1


fig = plt.figure()
ax = fig.gca(projection='3d')
j = 0


elem = 500
if circular_orbit==1:
    r = 1.0
    theta = np.linspace(-np.pi, np.pi,100)
    x = r*np.cos(theta)
    y = r*np.sin(theta)
    ax.scatter(x,y, s = 2, c = "red", marker = 'o', label = "Earth's circular orbit")
while j < antall_planeter:
    if j == 0:
        ax.scatter(planets[0][j][0::elem], planets[1][j][0::elem], planets[2][j][0::elem], label=planetlabel[j], s=30, c='yellow')
    else:
        ax.plot(planets[0][j][0::elem], planets[1][j][0::elem], planets[2][j][0::elem], label=planetlabel[j])

    j += 1

tittel = filename[8:-4]

ax.set_xlim3d(-lim, lim)
ax.set_ylim3d(-lim, lim)
ax.set_zlim3d(-lim, lim)
plt.title(tittel)
plt.xlabel("x [AU]")
plt.ylabel('y [AU]')
ax.set_zlabel('z [AU]')
plt.legend(loc="upper right")
plt.show()
