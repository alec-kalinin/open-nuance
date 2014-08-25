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

#include <cmath>
#include <string.h>

#include "VectorN.h"

using namespace std;

VectorN::VectorN() : m_nRows(0)
{
    m_v = new double[0];
}

VectorN::VectorN(int nRows) : m_nRows(nRows)
{
    m_v = new double[m_nRows];

    memset(m_v, 0, sizeof(double) * m_nRows);
}

VectorN::VectorN(const double * v, int nRows) : m_nRows(nRows)
{
    m_v = new double[m_nRows];

    memcpy(m_v, v, sizeof(double) * m_nRows);
}

VectorN::VectorN(const VectorN & src)
{
    m_nRows = src.m_nRows;
    m_v = new double[m_nRows];

    memcpy(m_v, src.m_v, sizeof(double) * m_nRows);
}

VectorN::~VectorN()
{
    delete[] m_v;
}

int VectorN::size() const
{
    return m_nRows;
}

double VectorN::norm() const
{
    return sqrt(operator*(*this, *this));
}


VectorN & VectorN::operator= (const VectorN & src)
{
    delete[] m_v;

    m_nRows = src.size();
    m_v = new double[m_nRows];
    memcpy(m_v, src.m_v, sizeof(double) * m_nRows);

    return (*this);
}

const VectorN operator+ (const VectorN & x, const VectorN & y)
{
    VectorN s(x.size());

    for (int i = 0; i < s.size(); i++)
        s[i] = x[i] + y[i];

    return s;
}

const VectorN operator+ (const VectorN & x, const double a)
{
    VectorN s(x.size());

    for (int i = 0; i < s.size(); i++)
        s[i] = x[i] + a;

    return s;
}

VectorN & VectorN::operator+= (const VectorN & y)
{
    for (int i = 0; i < size(); i++)
        (*this)[i] += y[i];

    return (*this);
}

const VectorN operator- (const VectorN & x, const VectorN & y)
{
    VectorN d(x.size());

    for (int i = 0; i < d.size(); i++)
        d[i] = x[i] - y[i];

    return d;
}

const VectorN operator- (const VectorN & x, const double a)
{
    VectorN d(x.size());

    for (int i = 0; i < x.size(); i++)
        d[i] = x[i] - a;

    return d;
}

const VectorN VectorN::operator-() const
{
    VectorN x(size());

    for (int i = 0; i < size(); i++) {
        x[i] = -(*this)[i];
    }

    return x;
}

double operator* (const VectorN & x, const VectorN & y)
{
    double s = 0;

    for (int i = 0; i < x.size(); i++)
        s += x[i] * y[i];

    return s;
}

const VectorN operator* (double alpha, const VectorN & x)
{
    VectorN y(x.size());

    for (int i = 0; i < x.size(); i++)
        y[i] = alpha * x[i];

    return y;
}

const VectorN operator/ (const VectorN & x, double alpha)
{
    VectorN y(x.size());

    for (int i = 0; i < x.size(); i++)
        y[i] = x[i] / alpha;

    return y;
}
