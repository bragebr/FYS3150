import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression
import sys

myfile = open("perihelionMercury.csv", "r")

lines = myfile.readlines()

N = len(lines)
print(N)
thetas = []
convert_arcsec = 4.848*1e-6
for line in lines:
    theta = float(line)
    thetas.append(theta/convert_arcsec)


number_of_orbits = np.linspace(0,N+1,N).reshape(-1,1)
mdl = LinearRegression().fit(number_of_orbits, thetas)
print(mdl.coef_)
plt.plot(number_of_orbits, thetas)
plt.show()
