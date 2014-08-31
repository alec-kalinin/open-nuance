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


""" Test different ways of python parallel calculations.
"""

import timeit
import numpy as np
import numpy_mp as npmp
import cython_mp_ext as cymp

def main():
    N = 5000
    
    p = np.random.rand(N, 3)
    q = np.random.rand(3, N)
    
    print ("Python single process:")
    t0 = timeit.default_timer()
    #nomp.pspGetR(p, q)
    t1 = timeit.default_timer()
    print("time: {:.3f} s.\n".format(t1 - t0))    
    
    print ("NumPy single process:")
    t0 = timeit.default_timer()
    npspR = npmp.npspGetR(p, q)
    t1 = timeit.default_timer()
    print("time: {:.3f} s.\n".format(t1 - t0))

    print ("NumPy multiple processes:")
    t0 = timeit.default_timer()
    npmpR = npmp.npmpGetR(p, q)
    t1 = timeit.default_timer()
    print("time: {:.3f} s.".format(t1 - t0))
    print ("err: {:.3e}\n".format(np.linalg.norm(npspR - npmpR)))
        
    print ("Cython single process:")
    t0 = timeit.default_timer()
    cyspR = cymp.cyspGetR(p, q)
    t1 = timeit.default_timer()
    print("time: {:.3f} s.".format(t1 - t0))
    print ("err: {:.3e}\n".format(np.linalg.norm(npspR - cyspR)))

    print ("Cython multiple processes:")
    t0 = timeit.default_timer()
    cympR = cymp.cympGetR(p, q)
    t1 = timeit.default_timer()
    print("time: {:.3f} s.".format(t1 - t0))
    print ("err: {:.3e}\n".format(np.linalg.norm(npspR - cympR)))
    
if __name__ == '__main__':
    main()