import matplotlib.pyplot as plt
import os

file_in="bif.dat"

def plot(outfile):
	fin=open(outfile, 'r')
	lines=fin.readlines()
	x_dat=[]
	y_dat=[]
	for l in lines:
		temp=l.split()
		x_dat.append(float(temp[0]))
		y_dat.append(float(temp[1]))
	return x_dat, y_dat

x,y=plot(file_in)
plt.plot(x,y,',')

plt.legend(loc="upper right")
plt.show()
