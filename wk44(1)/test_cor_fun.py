import numpy as np
import matplotlib.pyplot as plt
from correlation_functions import *

# example 1 from  https://www.real-statistics.com/time-series-analysis/stochastic-processes/autocorrelation-function/

data = [23.4, 24.1, 44.4, 25.5, 19.2, 37.1, 45.0, 61.8, 56.7, 62.3, 30.9, 69.6, 11.0, 56.6, 83.4, 33.9, 75.5, 87.3, 55.4, 95.2]
data_variance = Covariance(data, data)
data_covariance2 = Covariance(data, data, offset=2)
data_correlation2 = Correlation(data, data, offset=2)
print(data_variance, data_covariance2, data_correlation2, data_covariance2/data_variance)

# example 2 from  https://www.real-statistics.com/time-series-analysis/stochastic-processes/autocorrelation-function/
DowJones = [16272.01, 16472.37,16776.43,16790.19,16912.29,17050.75,17084.49,17131.86,17081.89,16924.75,17141.75,17215.97,17230.54,17217.11,17168.61,17489.16,17646.70,17623.05,17581.43,17779.52,17755.80,17663.54]

corr = [Correlation(DowJones, DowJones, offset=lag) for lag in range(1,11)]
plt.bar(range(1,11), corr, edgecolor = 'black')
plt.axhline(0, color='black')
plt.xlabel('Lag'), plt.ylabel('Autocorrelation')