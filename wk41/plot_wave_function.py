import matplotlib.pyplot as plt
import numpy as np
from subprocess import *

lambda_val = "0.5"
nmin = "1"
nmax = "10"
level = "4"
outfile = "wave_func.dat"

output=check_output( './anharmonic '+lambda_val+' '+nmin+' '+nmax+' '+level+ ' >' + outfile, shell=True) 
x, wf = np.loadtxt('wave_func.dat', unpack=True)

plt.xlabel('x')
plt.ylabel('$\psi(x)$')
plt.xlim(-4,4)
plt.ylim(-2,2)
plt.plot(x,wf,label='$x_{n}$'); 
plt.grid(True);

plt.show()
