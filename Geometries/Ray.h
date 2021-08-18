#pragma once

#include "Utilities/Types.h"

_FLUID_ENGINE_BEGIN

/*
* Ray<Dim>
*	a ray with a origin point and a direction vector
*/
template <int Dim>
class Ray {
	DECLARE_DIM_TYPES(Dim)

	/* The origin point */
	VectorDr _origin;
	/* The direction vector */
	VectorDr _direction;
public:
	Ray() = default;
	~Ray() = default;

	Ray(const VectorDr& origin, const VectorDr& direction);

	const VectorDr& origin() const { return _origin; }
	VectorDr& origin() { return _origin; }
	const VectorDr& direction() const { return _direction; }
	void setDirection(const VectorDr& newDirection);
};

_FLUID_ENGINE_END