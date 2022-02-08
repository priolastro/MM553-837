import matplotlib.pyplot as plt
import numpy as np
from subprocess import *

# this checks the convergence of the energy  


a = "1" #box dimensions along x
b = "0.2" 
v0 = "100" #depth of the well
v1 = "50" 
nmin = "5"
nmax = "70"
level = "0"
outfile = "eigenvalues.dat"

output=check_output( './finite '+a+' '+b+' '+v0+' '+v1+' '+nmin+' '+nmax+' '+level, shell=True) 

mat_dim, eval = np.loadtxt('eigenvalues.dat', unpack=True)
plt.xlabel('N') 
plt.ylabel('$E_n$') 
plt.plot(mat_dim, eval, 'r-',label='$x_{n}$') 
plt.grid(True)
plt.show() 