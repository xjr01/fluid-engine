#include "MathFunctions.h"
#include "Constants.h"

_MATH_FUNC_BEGIN

template<isVector VectorType>
VectorType normalized(const VectorType& ths)
{
	real length = ths.norm();
	if (length < eps)
		throw "Vector being normalized should not be zero!";
	return ths / length;
}

template<isVector VectorType>
void normalize(VectorType& ths)
{
	real length = ths.norm();
	if (length < eps)
		throw "Vector being normalized should not be zero!";
	ths /= length;
	return;
}

template Vector<real, 2> normalized<Vector<real, 2>>(const Vector<real, 2>&);
template Vector<real, 3> normalized<Vector<real, 3>>(const Vector<real, 3>&);
template Vector<real, 4> normalized<Vector<real, 4>>(const Vector<real, 4>&);

template void normalize(Vector<real, 2>&);
template void normalize(Vector<real, 3>&);
template void normalize(Vector<real, 4>&);

_MATH_FUNC_END