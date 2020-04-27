import numpy as np
from matplotlib import pyplot as plt
import matplotlib.animation as animation
import matplotlib.ticker as ticker
from subprocess import *

tau='10'
niter='10000'
npart='128'
outfile='dati.dat'

# output=check_output('./main'+' '+tau+' '+niter+' '+npart, shell=True)

K, P, avS, sqS=np.loadtxt(outfile, unpack=True)
H = K + P
errore_H=format((H[-1]-H[0])/H[0],'.2e')
errore_AvS=format((avS[-1]-avS[0])/avS[0],'.2e')
average_AvS=format(np.average(avS),'.2e')
errore_sqS=format((sqS[-1]-sqS[0])/sqS[0],'.2e')
average_sqS=format(np.average(sqS),'.2e')


f1,ax1 = plt.subplots()

ax1.ticklabel_format(useOffset=False)
ax1.plot(H[:50000], label='Energy', color='tab:red')
ax1.set_ylabel('Energy (a.u.)')
ax1.set_xlabel('Step')
ax1.set_title('Error = '+str(errore_H))
plt.show()

f2,(ax2,ax3) = plt.subplots(2,1,sharex=True)
ax2.plot(avS[:50000], label="Average speed", color="tab:blue")
ax3.plot(sqS[:50000], label="Squred speed", color="tab:green")
ax2.legend()
ax2.set_title('Error = '+str(errore_AvS)+'Average='+str(average_AvS))
ax3.legend()

ax3.set_xlabel('Step')
ax2.set_ylabel('Speed (a.u.)')
ax3.set_ylabel('Speed (a.u.)')
ax3.set_title('Error = '+str(errore_sqS)+'Average='+str(average_sqS))
plt.show()