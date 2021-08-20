#include "MathFunctions.h"
#include "Constants.h"

_MATH_FUNC_BEGIN

Vector<real, 2> normalized(const Vector<real, 2>& ths) {
	real length = ths.norm();
	if (length < eps)
		throw "Vector being normalized should not be zero!";
	return ths / length;
}
Vector<real, 3> normalized(const Vector<real, 3>& ths) {
	real length = ths.norm();
	if (length < eps)
		throw "Vector being normalized should not be zero!";
	return ths / length;
}

void normalize(Vector<real, 2>& ths) {
	real length = ths.norm();
	if (length < eps)
		throw "Vector being normalized should not be zero!";
	ths /= length;
	return;
}
void normalize(Vector<real, 3>& ths) {
	real length = ths.norm();
	if (length < eps)
		throw "Vector being normalized should not be zero!";
	ths /= length;
	return;
}

_MATH_FUNC_END