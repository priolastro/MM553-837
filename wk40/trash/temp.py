import numpy as np
# list=range(0,10,1)
# k=0
# for i in range(3):
#     print(i)
#     for j in range(3-1):
#         if j>=i:
#             print(i,j)
#             break
#         print(2*i,2*j,2*i+1,2*j+1)

for i in range(10):
    ix=i
    iy=i+1
    if i%2!=0:
        ix=i-1
        iy=i
    for n in range(10):
        if ix/2==n:
            continue
        print(ix,2*n,iy,2*n+1)
        # if ix==i:
        #     print(i,2*n)
        # else:
        #     print(i,2*n+1)
