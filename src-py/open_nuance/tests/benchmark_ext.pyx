""" Test python calculation speed on a typical task

Extensions.
"""

import numpy as np
from cython.parallel import parallel, prange

cimport cython
cimport numpy as np
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

@cython.wraparound(False)
@cython.nonecheck(False)
@cython.boundscheck(False)
def get_R_cython_sp(py_p, py_q):
    py_R = np.empty((py_p.shape[0], py_q.shape[0]))

    cdef int nP = py_p.shape[0]
    cdef int nQ = py_q.shape[0]
    cdef double[:, :] p = py_p
    cdef double[:, :] q = py_q
    cdef double[:, :] R = py_R

    cdef int i, j
    cdef double rx, ry, rz

    with nogil:
        for i in xrange(nP):
            for j in xrange(nQ):
                rx = p[i, 0] - q[j, 0]
                ry = p[i, 1] - q[j, 1]
                rz = p[i, 2] - q[j, 2]

                R[i, j] = 1 / (1 + sqrt(rx * rx + ry * ry + rz * rz))

    return py_R

@cython.wraparound(False)
@cython.nonecheck(False)
@cython.boundscheck(False)
def get_R_cython_mp(py_p, py_q):
    py_R = np.empty((py_p.shape[0], py_q.shape[0]))

    cdef int nP = py_p.shape[0]
    cdef int nQ = py_q.shape[0]
    cdef double[:, :] p = py_p
    cdef double[:, :] q = py_q
    cdef double[:, :] R = py_R

    cdef int i, j
    cdef double rx, ry, rz

    with nogil:
        for i in prange(nP):
            for j in xrange(nQ):
                rx = p[i, 0] - q[j, 0]
                ry = p[i, 1] - q[j, 1]
                rz = p[i, 2] - q[j, 2]

                R[i, j] = 1 / (1 + sqrt(rx * rx + ry * ry + rz * rz))

    return py_R

@cython.wraparound(False)
@cython.nonecheck(False)
@cython.boundscheck(False)
def get_R_cython_mp_buffer(py_p, py_q):
    py_R = np.empty((py_p.shape[0], py_q.shape[0]))

    cdef int nP = py_p.shape[0]
    cdef int nQ = py_q.shape[0]
    cdef double[:, :] p = py_p
    cdef double[:, :] q = py_q
    cdef double[:, :] R = py_R

    cdef int i, j
    cdef double * r

    with nogil, parallel():
        r = <double *> malloc(3 * sizeof(double))

        for i in prange(nP):
            for j in xrange(nQ):
                    r[0] = p[i, 0] - q[j, 0]
                    r[1] = p[i, 1] - q[j, 1]
                    r[2] = p[i, 2] - q[j, 2]
                    R[i, j] = 1 / (1 + sqrt(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]))

        free(r)

    return R

# @cython.wraparound(False)
# @cython.nonecheck(False)
# @cython.boundscheck(False)
# def get_R_cython_mp_buffer(py_p, py_q):
#     """ WRONG DESIGN OF THE METHOD
#     Do not use
#         cdef double r[3]
#     buffer in parallel cython. Instead of use
#         cdef double * r
#
#         with nogil, parallel():
#             r = < double * > malloc(3 * sizeof(double))
#
#             for i in prange
#                 ...
#
#             free(r)
#     """
#     py_R = np.empty((py_p.shape[0], py_q.shape[0]))
#
#     cdef int nP = py_p.shape[0]
#     cdef int nQ = py_q.shape[0]
#     cdef double[:, :] p = py_p
#     cdef double[:, :] q = py_q
#     cdef double[:, :] R = py_R
#
#     cdef int i, j
#     cdef double r[3]
#
#     with nogil:
#         for i in prange(nP):
#             for j in xrange(nQ):
#                 r[0] = p[i, 0] - q[j, 0]
#                 r[1] = p[i, 1] - q[j, 1]
#                 r[2] = p[i, 2] - q[j, 2]
#                 R[i, j] = 1 / (1 + sqrt(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]))
#
#     return R