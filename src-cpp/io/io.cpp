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

    out << fixed << setprecision(6);
    for (int i = 0; i < a.size(); i++) {
        out << a[i].x << " ";
        out << a[i].y << " ";
        out << a[i].z << endl;
    }

    out.close();
}

void savetxt(const string & fname, const MatrixMN & A)
{
    ofstream out;
    out.open(fname.c_str());

    out << fixed << setprecision(6);
    for (int i = 0; i < A.m_nRows; i++) {
        for (int j = 0; j < A.m_nCols; j++) {
            out << A(i, j);
            if (j < A.m_nRows - 1)
                out << " ";
        }
        out << endl;
    }

    out.close();
}

void savebin(const std::string & fname, const MatrixMN & A)
{
    ofstream out;
    out.open(fname.c_str(), ios::out | ios::binary);
    out.write((char *)A.m_v, A.m_nRows * A.m_nCols * sizeof(double));
    out.close();
}

