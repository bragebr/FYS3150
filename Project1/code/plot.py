import numpy as np
import matplotlib.pyplot as plt

myfile = open("dataproj1.txt", 'r')

first_line = myfile.readline()
# print(first_line)
lines = myfile.readlines()

# sepearate and append values

x = []
v = []
closed_form = []
errors_TDMA = np.array([-1.082, -2.701, -3.921, -4.951, -5.954, -1.204])

for line in lines:
    row = line.split()
    # print(row)
    x.append(float(row[0])); v.append(float(row[1]))
    closed_form.append(float(row[2]))
    #errors.append(float(row[3]))
myfile.close()

#loger = [np.log10(er) for er in errors_TDMA]

# closed form solution

def exact(x):
    return 1 - (1-np.exp(-10))*x - np.exp(-10*x)
n = 10; h = 1/(n+1)
xs = np.linspace(0,n+1)
plt.plot(x,v,'ro', label = 'Numerical approximation')
plt.xlabel("x")
plt.ylabel("u")
# plt.plot(x,closed_form)
plt.plot(xs*h, exact(xs*h), label = 'Closed form solution')
plt.legend(); plt.show()
n = np.array([10, 100, 1000, 10000, 100000, 1000000])
h = 1/(n+1)
plt.plot(np.log10(h), errors_TDMA, "-o")
plt.xlabel("log10(1/(n+1)")
plt.ylabel("max(log10(|($v_i$ - $u_i$)/($u_i$)|))")
plt.show()
