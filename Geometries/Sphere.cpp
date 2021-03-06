#include <cmath>
#include <limits>
#include "Sphere.h"
#include <Utilities/MathFunctions.h>
#include <Utilities/Constants.h>

_FLUID_ENGINE_BEGIN

template<int Dim>
inline Sphere<Dim>::Sphere(const VectorDr& center, const real& radius) :
	_center(center), _radius(radius)
{
}

template<int Dim>
Sphere<Dim>::VectorDr Sphere<Dim>::closestPoint(const VectorDr& otherPoint) const
{
	return _center + _radius * closestNormal(otherPoint);
}

template<int Dim>
Sphere<Dim>::VectorDr Sphere<Dim>::closestNormal(const VectorDr& otherPoint) const
{
	VectorDr direction = otherPoint - _center;
	if (direction.norm() < eps) return VectorDr::Unit(0);
	return MathFunc::normalized(direction);
}

template<int Dim>
BoundingBox<Dim> Sphere<Dim>::boundingBox() const
{
	return BoundingBox<Dim>(
		_center - _radius * VectorDr::Ones(),
		_center + _radius * VectorDr::Ones());
}

template<int Dim>
void Sphere<Dim>::getClosestIntersection(const Ray<Dim>& ray, SurfaceRayIntersection<Dim>& intersection) const
{
	VectorDr r = ray.origin() - _center;
	real b = (real)2 * r.dot(ray.direction()),
		c = r.dot(r) - _radius * _radius,
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
		intersection.normal = MathFunc::normalized<VectorDr>(intersection.point - _center);
	}
	else {
		intersection.t = std::numeric_limits<real>::infinity();
		intersection.point = intersection.normal = VectorDr::Zero();
	}
	return;
}

template<int Dim>
inline ImplicitSphere<Dim>::ImplicitSphere(const VectorDr& center, const real& radius) :
	_sphere(center, radius)
{
}

template<int Dim>
ImplicitSphere<Dim>::VectorDr ImplicitSphere<Dim>::closestPoint(const VectorDr& otherPoint) const
{
	return otherPoint - signedDistance(otherPoint) * closestNormal(otherPoint);
}

template<int Dim>
ImplicitSphere<Dim>::VectorDr ImplicitSphere<Dim>::closestNormal(const VectorDr& otherPoint) const
{
	return _sphere.closestNormal(otherPoint);
}

template<int Dim>
BoundingBox<Dim> ImplicitSphere<Dim>::boundingBox() const
{
	return _sphere.boundingBox();
}

template<int Dim>
void ImplicitSphere<Dim>::getClosestIntersection(const Ray<Dim>& ray, SurfaceRayIntersection<Dim>& intersection) const
{
	return _sphere.getClosestIntersection(ray, intersection);
}

template<int Dim>
real ImplicitSphere<Dim>::signedDistance(const VectorDr& otherPoint) const
{
	return (otherPoint - center()).norm() - radius();
}

template class Sphere<2>;
template class Sphere<3>;

template class ImplicitSphere<2>;
template class ImplicitSphere<3>;

_FLUID_ENGINE_END