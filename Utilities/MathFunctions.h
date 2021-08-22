#pragma once

#include "Types.h"
#include "Constants.h"

_MATH_FUNC_BEGIN

template <typename Type>
concept isVector = requires (Type x) {
	x / x.norm();
	x /= x.norm();
};

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

real sqr(real x);

_MATH_FUNC_END