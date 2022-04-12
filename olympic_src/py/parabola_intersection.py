# -*- coding: utf-8 -*-
"""
Created on Sun Oct 20 19:00:31 2019

@author: User
"""

import matplotlib
import matplotlib.pyplot as plt
import numpy as np
import math


# Data for plotting
a = 2
x = np.arange(-0.0, 5.0, 0.1)
f1 = (x-a)*(x-a)
f2 = np.sqrt(x) + a

fig, ax = plt.subplots()
ax.plot(x, f1)
ax.plot(x, f2)

ax.set(xlabel='x', ylabel='y',
       title='About as simple as it gets, folks')
ax.grid()

fig.savefig("test.png")
plt.show()

def integrate(a):
    dx=0.1
    X=np.arange(0.0, 4.0, dx)
    s=0
    for x in X:
        ff1 = (x-a)*(x-a)
        ff2 = np.sqrt(x) + a
        if ff2 > ff1:
            s = s + (ff2 - ff1)*dx
    return s

print("integral of f2-f1 = ", integrate(a))
            
    