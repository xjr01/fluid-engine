#pragma once

#include "Utilities/Types.h"

template <int Dim>
class SurfaceRayIntersection {
	DECLARE_DIM_TYPES(Dim)
public:
	bool isIntersecting;
	double t;
	VectorDr point, normal;
};

template <int Dim>
class Surface {

};