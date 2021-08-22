#include <algorithm>
#include <limits>
#include <ranges>
#include "BoundingBox.h"
#include "Ray.h"

_FLUID_ENGINE_BEGIN

template<int Dim>
inline BoundingBox<Dim>::BoundingBox(const VectorDr& lowerCorner, const VectorDr& upperCorner) :
	_lowerCorner(lowerCorner), _upperCorner(upperCorner)
{
}

template<int Dim>
real BoundingBox<Dim>::width(int axis) const
{
	return _upperCorner(axis) - _lowerCorner(axis);
}

template<int Dim>
bool BoundingBox<Dim>::overlaps(const BoundingBox& otherBox) const
{
	return std::ranges::all_of(std::views::iota(0, Dim), [&](int i) {
		return _lowerCorner(i) <= otherBox._upperCorner(i) &&
			_upperCorner(i) >= otherBox._lowerCorner(i);
	});
}

template<int Dim>
bool BoundingBox<Dim>::contains(const VectorDr& point) const
{
	return std::ranges::all_of(std::views::iota(0, Dim), [&](int i) {
		return _lowerCorner(i) <= point(i) && point(i) <= _upperCorner(i);
	});
}

template<int Dim>
void BoundingBox<Dim>::getClosestIntersection(const Ray<Dim>& ray, BoundingBoxRayIntersection<Dim>& intersection) const
{
	intersection.tNear = -std::numeric_limits<real>::infinity();
	intersection.tFar = std::numeric_limits<real>::infinity();

	for (int i = 0; i < Dim; ++i) {
		real tNear = (_lowerCorner(i) - ray.origin()(i)) / ray.direction()(i),
			tFar = (_upperCorner(i) - ray.origin()(i)) / ray.direction()(i);
		if (tNear > tFar) std::swap(tNear, tFar);
		if (intersection.tNear < tNear) intersection.tNear = tNear;
		if (intersection.tFar > tFar) intersection.tFar = tFar;

		if (intersection.tNear > intersection.tFar) {
			intersection.isIntersecting = false;
			intersection.tNear = intersection.tFar = std::numeric_limits<real>::infinity();
			return;
		}
	}

	for (int i = 0; i < 2; ++i)
		if (intersection.tNear < 0) {
			intersection.tNear = intersection.tFar;
			intersection.tFar = std::numeric_limits<real>::infinity();
		}
	intersection.isIntersecting = intersection.tNear != std::numeric_limits<real>::infinity();
	return;
}

template<int Dim>
BoundingBox<Dim>::VectorDr BoundingBox<Dim>::midPoint() const
{
	return (_lowerCorner + _upperCorner) * (real).5;
}

template<int Dim>
real BoundingBox<Dim>::diagonalLength() const
{
	return (_upperCorner - _lowerCorner).norm();
}

template<int Dim>
real BoundingBox<Dim>::diagonalLengthSquared() const
{
	return (_upperCorner - _lowerCorner).squaredNorm();
}

template<int Dim>
void BoundingBox<Dim>::merge(const VectorDr& point)
{
	for (int i = 0; i < Dim; ++i) {
		_lowerCorner(i) = std::min(_lowerCorner(i), point(i));
		_upperCorner(i) = std::max(_upperCorner(i), point(i));
	}
	return;
}

template<int Dim>
void BoundingBox<Dim>::merge(const BoundingBox& otherBox)
{
	for (int i = 0; i < Dim; ++i) {
		_lowerCorner(i) = std::min(_lowerCorner(i), otherBox._lowerCorner(i));
		_upperCorner(i) = std::max(_upperCorner(i), otherBox._upperCorner(i));
	}
	return;
}

template<int Dim>
void BoundingBox<Dim>::expand(real delta)
{
	_lowerCorner -= delta * VectorDr::Ones();
	_upperCorner += delta * VectorDr::Ones();
	return;
}

template<int Dim>
BoundingBox<Dim>::VectorDr BoundingBox<Dim>::clamped(const VectorDr& point) const
{
	VectorDr res = point;
	for (int i = 0; i < Dim; ++i)
		res(i) = std::min(std::max(res(i), _lowerCorner(i)), _upperCorner(i));
	return res;
}

template<int Dim>
bool BoundingBox<Dim>::isEmpty() const
{
	return std::ranges::any_of(std::views::iota(0, Dim), [&](int i) {
		return _lowerCorner(i) >= _upperCorner(i);
	});
}

template class BoundingBoxRayIntersection<2>;
template class BoundingBoxRayIntersection<3>;

template class BoundingBox<2>;
template class BoundingBox<3>;

_FLUID_ENGINE_END