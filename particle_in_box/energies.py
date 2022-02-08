from numpy import sin, cos, pi, array
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from subprocess import *

pot,kin,ene=np.loadtxt('energies.out', unpack=True)
x=range(0, len(pot))

plt.plot(ene)
plt.show()
