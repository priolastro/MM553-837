import numpy as np
from matplotlib import pyplot as plt
import matplotlib.animation as animation

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

npart = 32
outfile='cord.dat'
cord = np.loadtxt(outfile, unpack=True)

fig, ax = plt.subplots()
line, = ax.plot(range(npart),np.zeros(npart)*np.NaN, 'o')
ax.set_ylim(-300, 300)
ax.set_xlim(-3, npart+3)

def update(i):
    new_data = cord[npart*i:(i+1)*npart]
    line.set_ydata(new_data)
    return line,

ani = animation.FuncAnimation(fig, update, frames=len(cord)-npart, interval=1)
plt.show()