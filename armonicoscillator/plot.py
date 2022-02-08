import matplotlib.pyplot as plt
import numpy as np
from subprocess import *

lambda_val = "0.3"
nmin = "2"
nmax = "20"
level = "0"
outfile = "energy.dat"

output=check_output( './anharmonic '+lambda_val+' '+nmin+' '+nmax+' '+level, shell=True) 

fin = open(outfile, 'r'); 

lines=fin.readlines(); 

xdat=[]; 
ydat=[];

for l in lines:
    temp=l.split();

    xdat.append(float(temp[0]));
    ydat.append(float(temp[1])); 


plt.xlabel('N'); plt.ylabel('$E_n$'); 
plt.plot(xdat,ydat,'r-',label='$x_{n}$'); 
plt.grid(True);

plt.show() 
