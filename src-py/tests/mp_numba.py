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

""" Numba parallel calculations examples.
"""

import os, sys
sys.path.append(os.path.abspath('..'))

import numpy as np
from numba import jit, void, double, int64
from ctypes import pythonapi, c_void_p
import threading
from math import sqrt

import utils.utils as utils

@jit(double[:, :](double[:, :], double[:, :]))
def spnbGetR(p, q):
    nP = p.shape[0]
    nQ = q.shape[1]
    
    R = np.empty((nP, nQ))    
    
    for i in xrange(nP):
        for j in xrange(nQ):
            rx = p[i, 0] - q[0, j]
            ry = p[i, 1] - q[1, j]
            rz = p[i, 2] - q[2, j]

            R[i, j] = 1 / (1 + sqrt(rx * rx + ry * ry + rz * rz))
    return R
    
def makeWorker():
    savethread = pythonapi.PyEval_SaveThread
    savethread.argtypes = []
    savethread.restype = c_void_p

    restorethread = pythonapi.PyEval_RestoreThread
    restorethread.argtypes = [c_void_p]
    restorethread.restype = None

    def worker(p, q, R, job):
        threadstate = savethread()
    
        nQ = q.shape[1]
        for i in xrange(job[0], job[1]):
            for j in xrange(nQ):
                rx = p[i, 0] - q[0, j]
                ry = p[i, 1] - q[1, j]
                rz = p[i, 2] - q[2, j]

                R[i, j] = 1 / (1 + sqrt(rx * rx + ry * ry + rz * rz))
    
        restorethread(threadstate)
        
    signature = void(double[:, :], double[:, :], double[:, :], int64[:])
    worker_ext = jit(signature, nopython=True)(worker)
    
    return worker_ext

def mpnbGetR(p, q):
    nP, nQ = p.shape[0], q.shape[1]
    R = np.empty((nP, nQ))

    nCPU = utils.getCPUCount()
    jobs = utils.generateJobs(nP, nCPU) 
    worker_ext = makeWorker()

    threads = [threading.Thread(target=worker_ext, args=(p, q, R, job)) for job in jobs]
    for thread in threads:
        thread.start()
    for thread in threads:
        thread.join()

    return R
