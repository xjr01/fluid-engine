#include <limits>
#include "Box.h"
#include <Utilities/MathFunctions.h>

_FLUID_ENGINE_BEGIN

template<int Dim>
inline Box<Dim>::Box(const BoundingBox<Dim>& bound) : _bound(bound)
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

template class Box<2>;
template class Box<3>;

_FLUID_ENGINE_END