#include <limits>
#include <ranges>
#include "Box.h"
#include <Utilities/MathFunctions.h>

_FLUID_ENGINE_BEGIN

template<int Dim>
inline Box<Dim>::Box(const BoundingBox<Dim>& bound) : _bound(bound)
{
}

template<int Dim>
Box<Dim>::Box(const VectorDr& lowerCorner, const VectorDr& upperCorner) :
	_bound(lowerCorner, upperCorner)
{
}

template<int Dim>
Box<Dim>::VectorDr Box<Dim>::closestPoint(const VectorDr& otherPoint) const
{
	constexpr uint dimAll = 1 << Dim;
	real closestDistanceSquared = std::numeric_limits<real>::infinity();
	VectorDr res;
	for (uint dimSet = 0; dimSet < dimAll - 1; ++dimSet) {
		bool isInside = true;
		VectorDr currentClosestPoint;
		real currentDistanceSquared = 0;
		for (uint i = 0; i < Dim; ++i)
			if (dimSet >> i & 1) {
				if (otherPoint(i) <= _bound.lowerCorner()(i) || otherPoint(i) >= _bound.upperCorner()(i)) {
					isInside = false;
					break;
				}
				currentClosestPoint(i) = otherPoint(i);
			}
			else {
				real deltaLowerSquared = MathFunc::sqr(otherPoint(i) - _bound.lowerCorner()(i)),
					deltaUpperSquared = MathFunc::sqr(otherPoint(i) - _bound.upperCorner()(i));
				if (deltaLowerSquared < deltaUpperSquared) {
					currentDistanceSquared += deltaLowerSquared;
					currentClosestPoint(i) = _bound.lowerCorner()(i);
				}
				else {
					currentDistanceSquared += deltaUpperSquared;
					currentClosestPoint(i) = _bound.upperCorner()(i);
				}
			}
		if (!isInside) continue;
		if (closestDistanceSquared > currentDistanceSquared) {
			closestDistanceSquared = currentDistanceSquared;
			res = currentClosestPoint;
		}
	}
	return res;
}

template<int Dim>
Box<Dim>::VectorDr Box<Dim>::closestNormal(const VectorDr& otherPoint) const
{
	constexpr uint dimAll = 1 << Dim;
	real closestDistanceSquared = std::numeric_limits<real>::infinity();
	VectorDr res;
	for (uint dimSet = 0; dimSet < dimAll - 1; ++dimSet) {
		bool isInside = true;
		VectorDr currentClosestNormal;
		real currentDistanceSquared = 0;
		for (uint i = 0; i < Dim; ++i)
			if (dimSet >> i & 1) {
				if (otherPoint(i) <= _bound.lowerCorner()(i) || otherPoint(i) >= _bound.upperCorner()(i)) {
					isInside = false;
					break;
				}
				currentClosestNormal(i) = 0;
			}
			else {
				real deltaLowerSquared = MathFunc::sqr(otherPoint(i) - _bound.lowerCorner()(i)),
					deltaUpperSquared = MathFunc::sqr(otherPoint(i) - _bound.upperCorner()(i));
				if (deltaLowerSquared < deltaUpperSquared) {
					currentDistanceSquared += deltaLowerSquared;
					currentClosestNormal(i) = -1;
				}
				else {
					currentDistanceSquared += deltaUpperSquared;
					currentClosestNormal(i) = 1;
				}
			}
		if (!isInside) continue;
		if (closestDistanceSquared > currentDistanceSquared) {
			closestDistanceSquared = currentDistanceSquared;
			res = currentClosestNormal;
		}
	}
	return MathFunc::normalized(res);
}

template<int Dim>
BoundingBox<Dim> Box<Dim>::boundingBox() const
{
	return _bound;
}

template<int Dim>
void Box<Dim>::getClosestIntersection(const Ray<Dim>& ray, SurfaceRayIntersection<Dim>& intersection) const
{
	BoundingBoxRayIntersection<Dim> boundingIntersection = _bound.closestIntersection(ray);
	intersection.isIntersecting = boundingIntersection.isIntersecting;
	if (intersection.isIntersecting) {
		intersection.t = boundingIntersection.tNear;
		intersection.point = ray.origin() + intersection.t * ray.direction();
		intersection.normal = closestNormal(intersection.point);
	}
	else {
		intersection.t = std::numeric_limits<real>::infinity();
		intersection.point = intersection.normal = VectorDr::Zero();
	}
	return;
}

template<int Dim>
inline ImplicitBox<Dim>::ImplicitBox(const BoundingBox<Dim>& bound) :
	_box(bound)
{
}

template<int Dim>
ImplicitBox<Dim>::ImplicitBox(const VectorDr& lowerCorner, const VectorDr& upperCorner) :
	_box(lowerCorner, upperCorner)
{
}

template<int Dim>
ImplicitBox<Dim>::VectorDr ImplicitBox<Dim>::closestPoint(const VectorDr& otherPoint) const
{
	return _box.closestPoint(otherPoint);
}

template<int Dim>
ImplicitBox<Dim>::VectorDr ImplicitBox<Dim>::closestNormal(const VectorDr& otherPoint) const
{
	return _box.closestNormal(otherPoint);
}

template<int Dim>
BoundingBox<Dim> ImplicitBox<Dim>::boundingBox() const
{
	return _box.boundingBox();
}

template<int Dim>
void ImplicitBox<Dim>::getClosestIntersection(const Ray<Dim>& ray, SurfaceRayIntersection<Dim>& intersection) const
{
	return _box.getClosestIntersection(ray, intersection);
}

template<int Dim>
real ImplicitBox<Dim>::signedDistance(const VectorDr& otherPoint) const
{
	return (real)(isInside(otherPoint) ? -1 : 1) * closestDistance(otherPoint);
}

template<int Dim>
real ImplicitBox<Dim>::closestDistance(const VectorDr& otherPoint) const
{
	return _box.closestDistance(otherPoint);
}

template<int Dim>
bool ImplicitBox<Dim>::isInside(const VectorDr& otherPoint) const
{
	return std::ranges::all_of(std::views::iota(0, Dim), [&](int i) {
		return _box.lowerCorner()(i) <= otherPoint(i) &&
			otherPoint(i) <= _box.upperCorner()(i);
	});
}

template class Box<2>;
template class Box<3>;

template class ImplicitBox<2>;
template class ImplicitBox<3>;

_FLUID_ENGINE_END