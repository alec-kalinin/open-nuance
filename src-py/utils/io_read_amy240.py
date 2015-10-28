""" Read AMYCARD amplifier ecg binary exports (*.240 file format)
"""

import datetime
import numpy as np
import matplotlib.pyplot as plt


def gen_names_v1():
    """ Generate channels names for version 1 amplifier file
    """

    names = 256 * ['']

    names[0:6] = ['I', 'II', 'III', 'AVR', 'AVL', 'AVF']
    names[6:12] = ['V1', 'V2', 'V3', 'V4', 'V5', 'V6']

    cols = 'ABCDEFGHIJKLMNO'
    rows = range(1, 17)
    for i, col in enumerate(cols):
        for j, row in enumerate(rows):
            names[16+16*i+j] = '{}{}'.format(col, row)

    return np.array(names).reshape(-1, 1)


def gen_names_v2():
    """ Generate channels names for version 2 amplifier file
    """

    names = 256 * ['']

    names[0:6] = ['I', 'II', 'III', 'AVR', 'AVL', 'AVF']
    names[6:12] = ['V1', 'V2', 'V3', 'V4', 'V5', 'V6']

    devs = ['I', 'II', 'III', 'IV']
    cols = 'ABCDEFG'
    rows = range(1, 9)
    for i, dev in enumerate(devs):
        for j, col in enumerate(cols):
            for k, row in enumerate(rows):
                names[16+56*i+8*j+k] = '{}{}{}'.format(dev, col, row)

    return np.array(names).reshape(-1, 1)


def plot_channel(egs, names, name):
    # choose channel by name
    idx = np.flatnonzero(names == name)[0]

    # draw figure
    fig = plt.figure(figsize=(12.0, 6.0), facecolor=(1.0, 1.0, 1.0), tight_layout=True)
    fig.suptitle(name)
    ax = fig.add_subplot(111)
    ax.plot(egs[idx])
#    ax.set_xlim(x_lim)
#    ax.set_ylim(y_lim)
    plt.show()


def main():
    ecg_filename = 'D:\\WST\\data\\Tests\\export-1.240'

    # read data
    print('Input file:')
    print('    {}'.format(ecg_filename))

    ht = np.dtype([('ht', np.int8, 16), ('hs', np.int32), ('rus', np.int32),
                   ('rate', np.int32), ('lsb', np.int32), ('rt', np.int16, 8),
                   ('st', np.int32), ('uu1', np.int32), ('pn', np.int16, 20),
                   ('uu2', np.int8, 128), ('sn', np.int8, 32)])
    et = np.dtype(np.int16)

    f = open(ecg_filename, 'rb')
    header = np.fromfile(f, dtype=ht, count=1)
    ecgs = np.fromfile(f, dtype=et)
    f.close()

    # process data
    rate = header['rate'][0]
    lsb = header['lsb'][0]
    sn = header['sn'].view('c').tostring()
    if header['uu2'][0, -1] == 1:
        version = 'v2'
        names = gen_names_v2()
    else:
        version = 'v1'
        names = gen_names_v1()
    ecgs = np.reshape(ecgs, (-1, 256)).T
    ecgs = ecgs.astype('float') * 1000.0 / lsb

    print ('Data:')
    print ('    serial number: {}'.format(sn))
    print ('    version: {}'.format(version))
    print ('    rate: {} Hz'.format(rate))
    print ('    fragment length: {}'.format(datetime.timedelta(seconds=ecgs.shape[1]/rate)))

    # plot channel I
    plot_channel(ecgs, names, 'I')

if __name__ == '__main__':
    main()
