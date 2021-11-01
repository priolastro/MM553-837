import numpy as np
import matplotlib.pyplot as plt
from scipy.constants import Boltzmann

data=np.loadtxt('data.txt',)
autocorr = []

for index, i in enumerate(data):
    if index+2 >= len(data):
        break
    expval = data[index]*data[index+2]
    autocorr.append(expval)

plt.plot(autocorr)
plt.show()

# for i in [0,10,20,30]:
    # beta=(Boltzmann*(i+273.15))**(-1)
    # print(beta)