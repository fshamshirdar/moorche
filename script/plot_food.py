#!/usr/bin/env python
import sys
import numpy as np
import matplotlib.pyplot as plt

# data = np.genfromtxt(sys.argv[1])

# data = np.genfromtxt("../results/grid.txt")
# plt.matshow(data)
# plt.xlabel('X-axis')
# plt.ylabel('Y-axis')
# plt.title('Grid Visualization')

#plt.xticks(range(data.shape[0]), (np.asarray(range(data.shape[0])) - data.shape[0] / 2)*.25 )
#plt.yticks(range(data.shape[1]), (np.asarray(range(data.shape[1])) - data.shape[1] / 2)*.25 )

# plt.show()

# exit(0)

colors = [
	"red",
	"orange",
	"magenta"
]

data = np.genfromtxt(sys.argv[1])
try:
	no_of_sources = len(data[0])
except:
	no_of_sources = 1

fig = plt.figure()
if no_of_sources == 1:
	x = np.linspace(0, 30, len(data[:]))
	plt.plot(x, data[:], color=colors[0], linewidth=3)	
else:
	x = np.linspace(0, 30, len(data[:, 0]))
	for i in range(no_of_sources):
		plt.plot(x, data[:, i], color=colors[i], linewidth=3)

#plt.plot(data[:, 1], color="orange")



plt.xlabel("Time (seconds)")
plt.ylabel("Collected Resources")
plt.title("Collected Resources for " + sys.argv[2])

legends = []
for i in range(no_of_sources):
	legends.append("Source " + str(i+1))
plt.legend( tuple(legends) )
fig.savefig(sys.argv[2])


# data = np.genfromtxt("../results/logFileWithDensity2.txt")
# plt.plot(data[:, 0] + data[:, 1])


# data = np.genfromtxt("../results/logFileWithoutDensity2.txt")
# plt.plot(data[:, 0] + data[:, 1])


# plt.xlabel("Time")
# plt.ylabel("Collected Resources")
# plt.title("Performance comparison SO-LOST vs DISTRIBUTED SO-LOST")
# plt.legend( ("DISTRIBUTED SO-LOST", "SO-LOST") )
# plt.show()