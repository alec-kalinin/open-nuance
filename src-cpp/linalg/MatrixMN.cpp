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

#include <string.h>

#include "VectorN.h"
#include "MatrixMN.h"

using namespace std;

MatrixMN::MatrixMN() :
    m_nRows(0), m_nCols(0)
{
    m_v = new double[0];
}

MatrixMN::MatrixMN(int nRows, int nCols) :
    m_nRows(nRows), m_nCols(nCols)
{
    m_v = new double[m_nRows * m_nCols];

    memset(m_v, 0, sizeof(double) * m_nRows * m_nCols);
}

MatrixMN::MatrixMN(const double * v, int nRows, int nCols)
    : m_nRows(nRows), m_nCols(nCols)
{
    m_v = new double[m_nRows * m_nCols];

    memcpy(m_v, v, sizeof(double) * m_nRows * m_nCols);
}

MatrixMN::MatrixMN(const MatrixMN & src)
    : m_nRows(src.m_nRows), m_nCols(src.m_nCols)
{
    m_v = new double[m_nRows * m_nCols];

    memcpy(m_v, src.m_v, sizeof(double) * m_nRows * m_nCols);
}

MatrixMN::~MatrixMN()
{
    delete[] m_v;
}

double MatrixMN::norm(string normName) const
{
    double norm = 0.0;

    if (normName == "1") {
        double max_sum = 0.0, sum;
        for (int i = 0; i < m_nCols; i++) {
            sum = 0.0;
            for (int j = 0; j < m_nRows; j++)
                sum += (*this)(j, i);
            if (sum > max_sum)
                max_sum = sum;
        }

        norm = max_sum;
    }

    if (normName == "inf") {
        double max_sum = 0.0, sum;
        for (int i = 0; i < m_nRows; i++) {
            sum = 0.0;
            for (int j = 0; j < m_nCols; j++)
                sum += (*this)(i, j);
            if (sum > max_sum)
                max_sum = sum;
        }

        norm = max_sum;
    }

    return norm;
}

MatrixMN MatrixMN::transpose() const
{
    MatrixMN T(m_nCols, m_nRows);

    for (int i = 0; i < m_nRows; i++) {
        for (int j = 0; j < m_nCols; j++)  {
            T(j, i) = (*this)(i, j);
        }
    }

    return T;
}

MatrixMN & MatrixMN::operator=(const MatrixMN & src)
{
    delete[] m_v;

    m_nRows = src.m_nRows;
    m_nCols = src.m_nCols;
    m_v = new double[m_nRows * m_nCols];
    memcpy(m_v, src.m_v, sizeof(double) * m_nRows * m_nCols);

    return (*this);
}

const MatrixMN operator+ (const MatrixMN & A, const MatrixMN & B)
{
    MatrixMN C(A.m_nRows, A.m_nCols);

    for (int i = 0; i < C.m_nRows * C.m_nCols; i++) {
        C.m_v[i] = A.m_v[i] + B.m_v[i];
    }

    return C;
}

MatrixMN & MatrixMN::operator+= (const MatrixMN & B)
{
    for (int i = 0; i < m_nRows * m_nCols; i++) {
            m_v[i] += B.m_v[i];
    }

    return (*this);
}

const MatrixMN operator- (const MatrixMN & A, const MatrixMN & B)
{
    MatrixMN C(A.m_nRows, A.m_nCols);

    for (int i = 0; i < C.m_nRows * C.m_nCols; i++) {
        C.m_v[i] = A.m_v[i] - B.m_v[i];
    }

    return C;
}

const MatrixMN MatrixMN::operator-() const
{
    MatrixMN A(m_nRows, m_nCols);

    for (int i = 0; i < m_nRows * m_nCols; i++) {
        A.m_v[i] = -m_v[i];
    }

    return A;
}

const VectorN operator*(const MatrixMN & A, const VectorN & x)
{
    VectorN y(A.m_nRows);

    for (int i = 0; i < A.m_nRows; i++) {
        double sum = 0.0;
        for (int j = 0; j < A.m_nCols; j++)
            sum += A(i, j) * x[j];
        y[i] = sum;
    }

    return y;
}

const MatrixMN operator* (double alpha, const MatrixMN & A)
{
    MatrixMN C(A.m_nRows, A.m_nCols);

    for (int i = 0; i < C.m_nRows * C.m_nCols; i++) {
        C.m_v[i] = alpha * A.m_v[i];
    }

    return C;
}
