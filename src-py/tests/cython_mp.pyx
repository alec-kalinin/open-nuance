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

""" Test cython opemnp parallel accelerated calculations.
"""

import os, sys
sys.path.append(os.path.abspath('..'))

import time

cimport cython

import numpy as np
cimport numpy as np

from cython.parallel import parallel, prange
cimport openmp

from libc.math cimport sqrt
from libc.stdlib cimport abort, malloc, free

def getThreadsNum():
    cdef int i
    cdef int num_threads
    
    with nogil, parallel():
        for i in prange(1):
            num_threads = openmp.omp_get_num_threads()
    return num_threads
         
@cython.boundscheck(False)
@cython.wraparound(False)
def cyspGetR(pp, pq):
    pR = np.empty((pp.shape[0], pq.shape[1]))    
    
    cdef int i, j, k
    cdef int nP = pp.shape[0]
    cdef int nQ = pq.shape[1]
    cdef double[:, :] p = pp
    cdef double[:, :] q = pq
    cdef double[:, :] R = pR
    cdef double rx, ry, rz
    
    with nogil:
        for i in xrange(nP):
            for j in xrange(nQ):
                rx = p[i, 0] - q[0, j]
                ry = p[i, 1] - q[1, j]
                rz = p[i, 2] - q[2, j]

                R[i, j] = 1 / (1 + sqrt(rx * rx + ry * ry + rz * rz))
    return R

@cython.boundscheck(False)
@cython.wraparound(False)
def cympGetR(pp, pq):
    pR = np.empty((pp.shape[0], pq.shape[1]))    
    
    cdef int i, j, k
    cdef int nP = pp.shape[0]
    cdef int nQ = pq.shape[1]
    cdef double[:, :] p = pp
    cdef double[:, :] q = pq
    cdef double[:, :] R = pR
    cdef double rx, ry, rz
    
    with nogil, parallel():
        for i in prange(nP, schedule='guided'):
            for j in xrange(nQ):
                rx = p[i, 0] - q[0, j]
                ry = p[i, 1] - q[1, j]
                rz = p[i, 2] - q[2, j]
                
                R[i, j] = 1 / (1 + sqrt(rx * rx + ry * ry + rz * rz))
                
    return R
