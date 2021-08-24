#include "TriangleMesh.h"

_FLUID_ENGINE_BEGIN

template<int Dim>
inline TriangleMesh<Dim>::TriangleMesh(
	const std::vector<VectorDr>& points,
	const std::vector<VectorDr>& normals,
	const std::vector<Vector2r>& uvs,
	const std::vector<std::array<int, 3>>& indecies) :
	_points(points), _normals(normals), _uvs(uvs), _indecies(indecies)
{
}

template<int Dim>
TriangleMesh<Dim>::VectorDr TriangleMesh<Dim>::closestPoint(const VectorDr& otherPoint) const
{
	return VectorDr();
}

template<int Dim>
TriangleMesh<Dim>::VectorDr TriangleMesh<Dim>::closestNormal(const VectorDr& otherPoint) const
{
	return VectorDr();
}

template<int Dim>
BoundingBox<Dim> TriangleMesh<Dim>::boundingBox() const
{
	return BoundingBox<Dim>();
}

template<int Dim>
void TriangleMesh<Dim>::getClosestIntersection(const Ray<Dim>& ray, SurfaceRayIntersection<Dim>& intersection) const
{
}

_FLUID_ENGINE_END