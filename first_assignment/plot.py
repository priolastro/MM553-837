import numpy as np
from matplotlib import pyplot as plt
import matplotlib.animation as animation


outfile = "dati.out"
q,p=np.loadtxt(outfile, unpack=True)
q1=q[::4]
q2=q[1::4]
q3=q[2::4]
q4=q[3::4]
p1=p[::4]
p2=p[1::4]
p3=p[2::4]
p4=p[3::4]

H=0.5*(p1[:]**2+p2[:]**2+p3[:]**2+p4[:]**2)+0.5*((q1[:]-q2[:])**2+(q2[:]-q3[:])**2+(q3[:]-q4[:])**2+q1[:]**2+q4[:]**2)
plt.plot(H)
plt.show()


# fig, ax = plt.subplots()
# ax.set_xlim(-2,2)
# ax.set_ylim(-2,2)
# line_q1, = ax.plot([],[], '-o', lw=1)
# line_q2, = ax.plot([],[], '-o', lw=1)
# line_q3, = ax.plot([],[], '-o', lw=1)

# def init():
#     line_q1.set_data([],[])
#     line_q2.set_data([],[])
#     line_q3.set_data([],[])
#     return line_q1, line_q2, line_q3 

# def animation_frame(i):
#     pos_q1=[0,q1[i]]
#     pos_q2=[0,q2[i]]
#     line_q1.set_data(-1, pos_q1)
#     line_q2.set_data(0, pos_q2)
# #     line1.set_data(1, thisp1)
#     return line_q1, line_q2

# animation=animation.FuncAnimation(fig, func=animation_frame, init_func=init, 
#                          frames=200,interval=20,blit=True)
# plt.show()



