#include <cstring>
#include "Ray.h"
#include <Utilities/MathFunctions.h>

_FLUID_ENGINE_BEGIN

template<int Dim>
inline Ray<Dim>::Ray(const VectorDr& origin, const VectorDr& direction) :
	_origin(origin), _direction()
{
	try {
		_direction = MathFunc::normalized(direction);
	}
	catch (const char* msg) {
		if (!strcmp(msg, "Vector being normalized should not be zero!"))
			throw "Direction vector cannot be zero!";
		throw msg;
	}
}

template<int Dim>
void Ray<Dim>::setDirection(const VectorDr& newDirection)
{
	try {
		_direction = MathFunc::normalized(newDirection);
	}
	catch (const char* msg) {
		if (!strcmp(msg, "Vector being normalized should not be zero!"))
			throw "Direction vector cannot be zero!";
		throw msg;
	}
	return;
}

template class Ray<2>;
template class Ray<3>;

_FLUID_ENGINE_END