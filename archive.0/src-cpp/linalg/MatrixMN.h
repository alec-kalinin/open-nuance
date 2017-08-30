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

#ifndef MATRIXMN_H_
#define MATRIXMN_H_

#include <string>

#include "VectorN.h"

/*!
 * Linear algebra dense matrix of size MxN. Elements are linear in memory and
 * aligned in row major order.
 */
class MatrixMN
{
// Methods
public:
    MatrixMN();
    MatrixMN(int nRows, int nCols);
    MatrixMN(const double * v, int nRows, int nCols);
    MatrixMN(const MatrixMN & src);
   ~MatrixMN();

    //! Get matrix norm.
    /*! Possible values of normName:
         1   : largest column sum
         inf : larges row sum
     */
    double norm(std::string normName) const;
    MatrixMN transpose() const;

// Operators
public:
    MatrixMN & operator=  (const MatrixMN & src);

    //! Access to matrix elements.
    double &                operator() (int i, int j);
    double                  operator() (int i, int j) const;

    //! Basic linear algebra operation.
    friend const MatrixMN   operator+  (const MatrixMN & A, const MatrixMN & B);
    MatrixMN &              operator+= (const MatrixMN & B);
    friend const MatrixMN   operator-  (const MatrixMN & A, const MatrixMN & B);
    const MatrixMN          operator-  () const;
    friend const VectorN    operator*  (const MatrixMN & A, const VectorN & x);
    friend const MatrixMN   operator*  (double alpha, const MatrixMN & A);

// Data members
public:
    int m_nRows;
    int m_nCols;

    double *m_v;
};

inline double & MatrixMN::operator() (int i, int j)
{
    return m_v[i * m_nCols + j];
}

inline double MatrixMN::operator() (int i, int j) const
{
    return m_v[i * m_nCols + j];
}

#endif /*MATRIXMN_H_*/
