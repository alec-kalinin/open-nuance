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

import numpy as np

def main():
    N = 5000
    
    p = np.random.rand(N, 3)
    q = np.random.rand(3, N)

    
if __name__ == '__main__':
    main()