import matplotlib.pyplot as plt
import numpy as np
from subprocess import *
import sys

a = "1"
v0 = "50"
nmin = "30"
nmax = "30"
level = sys.argv[1]
outfile = "wave_func.dat"

output=check_output( './finite '+a+' '+v0+' '+nmin+' '+nmax+' '+level, shell=True) 
x, wf = np.loadtxt('wave_func.dat', unpack=True)

plt.xlabel('x') 
plt.ylabel('$\phi_n(x)$') 
plt.plot(x,wf,'r-',label='$x_{n}$') 
# plt.axhline(x=1)
plt.plot((1,1),(0,5),'k-')
plt.plot((-1,-1),(0,5),'k-')
plt.grid(True)
plt.xlim(-3, 3)
plt.ylim(-2,6)
plt.show() 
