import matplotlib.pyplot as plt
import numpy as np
from subprocess import *

lambda_val = "0.0"
nmin = "10"
nmax = "10"
level = "0"
outfile = "wave_func.dat"

output=check_output( './anharmonic '+lambda_val+' '+nmin+' '+nmax+' '+level+' > anharmonic.log', shell=True) 

fin = open(outfile, 'r'); 

lines=fin.readlines(); 

xdat=[]; 
ydat=[];

for l in lines:
    temp=l.split();

    xdat.append(float(temp[0]));
    ydat.append(float(temp[1])); 


plt.xlabel('x'); plt.ylabel('$\psi(x)$'); 
plt.plot(xdat,ydat,'r-',label='$x_{n}$'); 
plt.grid(True);

plt.show() 
plt.close()
