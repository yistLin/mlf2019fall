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
print("avg_error_rate = {:.2f}%".format(avg_error_rate))

plt.hist(error_rates, bins=np.arange(10, 75, step=0.1), color='#339966', alpha=.75)

plt.xlabel('error rate (%)')
plt.ylabel('frequency of the number')
plt.title(r'Histogram of error rate of $w_{100}$ after 100 updates')
plt.text(44, 15.5, 'Average error rate is {:.4f}%'.format(avg_error_rate))
plt.savefig(sys.argv[2])
