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

import numpy as np
import matplotlib.pyplot as plt


def draw_stats(lbls, values):
    N = len(values)
    bar_height = 0.4
    bar_spacing = 0.04
    bar_distance = bar_height + bar_spacing
    
    positions = 2 * bar_spacing + (N - 1) * bar_distance - \
                np.arange(0.0, N * bar_distance, bar_distance)

    fig = plt.figure(figsize=(8, 3), facecolor=(1.0, 1.0, 1.0), tight_layout=True)
    ax = fig.add_subplot(111)
    ax.spines["top"].set_visible(False)
    ax.spines["left"].set_visible(False) 
    ax.spines["right"].set_visible(False)
    
    ax.get_xaxis().tick_bottom()     
 
    ax.set_ylim([0, (N + 1) * bar_height])
    ax.get_yaxis().tick_left()
    ax.set_yticks(positions + bar_height / 2)
    ax.set_yticklabels(lbls) 
    
    ax.barh(positions, values, height=bar_height, color="#3F5D7D")

    ax.set_title("Results of multiple processes calculations")
                      
    for i in range(N):
        ax.text(values[i] / 2, positions[i] + bar_height / 2, str(values[i]),
                ha='center', va='center', color='w')

    plt.show()


def main():
    lbls = ['C++', 'Cython', 'Numba', 'NumPy']
    sp = [224, 255, 359, 973]
    mp = [65, 75, 180, 795]
    draw_stats(lbls, mp)

if __name__ == '__main__':
    main()
