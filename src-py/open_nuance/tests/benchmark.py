""" Test python calculation speed on a typical task
"""

import time

import math
import numpy as np
import numba as nb
import scipy.spatial.distance as spd

from open_nuance.tests.benchmark_ext import get_R_cython_sp, get_R_cython_mp

def get_R(p, q):
    R = np.empty((p.shape[0], q.shape[0]))

    for i in range(p.shape[0]):
        for j in range(q.shape[0]):
            rx = p[i, 0] - q[j, 0]
            ry = p[i, 1] - q[j, 1]
            rz = p[i, 2] - q[j, 2]
            R[i, j] = 1 / (1 + math.sqrt(rx * rx + ry * ry + rz * rz))

    return R

def get_R_numpy(p, q):
    Rx = p[:, 0:1] - q[0:1]
    Ry = p[:, 1:2] - q[1:2]
    Rz = p[:, 2:3] - q[2:3]

    R = 1 / (1 + np.sqrt(Rx * Rx + Ry * Ry + Rz * Rz))

    return R


def get_R_scipy(p, q):
    D = spd.cdist(p, q)
    R = 1 / (1 + D)
    return R


@nb.jit(nb.float64[:, :](nb.float64[:, :], nb.float64[:, :]), nopython=True)
def get_R_numba_sp(p, q):
    R = np.empty((p.shape[0], q.shape[0]))

    for i in range(p.shape[0]):
        for j in range(q.shape[0]):
            rx = p[i, 0] - q[j, 0]
            ry = p[i, 1] - q[j, 1]
            rz = p[i, 2] - q[j, 2]
            R[i, j] = 1 / (1 + math.sqrt(rx * rx + ry * ry + rz * rz))

    return R


@nb.jit(nb.float64[:, :](nb.float64[:, :], nb.float64[:, :]), nopython=True, parallel=True)
def get_R_numba_mp(p, q):
    R = np.empty((p.shape[0], q.shape[0]))

    for i in nb.prange(p.shape[0]):
        for j in range(q.shape[0]):
            rx = p[i, 0] - q[j, 0]
            ry = p[i, 1] - q[j, 1]
            rz = p[i, 2] - q[j, 2]

            R[i, j] = 1 / (1 + math.sqrt(rx * rx + ry * ry + rz * rz))

    return R


def main():
    N = 5000

    p = np.random.rand(N, 3)
    q = np.random.rand(N, 3)

    print('Python:')
    t0 = time.time()
    R0 = get_R(p, q)
    t1 = time.time()
    print('  time: {:.3f} s.\n'.format(t1 - t0))

    print('NumPy:')
    t0 = time.time()
    R = get_R_numpy(p, q.T)
    t1 = time.time()
    print('  valid:', np.array_equal(R0, R))
    print('  time: {:.3f} s.\n'.format(t1 - t0))

    print('SciPy:')
    t0 = time.time()
    R = get_R_scipy(p, q)
    t1 = time.time()
    print('  valid:', np.array_equal(R0, R))
    print('  time: {:.3f} s.\n'.format(t1 - t0))

    print('Cython:')
    t0 = time.time()
    R = get_R_cython_sp(p, q)
    t1 = time.time()
    print('  valid:', np.array_equal(R0, R))
    print('  time: {:.3f} s.\n'.format(t1 - t0))

    print('Cython Parallel:')
    t0 = time.time()
    R = get_R_cython_mp(p, q)
    t1 = time.time()
    print('  valid:', np.array_equal(R0, R))
    print('  time: {:.3f} s.\n'.format(t1 - t0))

    print('Numba:')
    t0 = time.time()
    R = get_R_numba_sp(p, q)
    t1 = time.time()
    print('  valid:', np.array_equal(R0, R))
    print('  time: {:.3f} s.\n'.format(t1 - t0))

    print('Numba Parallel:')
    t0 = time.time()
    R = get_R_numba_mp(p, q)
    t1 = time.time()
    print('  valid:', np.array_equal(R0, R))
    print('  time: {:.3f} s.\n'.format(t1 - t0))

if __name__ == '__main__':
    main()