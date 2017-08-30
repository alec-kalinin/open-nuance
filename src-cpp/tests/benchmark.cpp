#include <vector>
#include <iostream>
#include <windows.h>

class Matrix {
public:
	Matrix() : nRows(0), nCols(0)
	{
		v = new double[0];
	}

	Matrix(int nRows, int nCols) : nRows(nRows), nCols(nCols)
	{
		v = new double[nRows * nCols];

		memset(v, 0, sizeof(double) * nRows * nCols);
	}

	~Matrix()
	{
		delete[] v;
	}

public:
	double & operator() (int i, int j);

public:
	int nRows;
	int nCols;

	double *v;
};

inline double & Matrix::operator() (int i, int j)
{
	return v[i * nCols + j];
}


class Point3D {
public:
	double x;
	double y;
	double z;
};

std::vector<Point3D> generatePoints(int N)
{
	std::vector<Point3D> points;

	for (int i = 0; i < N; i++) {
		Point3D p;
		p.x = (double)rand() / (double)RAND_MAX;
		p.y = (double)rand() / (double)RAND_MAX;
		p.z = (double)rand() / (double)RAND_MAX;

		points.push_back(p);
	}

	return points;
}


void getR(std::vector<Point3D> & p, std::vector<Point3D> & q, Matrix & R)
{
	double rx, ry, rz;
    
    #pragma omp parallel for
	for (int i = 0; i < p.size(); i++) {
		for (int j = 0; j < q.size(); j++) {
			rx = p[i].x - q[j].x;
			ry = p[i].y - q[j].y;
			rz = p[i].z - q[j].z;

			R(i, j) = 1 / (1 + sqrt(rx * rx + ry * ry + rz * rz));
		}
	}
}

int main()
{
	const int N = 5000;
	std::vector<Point3D> p = generatePoints(N);
	std::vector<Point3D> q = generatePoints(N);
	Matrix R(N, N);

	LARGE_INTEGER startTime, stopTime, elapsed, freq;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&startTime);
	getR(p, q, R);
	QueryPerformanceCounter(&stopTime);

	elapsed.QuadPart = stopTime.QuadPart - startTime.QuadPart;
	double ms = (double)(elapsed.QuadPart * 1000 / freq.QuadPart);
	std::cout << "time : " << ms << " ms" << std::endl;

	return 0;
}
