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
filename3 = str(input("Third filename : "))
filename4 = str(input("Fourth filename : "))
def read_from_file(filename1,filename2, filename3, filename4):

    infile1 = open(filename1, "r")
    infile2 = open(filename2, "r")
    infile3 = open(filename3, "r")
    infile4 = open(filename4, "r")
    """
    Read the first line as list of eigenvalues (unsorted)
    """

    eigvals_int1 = infile1.readline().split(",")
    eigvals_int2 = infile2.readline().split(",")
    eigvals_int3 = infile3.readline().split(",")
    eigvals_int4 = infile4.readline().split(",")

    eigs1 = [float(eig) for eig in eigvals_int1]
    eigs2 = [float(eig) for eig in eigvals_int2]
    eigs3 = [float(eig) for eig in eigvals_int3]
    eigs4 = [float(eig) for eig in eigvals_int4]

    eigs_sorted1 = np.sort(eigs1)
    eigs_sorted2 = np.sort(eigs2)
    eigs_sorted3 = np.sort(eigs3)
    eigs_sorted4 = np.sort(eigs4)


    """
    Empty line is read
    """

    empty_line1 = infile1.readline()
    empty_line2 = infile2.readline()
    empty_line3 = infile3.readline()
    empty_line4 = infile4.readline()


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
    """
    Third filename
    """
    elements3 = []
    lines3 = infile3.readlines()
    for line in lines3:
        element = float(line)
        elements3.append(element)

    elements3 = np.insert(elements3,0,0)
    eigenvec3 = np.insert(elements3,len(elements3),0)
    """Fourth file
    """
    elements4 = []
    lines4 = infile4.readlines()
    for line in lines4:
        element = float(line)
        elements4.append(element)

    elements4 = np.insert(elements4,0,0)
    eigenvec4 = np.insert(elements4,len(elements4),0)

    return eigenvec1, eigs_sorted1, eigs1, eigenvec2, eigs_sorted2, eigs2, eigenvec3, eigs_sorted3, eigs3, eigenvec4, eigs_sorted4, eigs4

eigenvec1, eigs_sorted1, eigs1, eigenvec2, eigs_sorted2, eigs2, eigenvec3, eigs_sorted3, eigs3, eigenvec4, eigs_sorted4, eigs4\
 = read_from_file(filename1, filename2, filename3, filename4)

rhos1 = np.linspace(0,5.5,len(eigenvec1))
rhos2 = np.linspace(0,5.5,len(eigenvec2))
rhos3 = np.linspace(0,5.5,len(eigenvec3))
rhos4 = np.linspace(0,5.5,len(eigenvec4))

plt.plot(rhos1, eigenvec1, "-", label = r"$\omega = 0.01$")
plt.plot(rhos2, eigenvec2, ".", label = r"$\omega = 0.5$")
plt.plot(rhos3, eigenvec3, ".", label = r"$\omega = 1$")
plt.plot(rhos4, eigenvec4, ".", label = r"$\omega = 5$")
plt.xlabel(r"$\rho$")
plt.ylabel(r"Probability distribution, $|u(\rho)|^2$")
plt.legend()
plt.savefig("groundstates" + str(figure) + ".png")
plt.show()
