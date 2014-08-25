/******************************************************************************
 * Open NUANCE:                                                               *
 *     NUmerical Algorithms for Noninvasive Cardiac Electrophysiology         *
 *                                                                            *
 * Authors:                                                                   *
 *     Alexander V. Kalinin <alec.kalinin@gmail.com>, 2012 -- 2014            *
 *                                                                            *
 * License:                                                                   *
 *     Redistribution and use of the source code with or without modification *
 *     are permitted for any scientific, research and educational purposes.   *
 ******************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>

#include "io.h"
#include "../linalg/Vector3D.h"

using namespace std;

void savetxt(const string & fname, const vector<Vector3D> & a)
{
    ofstream out;
    out.open(fname.c_str());

    out << setprecision(4);
    for (int i = 0; i < a.size(); i++) {
        out << a[i].x << endl;
    }

    out.close();
}

