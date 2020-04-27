import sys
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

npart = int(sys.argv[1])
outfile='cord.dat'
cord = np.loadtxt(outfile, unpack=True)

fig, ax = plt.subplots()
line, = ax.plot(range(npart),np.zeros(npart)*np.NaN, 'o')
ax.set_ylim(-20, 20)
ax.set_xlim(-3, npart+3)

def update(i):
    new_data = cord[npart*i:(i+1)*npart]
    line.set_ydata(new_data)
    return line,

ani = animation.FuncAnimation(fig, update, frames=(len(cord)-npart), interval=1)
ani.save('system.mp4', writer="ffmpeg", fps=1)
