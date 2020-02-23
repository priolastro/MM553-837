###################################################
 # Compares integrators for a single simple pendulum 
 # oscillator: naiveEuler, EulerCromer and Leapfrog.
 # Prints Hamiltonian and phase space plot and animation.
###################################################

from numpy import sin, cos, pi, array
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from subprocess import *

def plot_hamiltonian(file):
    nome=str(file).split()[0].replace('dat','')
    q, p=np.loadtxt(file, unpack=True)
    H=0.5*p[:]**2-G*np.cos(q[:])
    plt.plot(H,label=nome)
    plt.legend(loc='upper right')

def plot_phasespace(file):
    nome=str(file).split()[0].replace('dat','')
    q, p=np.loadtxt(file, unpack=True)
    plt.plot(q,p,label=nome)
    plt.legend(loc='upper right')

G =  9.807 # acceleration due to gravity, in m/s^2
L1 = 1.0 # length of pendulum 1 in m
M1 = 1.0 # mass of pendulum 1 in kg

t = "100"
niter = "2500"
outfile = "pendulum.dat"
dt = float(t)/float(niter) 

output=check_output( './simple_pendulum.out '+t+' '+niter+' '+ '>' + outfile, shell=True) 
q,p=np.loadtxt(outfile, unpack=True)

plot_hamiltonian(outfile)
plt.show()
plot_phasespace(outfile)
plt.show()

x = +L1*sin(q[:])
y = -L1*cos(q[:])

plt.plot(x,y)
plt.show()

fig = plt.figure()
ax = fig.add_subplot(111, autoscale_on=False, xlim=(-2, 2), ylim=(-2, 2))
ax.grid()

line, = ax.plot([], [], 'o-', lw=2)
time_template = 'time = %.1f'
time_text = ax.text(0.05, 0.9, '', transform=ax.transAxes)

def init():
    line.set_data([], [])
    time_text.set_text('')
    return line, time_text

def animate(i):
    thisx = [0, x[i]]
    thisy = [0, y[i]]

    line.set_data(thisx, thisy)
    time_text.set_text(time_template%(i*dt))
    return line, time_text

ani = animation.FuncAnimation(fig, animate, np.arange(1, len(x)),
    interval=15, blit=True, init_func=init)

plt.show()
