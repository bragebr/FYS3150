import numpy as np
import matplotlib.pyplot as plt

from sklearn.linear_model import LinearRegression

N = [1E1,1E2, 1E3,1E4,1E5,1E6,1E7]
Ns = np.array([np.log10(n) for n in N]).reshape((-1,1))
Ns_EC = Ns[:-2]
error_E = [4.19*1E0,7.17*1E-1,7.69*1E-2,7.87*1E-3,7.89*1E-4,7.89*1E-5,1.40*1E-5]
error_log_E = np.array([np.log10(a) for a in error_E])
error_EC = [5.31*1E-1,3.34*1E-2,3.14*1E-3,3.15*1E-4,3.29*1E-5,1.74*1E-5,2.02*1E-5]
error_log_EC = np.array([np.log10(a) for a in error_EC])
error_log_EC_short = error_log_EC[:-2]
error_VV = [1.87*1E-1,1.97*1E-3,1.97*1E-5,1.97*1E-7,1.97*1E-9,1.97*1E-11,7.65*1E-14]
error_log_VV = np.array([np.log10(a) for a in error_VV])
timed_E = [3.04e-4,9.29e-4,6.70*1e-3,5.96*1e-2,5.98*1e-1,5.98*1E0,6.60*1E1]
timed_log_E = np.array([np.log10(a) for a in timed_E])
timed_EC = [1.57*1E-4,6.80*1E-4,6.89*1E-3,6.18*1E-2,5.64*1E-1,5.58*1E0,6.59*1E1]
timed_log_EC = np.array([np.log10(a) for a in timed_EC])
timed_VV = [2.68e-4,7.23e-4,8.50*1E-3,6.65*1e-2,6.54*1e-1,6.79*1E0,6.75*1E1]
timed_log_VV = np.array([np.log10(a) for a in timed_VV])

mdl_E = LinearRegression().fit(Ns,timed_log_E,1)
mdl_error_E = LinearRegression().fit(Ns,error_log_E,1)
print("Gradient of Euler-curve:",mdl_error_E.coef_)



mdl_EC = LinearRegression().fit(Ns,timed_log_EC,1)
mdl_error_EC = LinearRegression().fit(Ns_EC,error_log_EC_short,1)
print("Gradient of Euler-Cromer curve:", mdl_error_EC.coef_)


mdl_VV = LinearRegression().fit(Ns,timed_log_VV,1)
mdl_error_VV = LinearRegression().fit(Ns,error_log_VV,1)
print("Gradient of Velocity Verlet curve:", mdl_error_VV.coef_)

NSS = np.linspace(0,7,1000)
plt.plot(Ns,timed_log_E,'b-o', label = "Euler Data")
plt.plot(Ns,timed_log_VV,'r-o', label = "Euler-Cromer Data")
plt.plot(Ns,timed_log_EC, 'g-o', label = "Velocity Verlet Data")

plt.title(r"Elapsed Run Times as a Function of $N$ (logarithmic scale)")
plt.xlabel(r"Number of integration points [$\log\ N$]", fontsize = 12)
plt.ylabel(r"Run Time [$\log \ s$ ]", fontsize = 12)
plt.legend(loc = "upper left")
plt.savefig('runtimes_proj3.png')
plt.show()

plt.title(r"Maximum Numerical Error as a Function of $N$ (logarithmic scale)")
plt.plot(Ns, error_log_E, 'r-o', label = 'Euler Data')
plt.plot(Ns,error_log_EC, 'b-o', label = 'Euler-Cromer Data');
plt.plot(Ns,error_log_VV,'g-o', label = "Velocity Verlet Data")
plt.xlabel(r"$ \log\ N$", fontsize = 12)
plt.ylabel(r"$\log$ Maximum Error", fontsize = 12)
plt.legend()
plt.savefig('maxerrorplot_proj3.png')

plt.show()
