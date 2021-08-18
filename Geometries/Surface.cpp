#include "Surface.h"

_FLUID_ENGINE_BEGIN

template<int Dim>
inline SurfaceRayIntersection<Dim> Surface<Dim>::closestIntersection(const Ray<Dim>& ray) const
{
	SurfaceRayIntersection<Dim> intersection;
	getClosestIntersection(ray, intersection);
	return intersection;
}

template<int Dim>
bool Surface<Dim>::intersects(const Ray<Dim>& ray) const
{
	return closestIntersection(ray).isIntersecting;
}

template<int Dim>
real Surface<Dim>::closestDistance(const VectorDr& otherPoint) const
{
	return (otherPoint - closestPoint(otherPoint)).norm();
}

_FLUID_ENGINE_END