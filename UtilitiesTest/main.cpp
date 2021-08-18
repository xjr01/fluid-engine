#include <iostream>
#include "Utilities/Types.h"

int main() {
	using namespace FluidEngine;
	Vector3d X(1.0, 2.0, 3.0), Y(3.2, 5.6, 4.1);
	Matrix2d m1, m2;
	
	m1 << 1.0, 2.0, 3.0, 4.0;
	m2 << .5, .5, .5, .5;

	X += Y;
	printf("%lf %lf %lf\n", X(0), X(1), X(2));
	m1 -= m2;
	printf("%lf %lf\n%lf %lf\n", m1(0, 0), m1(0, 1), m1(1, 0), m1(1, 1));

	Matrix4r A;
	A << 1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16;
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			printf("%lf%c", A(i, j), j < 3 ? ' ' : '\n');

	return 0;
}