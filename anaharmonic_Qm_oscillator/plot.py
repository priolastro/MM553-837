import matplotlib.pyplot as plt
import numpy as np
from subprocess import *

lambda_val = "0.5"
nmin = "1"
nmax = "30"
level = "4"

output=check_output( './anharmonic '+lambda_val+' '+nmin+' '+nmax+' '+level, shell=True) 
mat_dim, eval = np.loadtxt('eigenvalues.dat', unpack=True)

plt.xlabel('N')
plt.ylabel('$E_n$')
plt.plot(mat_dim, eval, 'r-', label='$x_{n}$') 
plt.legend()
plt.grid(True)

plt.show() 
