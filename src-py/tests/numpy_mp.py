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

""" Test numpy parallel accelerated calculations.
"""

import os, sys
sys.path.append(os.path.abspath('..'))

import ctypes
import numpy as np
import multiprocessing as mp
from math import sqrt

import mp_share
import utils.utils as utils


def pyspGetR(p, q):
    R = np.empty((p.shape[0], q.shape[1]))    
    
    nP = p.shape[0]
    nQ = q.shape[1]
    for i in xrange(nP):
        for j in xrange(nQ):
            rx = p[i, 0] - q[0, j]
            ry = p[i, 1] - q[1, j]
            rz = p[i, 2] - q[2, j]

            R[i, j] = 1 / (1 + sqrt(rx * rx + ry * ry + rz * rz))
    return R

def npspGetR(p, q):    
    Rx = p[:, 0:1] - q[0:1]
    Ry = p[:, 1:2] - q[1:2]
    Rz = p[:, 2:3] - q[2:3]
         
    R = 1 / (1 + np.sqrt(Rx * Rx + Ry * Ry + Rz * Rz))
       
    return R
        
def mp_init(sh_p, sh_q, sh_R):
    mp_share.p = sh_p
    mp_share.q = sh_q
    mp_share.R = sh_R

def npmpGetR_worker(job):
    start, stop = job
    p = np.reshape(np.frombuffer(mp_share.p), (-1, 3))
    q = np.reshape(np.frombuffer(mp_share.q), (3, -1))
    R = np.reshape(np.frombuffer(mp_share.R), (p.shape[0], q.shape[1]))

    Rx = p[start:stop, 0:1] - q[0:1]
    Ry = p[start:stop, 1:2] - q[1:2]
    Rz = p[start:stop, 2:3] - q[2:3]

    R[start:stop, :] = 1 / (1 + np.sqrt(Rx * Rx + Ry * Ry + Rz * Rz))
        
def npmpGetR(p, q):
    nP, nQ = p.shape[0], q.shape[1]    
    
    sh_p = mp.RawArray(ctypes.c_double, p.ravel())
    sh_q = mp.RawArray(ctypes.c_double, q.ravel())
    sh_R = mp.RawArray(ctypes.c_double, nP * nQ)
    
    nCPU = 4#utils.getCPUCount()
    jobs = utils.generateJobs(nP, nCPU)
    
    pool = mp.Pool(processes=nCPU, initializer=mp_init, initargs=(sh_p, sh_q, sh_R))
    pool.map(npmpGetR_worker, jobs, chunksize=1)

    R = np.reshape(np.frombuffer(sh_R), (nP, nQ))
    return R