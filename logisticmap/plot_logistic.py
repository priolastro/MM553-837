import matplotlib.pyplot as plt
import os

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

for dirpath, dirname, filename in os.walk("./"):
	for file in filename:
		if "log0336789.dat" in file:
			x,y=plot(file)
			plt.xlabel('time')
			plt.ylabel('population')
			plt.plot(x[:12],y[:12], label=file)

plt.legend(loc="upper right")
plt.show()
