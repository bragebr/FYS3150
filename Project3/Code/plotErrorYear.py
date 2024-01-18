import matplotlib.pyplot as plt
import numpy as np


errorEuler = np.array([7.89E-4, 7.33E-2, 1.94, 2.59E1, 4.16E4, 3.99E6])
errorCromer = np.array([3.29E-5, 3.15E-4, 3.14E-3, 4.2E-2, 3.25E3, 3.99E6])
errorVerlet = np.array([1.97E-9, 1.97E-7, 1.97E-5, 1.97E-3, 1.88E-1, 2.06E6])

Years = np.array([0, 1, 2, 3, 4, 5])

plt.title("Maximum Numerical Error as a Function of Years (logarithmic scale)")
plt.plot(Years, np.log10(errorEuler), 'r-o', label="Euler Forward")
plt.plot(Years, np.log10(errorCromer), 'b-o', label="Euler-Cromer")
plt.plot(Years, np.log10(errorVerlet), 'g-o', label="Velocity Verlet")
plt.xlabel("log Years")
plt.ylabel("log Maximum Error")
plt.legend()
plt.show()
