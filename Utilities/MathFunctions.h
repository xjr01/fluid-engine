#pragma once

#include "Types.h"
#include "Constants.h"

_MATH_FUNC_BEGIN

template <class VectorType>
VectorType normalized(const VectorType& ths) {
	real length = ths.norm();
	if (length < eps)
		throw "Vector being normalized should not be zero!";
	return ths / length;
}

template <class VectorType>
void normalize(VectorType& ths) {
	if (length < eps)
		throw "Vector being normalized should not be zero!";
	ths /= length;
	return;
}

_MATH_FUNC_END