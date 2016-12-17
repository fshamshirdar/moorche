#!/usr/bin/env python

import sys
import numpy as np
import matplotlib.pyplot as plt

ax = [None, None, None]
f, (ax[0], ax[1], ax[2]) = plt.subplots(3, sharex=True, sharey=True)
# ax[0].set_title('Sharing x per column, y per row')

for num_sources in range(1, 4):
	files = ["/explicit.txt", "/embodied.txt", "/so-lost.txt"]

	for file_idx in range(len(files)):
		data = np.genfromtxt(
			"../results/results/" + str(num_sources ) + files[file_idx],
			delimiter=","
		)

		x = data[:, 0]
		y = []
		error = [[], []]
		for i in range(len(data)):
			row = data[i, 1:]
			y.append(np.median(row))
			error[0].append(y[-1] - min(row))
			error[1].append(max(row) - y[-1])
		
		# print y
		# print error

		# ax[file_idx].errorbar(x, y, yerr=error)
		ax[num_sources-1].errorbar(x, y, yerr=error)



		ax[num_sources-1].set_xlabel("Population Size")
		ax[num_sources-1].set_ylabel("Collected Resources")
		ax[num_sources-1].set_title("Number of sources: " + str(num_sources))
		#ax[num_sources-1].legend(["Explicit Allocation", "Embodied Approach", "SO-LOST"])
		# ax[num_sources-1].title("Number of sources: " + str(num_sources))
	

ax[0].legend(["Explicit Allocation", "Embodied Approach", "SO-LOST"])

#fig.legend((l1, l2), ("Explicit Allocation", "Embodied Approach", "SO-LOST"), 'upper left')
# Fine-tune figure; make subplots close to each other and hide x ticks for
# all but bottom plot.
f.subplots_adjust(hspace=0)
plt.setp([a.get_xticklabels() for a in f.axes[:-1]], visible=False)

plt.xticks(np.arange(0, 36, 4.))

#plt.figlegend( ['rs-', 'yd+', 'bs-'], ["Explicit Allocation", "Embodied Approach", "SO-LOST"], 'upper left')
plt.show()