#pragma once

#include "Utilities/Types.h"
#include "Ray.h"

_FLUID_ENGINE_BEGIN

/*
* SurfaceRayIntersection<Dim>
*	a structure that stores intersection info
*/
template <int Dim>
class SurfaceRayIntersection {
	DECLARE_DIM_TYPES(Dim)
public:
	/* Whether the ray is intersecting the surface */
	bool isIntersecting;
	/* The distance between intersecting point and the ray origin point */
	real t;
	/* The intersecting point */
	VectorDr point;
	/* Normal vector at the intersecting point */
	VectorDr normal;
};

/*
* Surface<Dim>
*	an API for surfaces
*/
template <int Dim>
class Surface {
	DECLARE_DIM_TYPES(Dim)
public:
	Surface() = default;
	virtual ~Surface() = default;

	/* Returns the closest point to otherPoint on the surface */
	virtual VectorDr closestPoint(const VectorDr& otherPoint) const = 0;
	/* Returns normal vector at the closest point */
	virtual VectorDr closestNormal(const VectorDr& otherPoint) const = 0;
	/* Returns the closest intersection info of ray and this surface */
	SurfaceRayIntersection<Dim> closestIntersection(const Ray<Dim>& ray) const;
	/* Calculates the closest intersection info of ray and this surface and stores to intersection */
	virtual void getClosestIntersection(const Ray<Dim>& ray, SurfaceRayIntersection<Dim>& intersection) const = 0;
	/* Returns if ray intersects with this surface */
	bool intersects(const Ray<Dim>& ray) const;
	/* Returns the closest distance between otherPoint and this surface */
	real closestDistance(const VectorDr& otherPoint) const;
};

_FLUID_ENGINE_END