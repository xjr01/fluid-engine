#pragma once

#include "Types.h"

_MATH_FUNC_BEGIN

Vector<real, 2> normalized(const Vector<real, 2>& ths);
Vector<real, 3> normalized(const Vector<real, 3>& ths);

void normalize(Vector<real, 2>& ths);
void normalize(Vector<real, 3>& ths);

_MATH_FUNC_END