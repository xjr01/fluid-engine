#include "Triangle.h"

_FLUID_ENGINE_BEGIN

template<int Dim>
inline Triangle<Dim>::Triangle(
	const std::array<VectorDr, 3>& points,
	const std::array<VectorDr, 3>& normals,
	const std::array<Vector2r, 3>& uvs) :
	_points(points),
	_normals(normals),
	_uvs(uvs)
{
}

template<int Dim>
Triangle<Dim>::VectorDr Triangle<Dim>::closestPoint(const VectorDr& otherPoint) const
{
	return VectorDr();
}

template<int Dim>
Triangle<Dim>::VectorDr Triangle<Dim>::closestNormal(const VectorDr& otherPoint) const
{
	return VectorDr();
}

template<int Dim>
BoundingBox<Dim> Triangle<Dim>::boundingBox() const
{
	return BoundingBox<Dim>();
}

template<int Dim>
void Triangle<Dim>::getClosestIntersection(const Ray<Dim>& ray, SurfaceRayIntersection<Dim>& intersection) const
{
}

template class Triangle<3>;

_FLUID_ENGINE_END