#pragma once

#include "Types.h"

_MATH_FUNC_BEGIN

template <typename Type>
concept isVector = requires (Type x) {
	x / x.norm();
	x /= x.norm();
};

template <isVector VectorType>
VectorType normalized(const VectorType& ths);

template <isVector VectorType>
void normalize(VectorType& ths);

_MATH_FUNC_END