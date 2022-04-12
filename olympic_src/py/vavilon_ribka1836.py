# -*- coding: utf-8 -*-
"""
Created on Thu Oct 03 06:29:38 2019

@author: User
# http://acm.timus.ru/problem.aspx?space=1&num=1836
"""
import numpy as np
from numpy import dot
import random
import math

max_iters=60000

def getZfromPlane(N, x, y, Origin):
    return (-N[0]*(x-Origin[0]) - N[1] * (y-Origin[1]))/N[2] + Origin[2];

def main():
    A = np.array([0, 0,2],float)
    B = np.array([10,0,3],float)
    C = np.array([10,10,4],float)
    D = np.array([0,10,3],float)
    # normal vector    
    N = np.cross((D-A),(B-A))
    
    #monte carlo method
    iters=0;
    n_under_plane=0;
    RND=np.random.random_sample((max_iters*3,))
    
    while iters < max_iters-2:
        X = 10. * RND[iters];
        Y = 10. * RND[iters+1];
        Z = 10. * RND[iters+2];
        z = getZfromPlane(N, X, Y, B);
        if Z < z:
            n_under_plane+=1;
        iters+=1;
    
    V = math.ceil(float(10*10*10) * float(n_under_plane) / max_iters);
    print("estimated volume is ", V)

main()
