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

#ifndef VECTOR3D_H
#define VECTOR3D_H

/*!
 * Coordinate column free vector in 3D Euclidian space.
 */
class Vector3D
{
// Methods
public:
    Vector3D();
    Vector3D(double x, double y, double z);
   ~Vector3D();

    //! L_2 Euclidian norm.
    double norm() const;

// Operators
public:
    Vector3D &             operator=  (const Vector3D & src);

    //! Access to vector elements.
    double &               operator[] (int i);
    double                 operator[] (int i) const;

    //! Basic 3D space coordinate operations.
    friend const Vector3D operator+  (const Vector3D & a, const Vector3D & b);
    Vector3D &            operator+= (const Vector3D & b);
    friend const Vector3D operator-  (const Vector3D & a, const Vector3D & b);
    const Vector3D        operator-  () const;
    //! Dot product.
    friend double         operator*  (const Vector3D & a, const Vector3D & b);
    friend const Vector3D operator*  (double alpha, const Vector3D & a);
    //! Cross product.
    friend const Vector3D operator^  (const Vector3D & a, const Vector3D & b);
    friend const Vector3D operator/  (const Vector3D & a, double alpha);

// Data members
public:
    double x;
    double y;
    double z;
};

inline double & Vector3D::operator[] (int i)
{
    if (i == 0)
        return x;
    else if (i == 1)
        return y;
    else
        return z;
}

inline double Vector3D::operator[] (int i) const
{
    if (i == 0)
        return x;
    else if (i == 1)
        return y;
    else
        return z;
}

#endif // VECTOR3D_H
