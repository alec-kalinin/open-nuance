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

#include "Vector3D.h"

using namespace std;

Vector3D::Vector3D()
    : x(0.0), y(0.0), z(0.0)
{
}

Vector3D::Vector3D(double x, double y, double z)
    : x(x), y(y), z(z)
{
}

Vector3D::~Vector3D()
{
}

double Vector3D::norm() const
{
    return sqrt(x * x + y * y + z * z);
}

Vector3D & Vector3D::operator= (const Vector3D & src)
{
    x = src.x;
    y = src.y;
    z = src.z;

    return (*this);
}

const Vector3D operator+ (const Vector3D & a, const Vector3D & b)
{
    return Vector3D (a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3D & Vector3D::operator+= (const Vector3D & b)
{
    x += b.x;
    y += b.y;
    z += b.z;

    return (*this);
}

const Vector3D operator- (const Vector3D & a, const Vector3D & b)
{
    return Vector3D (a.x - b.x, a.y - b.y, a.z - b.z);
}

const Vector3D Vector3D::operator-() const
{
    return Vector3D(-x, -y, -z);
}

double operator* (const Vector3D & a, const Vector3D & b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

const Vector3D operator* (double alpha, const Vector3D & a)
{
    return Vector3D(a.x * alpha, a.y * alpha, a.z * alpha);
}

const Vector3D operator^ (const Vector3D & a, const Vector3D & b)
{
    return Vector3D (a.y * b.z - a.z * b.y,
                     a.z * b.x - a.x * b.z,
                     a.x * b.y - a.y * b.x);
}

const Vector3D operator/ (const Vector3D & a, double alpha)
{
    return Vector3D(a.x / alpha, a.y / alpha, a.z / alpha);
}
