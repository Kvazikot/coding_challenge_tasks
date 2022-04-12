# -*- coding: utf-8 -*-
"""
Created on Sun Oct 20 17:06:54 2019
   http://acm.timus.ru/problem.aspx?space=1&num=2105
@author: User
"""
L=10
T=10
Va=2
Vb=1
delay_times=[[1,1,1],[1,2,2],[2,2,1]]
t1 = 0
t2 = 0
t = 0
meet_counter = 0
while t < T:
    
    s1 = Va * t1
    s2 = Vb * t2
    if s1 > L:
        s1 = s1 - L
    if s2 > L:
        s2 = s2 - L
    print('t1=',t1)
    print('t2=',t2)
    print('t=',t)
    if s1 == s2:
        meet_counter = meet_counter + 1
    t1 = t1 + 1
    t2 = t2 + 1
    t = t + 1
    for i in range(len(delay_times)):
        if delay_times[i][0]==1:            
            if (t >= delay_times[i][1]) and (delay_times[i][1]+delay_times[i][2]) >= t:
                t1 = t1 - 1
                print('delay t1')
        if delay_times[i][0]==2:
            if  (t >= delay_times[i][1]) and (delay_times[i][1]+delay_times[i][2]) >= t:
                t2 = t2 - 1
                print('delay t2')


print('meet counts ', meet_counter)
    