import numpy as np
from matplotlib import pyplot as plt
import matplotlib.animation as animation
import matplotlib.ticker as ticker
import sys
from subprocess import *

outfile='dati.dat'

K, P, avS, sqS, Fm1, Fm2, Fm3=np.loadtxt(outfile, unpack=True)

H = K + P
errore_H=format((H[-1]-H[0])/H[0],'.2e')
average_AvS=format(np.average(avS),'.2e')
average_sqS=format(np.average(sqS),'.2e')


f1,(ax1,ax11) = plt.subplots(2,1, sharex=True)

ax1.ticklabel_format(useOffset=False)
ax1.plot(H, label='Energy', color='tab:red')
ax1.set_ylabel('Energy (a.u.)')
ax1.set_xlabel('Step')
ax1.set_title('Error = '+str(errore_H))
ax11.plot(Fm1, label='Energy mode k=1')
ax11.plot(Fm2, label='Energy mode k=2')
ax11.plot(Fm3, label='Energy mode k=3')
plt.legend()
plt.savefig('Ham.pdf')

f2,(ax2,ax3) = plt.subplots(2,1,sharex=True)
ax2.plot(avS, label="Average speed", color="tab:blue")
ax3.plot(sqS, label="Squred speed", color="tab:green")
ax2.legend()
ax2.set_title('Average='+str(average_AvS))
ax3.legend()

ax3.set_xlabel('Step')
ax2.set_ylabel('Speed (a.u.)')
ax3.set_ylabel('Speed (a.u.)')
ax3.set_title('Average='+str(average_sqS))
plt.savefig('speed.pdf')


