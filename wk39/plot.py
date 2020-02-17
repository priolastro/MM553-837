import matplotlib.pyplot as plt
import sys
import numpy as np
g=float(9.807)

def read_file(file_in):
    fin=open(file_in, 'r')
    lines=fin.readlines()
    return lines

input=sys.argv[1]
H=[]
for i in read_file(input):
    q=float(i.split()[0])
    p=float(i.split()[1])
    h=0.5*p**2-g*np.cos(q)
    H.append(h)
plt.plot(H)
plt.show()
