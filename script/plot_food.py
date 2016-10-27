#!/usr/bin/env python
import sys
import numpy as np
import matplotlib.pyplot as plt

# data = np.genfromtxt(sys.argv[1])

data = np.genfromtxt("../results/grid.txt")
plt.matshow(data)
plt.xlabel('X-axis')
plt.ylabel('Y-axis')
plt.title('Grid Visualization')
#plt.xticks(range(data.shape[0]), (np.asarray(range(data.shape[0])) - data.shape[0] / 2)*.25 )
#plt.yticks(range(data.shape[1]), (np.asarray(range(data.shape[1])) - data.shape[1] / 2)*.25 )

plt.show()

exit(0)


data = np.genfromtxt("../results/logFileWithoutDensity2.txt")
plt.plot(data[:, 0], color="red")
plt.plot(data[:, 1], color="orange")



plt.xlabel("Time")
plt.ylabel("Collected Resources")
plt.title("Collected Resources for SO-LOST")
plt.legend( ("Source 1", "Source 2") )
plt.show()

# data = np.genfromtxt("../results/logFileWithDensity2.txt")
# plt.plot(data[:, 0] + data[:, 1])


# data = np.genfromtxt("../results/logFileWithoutDensity2.txt")
# plt.plot(data[:, 0] + data[:, 1])


# plt.xlabel("Time")
# plt.ylabel("Collected Resources")
# plt.title("Performance comparison SO-LOST vs DISTRIBUTED SO-LOST")
# plt.legend( ("DISTRIBUTED SO-LOST", "SO-LOST") )
# plt.show()