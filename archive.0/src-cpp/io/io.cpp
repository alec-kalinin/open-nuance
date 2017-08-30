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

void savetxt(const string & fname, const vector<Vector3D> & v)
{
    ofstream out;
    out.open(fname.c_str());

    //out << fixed << setprecision(6);
    out << fixed;
    for (int i = 0; i < v.size(); i++) {
        out << v[i].x << " ";
        out << v[i].y << " ";
        out << v[i].z << endl;
    }

    out.close();
}

void savetxt(const string & fname, const MatrixMN & A)
{
    ofstream out;
    out.open(fname.c_str());

    //out << fixed << setprecision(6);
    out << fixed;
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

void savebin(const std::string & fname, const vector<Vector3D> & v)
{
    ofstream out;
    out.open(fname.c_str(), ios::out | ios::binary);
    for (int i = 0; i < v.size(); i++) {
        out.write(reinterpret_cast<const char *>(&v[i].x), sizeof(double));
        out.write(reinterpret_cast<const char *>(&v[i].y), sizeof(double));
        out.write(reinterpret_cast<const char *>(&v[i].z), sizeof(double));
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

