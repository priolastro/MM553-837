import matplotlib.pyplot as plt
import numpy as np
outfile="circle.dat"
fin=open(outfile, 'r')
lines=fin.readlines()

t_dat=[]
x_dat=[]
y_dat=[]
vx_dat=[]
vy_dat=[]
theta_dat=[]
x_0=1
y_0=1
for l in lines:
    temp=l.split()
    t_dat.append(float(temp[0]))
    x_dat.append(float(temp[1]))
    y_dat.append(float(temp[2]))
    vx_dat.append(float(temp[3]))
    vy_dat.append(float(temp[4]))
    theta_dat.append(np.arctan2((float(temp[2])-y_0), (float(temp[1])-x_0)))    
    
#plt.plot(t_dat, x_dat, label="x(t)")
#plt.plot(t_dat, y_dat, label="y(t)")
plt.plot(t_dat, theta_dat, label="$\Theta$(t)")
plt.axhline(y=np.pi, color='r', linestyle="--", label="$\pi$")
plt.axhline(y=-np.pi, color='b', linestyle="--", label="-$\pi$")
#plt.plot(x_dat, y_dat, label="trajectory")
#plt.xlim([0,4])
#plt.ylim([0,4])
#plt.legend(loc="upper right")
plt.show()
