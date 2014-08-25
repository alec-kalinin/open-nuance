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

#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>

#include "../linalg/Vector3D.h"
#include "../linalg/MatrixMN.h"
#include "../io/io.h"

using namespace std;

vector<Vector3D> generatePoints(int N)
{
    vector<Vector3D> points;

    //srand(time(0));
    for (int i = 0; i < N; i++) {
        Vector3D v;
        v.x = (double)rand() / (double)RAND_MAX;
        v.y = (double)rand() / (double)RAND_MAX;
        v.z = (double)rand() / (double)RAND_MAX;

        points.push_back(v);
    }

    return points;
}

//! Single thread matrix R calculation
void stGetR(vector<Vector3D> & p, vector<Vector3D> & q, MatrixMN & R)
{
    for (int i = 0; i < p.size(); i++) {
        Vector3D & a = p[i];
        for (int j = 0; j < q.size(); j++) {
            Vector3D & b = q[j];

            Vector3D r = b - a;
            R(i, j) = 1 / (1 + sqrt(r * r));
        }
    }
}

int main()
{
    const int N = 5000;

    vector<Vector3D> p = generatePoints(N);
    vector<Vector3D> q = generatePoints(N);
    MatrixMN R(N, N);

    stGetR(p, q, R);

    savetxt("p.npy", p);
    cout << setprecision(4);
    cout << R(0, 0);

    return 0;
}
