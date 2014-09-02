#!/usr/bin/env python

# Open NUANCE:
#     Numerical Algorithms for Noninvasive Cardiac Electrophysiology
#
# Authors:
#     Alexander V. Kalinin <alec.kalinin@gmail.com>, 2012 -- 2014
#
# License:
#     Redistribution and use of the source code with or without modification
#     are permitted for any scientific, research and educational purposes.

""" Utility functions.
"""

import numpy as np
import multiprocessing

def generateJobs(nItems, nCPU):
    q = nItems / nCPU
    r = nItems % nCPU
 
    jobs = []
    firstRow = 0
    for i in range(nCPU):
        rowsInJob = q
        if (r > 0):
            rowsInJob += 1
            r -= 1
        jobs.append([firstRow, firstRow + rowsInJob])
        firstRow += rowsInJob
        
    return np.array(jobs)
    
def getCPUCount():
    return multiprocessing.cpu_count()