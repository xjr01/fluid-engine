#include <cmath>
#include <limits>
#include "Sphere.h"
#include "Utilities/Constants.h"
#include "Utilities/MathFunctions.h"

_FLUID_ENGINE_BEGIN

DECLARE_DIM_TYPES(Dim)

template<int Dim>
inline Sphere<Dim>::Sphere(const VectorDr& center, const real& radius) :
	_center(center), _radius(radius)
{
}

template<int Dim>
VectorDr Sphere<Dim>::closestPoint(const VectorDr& otherPoint) const
{
	return _center + _radius * closestNormal(otherPoint);
}

template<int Dim>
VectorDr Sphere<Dim>::closestNormal(const VectorDr& otherPoint) const
{
	VectorDr direction = otherPoint - _center;
	if (direction.norm() < eps) return VectorDr(1, 0, 0);
	return MathFunc::normalized(direction);
}

template<int Dim>
void Sphere<Dim>::getClosestIntersection(const Ray<Dim>& ray, SurfaceRayIntersection<Dim>& intersection) const
{
	VectorDr r = ray.origin() - _center;
	real b = (real)2 * r.dot(ray.direction()),
		c = r.dot(r),
		delta = b * b - (real)4 * c; // a = 1;
	if (delta < 0) intersection.isIntersecting = false;
	else {
		real t1 = (-b - std::sqrt(delta)) * (real).5,
			t2 = (-b + std::sqrt(delta)) * (real).5;
		if (t1 >= 0) intersection.t = t1;
		else if (t2 >= 0) intersection.t = t2;
		else intersection.t = -std::numeric_limits<real>::infinity();
		intersection.isIntersecting = intersection.t >= 0;
	}
	if (intersection.isIntersecting) {
		intersection.point = ray.origin() + ray.direction() * intersection.t;
		intersection.normal = MathFunc::normalized(intersection.point - _center);
	}
	else {
		intersection.t = (real)0;
		intersection.point = intersection.normal = VectorDr::Zero();
	}
	return;
}

_FLUID_ENGINE_END