import numpy as np

def Covariance(x,y, ddof=0, offset=0):
    X_av = np.average(x)
    Y_av = np.average(y)
    temp = 0
    for i in range(0,len(x)-offset):
        temp += ((x[i] - X_av) * (y[i+offset] - Y_av))
    return temp / (len(x) - ddof)

def Correlation(x, y, ddof=0, offset=0):
    X_av = np.average(x)
    Y_av = np.average(y)
    X_std = np.std(x)
    Y_std = np.std(y)
    temp = Covariance(x,y, ddof, offset)
    return temp/(X_std*Y_std)