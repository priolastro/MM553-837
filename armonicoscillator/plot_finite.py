import matplotlib.pyplot as plt
import numpy as np
from subprocess import *

a = "1"
v0 = "5.0"
nmin = "5"
nmax = "50"
level = "1"
outfile = "energy.dat"

output=check_output( './finite '+a+' '+v0+' '+nmin+' '+nmax+' '+level, shell=True) 

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
