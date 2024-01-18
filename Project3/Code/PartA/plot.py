import numpy as np
import matplotlib.pyplot as plt

myfile = open("E_S_Sys.txt", 'r')

first_line = myfile.readline()
# print(first_line)
lines = myfile.readlines()

# sepearate and append values

x = []
y = []


for line in lines:
    row = line.split()
    # print(row)
    x.append(float(row[0])); y.append(float(row[1]))

myfile.close()

plt.plot(x,y)
plt.axis("equal")
plt.show()
