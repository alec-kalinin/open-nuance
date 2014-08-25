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
#


""" Test cython opemnp parallel accelerated calculations.
"""

import time
import numpy as np
import cython_omp_ext as compx

def main():
    N = 5000
    
    p = np.random.rand(N, 3)
    q = np.random.rand(3, N)
    
    print ("NumPy single process:")
    t0 = time.time()
    compx.nstGetR(p, q)
    t1 = time.time()
    print("time: {:.3f} s.\n".format(t1 - t0))    

    print ("Cython single process:")
    t0 = time.time()
    compx.cstGetR(p, q)
    t1 = time.time()
    print("time: {:.3f} s.\n".format(t1 - t0))

    print ("Cython multiple process:")
    t0 = time.time()
    compx.cmtGetR(p, q)
    t1 = time.time()
    print("time: {:.3f} s.\n".format(t1 - t0))

    
if __name__ == '__main__':
    main()