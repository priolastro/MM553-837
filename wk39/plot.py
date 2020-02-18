# Plot Hamiltonian for the three integrators

import matplotlib.pyplot as plt
import sys
import numpy as np
g=float(9.807)

def read_file(file_in):
    fin=open(file_in, 'r')
    lines=fin.readlines()
    return lines

for input in ['leapfrog_out.txt']:
# , 'euler_cromer_out.txt', 'leapfrog_out.txt']:
    H=[]
    P=[]
    Q=[]
    for i in read_file(input):
        q=float(i.split()[0])
        p=float(i.split()[1])
        h=0.5*p**2-g*np.cos(q)
        H.append(h)
        Q.append(q)
        P.append(p)
    # plt.plot(H[:1000], label=input)
    plt.plot(Q,label=input)
    plt.legend()
    break
plt.show()
