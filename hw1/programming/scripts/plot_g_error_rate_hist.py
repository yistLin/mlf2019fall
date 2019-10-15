# -*- coding: utf-8 -*-

import sys
import numpy as np
import matplotlib.pyplot as plt

error_rates = []

with open(sys.argv[1]) as f:
    next(f)
    for line in f:
        error_rates.append(float(line.split(',')[0]))

avg_error_rate = sum(error_rates) / len(error_rates)

plt.hist(error_rates, bins=np.arange(9, 20, step=0.1), color='#993366', alpha=.75)

plt.xlabel('error rate')
plt.ylabel('frequency of the number')
plt.title(r'Histogram of error rate of $w_{POCKET}$ after 100 updates')
plt.text(15, 190, 'Average error rate is {:.4f}'.format(avg_error_rate))
plt.savefig(sys.argv[2])
