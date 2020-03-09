import numpy as np
from scipy.spatial.distance import pdist, squareform
from subprocess import *
import copy
import sys
import matplotlib.pyplot as plt
import matplotlib.animation as animation

t = "100"
niter = "100000"
outfile = "int.dat"
nparticles = "40"

output=check_output( './particlesbox '+t+' '+niter+' '+nparticles+' > '+outfile, shell=True) 

ene=np.loadtxt('energies.out', unpack=True)
x=range(0, len(ene))


fin = open(outfile, 'r'); 
lines=fin.readlines(); 

pctr=0; ictr=0; xyctr=0;
state=[]; xpos=[]; ypos=[];

for l in lines: 
    temp=l.split()
    q=float(temp[0]) 
    p=float(temp[1])
  
    
    if (xyctr==0):
        xpos.append(q) 
    else:
        ypos.append(q) 

    if (xyctr==0):
        xyctr=xyctr+1;
    else:
        xyctr=0;
        pctr=pctr+1;

    if (pctr==int(nparticles)):
        pctr=0;
        ictr=ictr+1; 
        state.append([copy.copy(xpos),copy.copy(ypos)]);
        xpos[:]=[]; ypos[:]=[];
  

bounds = [-2, 2, -2, 2]
#------------------------------------------------------------
# set up figure and animation
fig = plt.figure()
fig.subplots_adjust(left=0, right=1, bottom=0, top=1)
ax = fig.add_subplot(111, aspect='equal', autoscale_on=False,
                     xlim=(-3.2, 3.2), ylim=(-2.4, 2.4))

# particles holds the locations of the particles
particles, = ax.plot([], [], 'bo', ms=6)

# rect is the box edge
rect = plt.Rectangle(bounds[::2],
                     bounds[1] - bounds[0],
                     bounds[3] - bounds[2],
                     ec='none', lw=2, fc='none')
ax.add_patch(rect)

size=0.01

def init():
    """initialize animation"""
    global rect
    particles.set_data([], [])
    rect.set_edgecolor('none')
    return particles, rect

def animate(i):
    """perform animation step"""
    global rect, ax, fig, state,size

    ms = int(fig.dpi * 2 * size * fig.get_figwidth()
             / np.diff(ax.get_xbound())[0])
    
    # update pieces of the animation
    rect.set_edgecolor('k')
    particles.set_data(state[i][0], state[i][1])
    particles.set_markersize(ms)
    return particles, rect

ani = animation.FuncAnimation(fig, animate, frames=int(niter),
                              interval=10, blit=True, init_func=init)


plt.show()
