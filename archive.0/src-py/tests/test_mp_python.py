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


""" Test parallel calculations with pure python.
"""


import numpy as np
import mp_numpy as mpnp
import timeit

def main():
    # load data
    p = np.fromfile("../../results/tests/p.bin").reshape(-1, 3)
    q = np.fromfile("../../results/tests/q.bin").reshape(-1, 3).T
    
    M, N  = p.shape[0], q.shape[1]
    R = np.fromfile("../../results/tests/R.bin").reshape(M, N)
    
    print("Problem dimensions:")
    print("R({:d}, {:d})\n".format(M, N))

    # run tests
    print("Python single process:")
    t0 = timeit.default_timer()
    sppyR = mpnp.sppyGetR(p, q)
    t1 = timeit.default_timer()
    print("time: {:.3f} s.".format(t1 - t0))
    print("err: {:.3e}\n".format(np.linalg.norm(R - sppyR)))

    print("NumPy single process:")
    t0 = timeit.default_timer()
    spnpR = mpnp.spnpGetR(p, q)
    t1 = timeit.default_timer()
    print("time: {:.3f} s.".format(t1 - t0))
    print("err: {:.3e}\n".format(np.linalg.norm(R - spnpR)))

    print ("NumPy multiple processes:")
    t0 = timeit.default_timer()
    mpnpR = mpnp.mpnpGetR(p, q)
    t1 = timeit.default_timer()
    print("time: {:.3f} s.".format(t1 - t0))
    print("err: {:.3e}\n".format(np.linalg.norm(R - mpnpR)))
    
if __name__ == '__main__':
    main()