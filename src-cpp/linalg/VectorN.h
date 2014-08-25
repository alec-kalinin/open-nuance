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

#ifndef VECTORN_H_
#define VECTORN_H_

/*!
 * Linear algebra column vector of size N.
 */
class VectorN
{
// Methods
public:
	VectorN();
    VectorN(int nRows);
    VectorN(const double * v, int nRows);
    VectorN(const VectorN & src);
   ~VectorN();

    int size() const;
    //! L_2 Euclidian norm.
    double norm() const;

// Operators
public:
    VectorN &              operator=  (const VectorN & src);

    //! Access to vector elements.
    double &               operator[] (int i);
    double                 operator[] (int i) const;
    double &               operator() (int i);
    double                 operator() (int i) const;

    //! Basic linear algebra operation.
    friend const VectorN   operator+  (const VectorN & x, const VectorN & y);
    friend const VectorN   operator+  (const VectorN & x, const double alpha);
    VectorN &              operator+= (const VectorN & y);
    friend const VectorN   operator-  (const VectorN & x, const VectorN & y);
    friend const VectorN   operator-  (const VectorN & x, const double a);
    const VectorN          operator-  () const;
    //! Dot product.
    friend       double    operator*  (const VectorN & x, const VectorN & y);
    friend const VectorN   operator*  (double alpha, const VectorN & x);
    friend const VectorN   operator/  (const VectorN & x, double alpha);

// Data members
public:
    int m_nRows;

    double *m_v;
};

inline double & VectorN::operator[] (int i)
{
    return m_v[i];
}

inline double VectorN::operator[] (int i) const
{
    return m_v[i];
}

inline double & VectorN::operator() (int i)
{
    return m_v[i];
}

inline double VectorN::operator() (int i) const
{
    return m_v[i];
}

#endif /*VECTORN_H_*/
