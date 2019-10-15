# -*- coding: utf-8 -*-

import sys
import matplotlib.pyplot as plt

update_cnts = []

with open(sys.argv[1]) as f:
    next(f)
    for line in f:
        update_cnts.append(int(line.split(',')[0]))

avg_update_cnt = sum(update_cnts) / len(update_cnts)

plt.hist(update_cnts, bins=range(100), color='#336699', alpha=.75)
plt.yticks(range(0, 150, 10))

plt.xlabel('# of updates')
plt.ylabel('frequency of the number')
plt.title('Histogram of number of updates before PLA halts')
plt.text(50, 130, 'Average update count is {:.4f}'.format(avg_update_cnt))
plt.savefig(sys.argv[2])
