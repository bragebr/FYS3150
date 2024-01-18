import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

print("Please enter file names when prompted and index of figure you wish to save.\
 For the buckling beam problem this should be BucklingBeam.dat, for one electron in the QM solver it should be \
Schroedinger_one_electron.dat, and for two electrons it should be \
Schroedinger_two_electrons_frequency.dat where frequency is the previously entered \
value.")
figure = str(input("Index of figure : "))
filename1 = str(input("First filename : "))
filename2 = str(input("Second filename : "))
def read_from_file(filename1,filename2):

    infile1 = open(filename1, "r")
    infile2 = open(filename2, "r")
    """
    Read the first line as list of eigenvalues (unsorted)
    """

    eigvals_int1 = infile1.readline().split(",")
    eigvals_int2 = infile2.readline().split(",")

    eigs1 = [float(eig) for eig in eigvals_int1]
    eigs2 = [float(eig) for eig in eigvals_int2]

    eigs_sorted1 = np.sort(eigs1)
    eigs_sorted2 = np.sort(eigs2)


    """
    Empty line is read
    """

    empty_line1 = infile1.readline()
    empty_line2 = infile2.readline()


    """
    Remaning lines in data file are elements of the "ground state" column vector in
    R
    """
    elements1 = []
    lines1 = infile1.readlines()
    for line in lines1:
        element = float(line)
        elements1.append(element)

    elements1 = np.insert(elements1,0,0)
    eigenvec1 = np.insert(elements1,len(elements1),0)
    """
    Repeat for second file
    """
    elements2 = []
    lines2 = infile2.readlines()
    for line in lines2:
        element = float(line)
        elements2.append(element)

    elements2 = np.insert(elements2,0,0)
    eigenvec2 = np.insert(elements2,len(elements2),0)

    return eigenvec1, eigs_sorted1, eigs1, eigenvec2, eigs_sorted2, eigs2

eigenvec1, eigs_sorted1, eigs1, eigenvec2, eigs_sorted2, eigs2\
 = read_from_file(filename1, filename2)

rhos1 = np.linspace(0,5.5,len(eigenvec1))
rhos2 = np.linspace(0,5.5,len(eigenvec2))

plt.plot(rhos1, eigenvec1, "-", label = r"Analytic")
plt.plot(rhos2, eigenvec2, ".", label = r"Computed")
plt.xlabel(r"$\rho$")
plt.ylabel(r"Displacement")
plt.legend()
plt.savefig("groundstates" + str(figure) + ".png")
plt.show()
