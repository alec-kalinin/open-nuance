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

#ifndef IO_H
#define IO_H

#include <vector>
#include <string>

#include "../linalg/Vector3D.h"
#include "../linalg/MatrixMN.h"

void savetxt(const std::string & fname, const std::vector<Vector3D> & a);
void savetxt(const std::string & fname, const MatrixMN & A);

#endif // IO_H
