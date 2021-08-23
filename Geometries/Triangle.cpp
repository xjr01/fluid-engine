#include <Eigen/Geometry>
#include <limits>
#include "Triangle.h"
#include <Utilities/MathFunctions.h>
#include <Utilities/Constants.h>

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
	try {
		for (int i = 0; i < 3; ++i)
			MathFunc::normalize<VectorDr>(_normals[i]);
	}
	catch (const char* msg) {
		if (!strcmp(msg, "Vector being normalized should not be zero!"))
			throw "Normal should not be zero!";
		throw msg;
	}
}

template<int Dim>
Triangle<Dim>::VectorDr Triangle<Dim>::faceNormal() const
{
	try {
		return MathFunc::normalized<VectorDr>((_points[1] - _points[0]).cross(_points[2] - _points[0]));
	}
	catch (const char* msg) {
		if (!strcmp(msg, "Vector being normalized should not be zero!"))
			throw "Three points of a triangle must distinct from each other!";
		throw msg;
	}
}

template<int Dim>
real Triangle<Dim>::area() const
{
	return (real).5 * (_points[1] - _points[0]).cross(_points[2] - _points[0]).norm();
}

template<int Dim>
void Triangle<Dim>::setNormalsToFaceNormal()
{
	_normals[0] = _normals[1] = _normals[2] = faceNormal();
}

template<int Dim>
Triangle<Dim>::VectorDr Triangle<Dim>::closestPoint(const VectorDr& otherPoint) const
{
	VectorDr normal = faceNormal();
	real signedDistanceToPlane = (otherPoint - _points[0]).dot(normal);
	VectorDr projectedPoint = otherPoint - signedDistanceToPlane * normal;

	if ((_points[1] - _points[0]).cross(projectedPoint - _points[0]).dot(normal) < 0)
		return closestPointOnEdge(_points[0], _points[1], otherPoint);
	if ((_points[2] - _points[1]).cross(projectedPoint - _points[1]).dot(normal) < 0)
		return closestPointOnEdge(_points[1], _points[2], otherPoint);
	if ((_points[0] - _points[2]).cross(projectedPoint - _points[2]).dot(normal) < 0)
		return closestPointOnEdge(_points[2], _points[0], otherPoint);
	return projectedPoint;
}

template<int Dim>
Triangle<Dim>::VectorDr Triangle<Dim>::closestNormal(const VectorDr& otherPoint) const
{
	VectorDr normal = faceNormal();
	real signedDistanceToPlane = (otherPoint - _points[0]).dot(normal);
	VectorDr projectedPoint = otherPoint - signedDistanceToPlane * normal;

	if ((_points[1] - _points[0]).cross(projectedPoint - _points[0]).dot(normal) < 0)
		return closestNormalOnEdge(_points[0], _points[1], _normals[0], _normals[1], otherPoint);
	if ((_points[2] - _points[1]).cross(projectedPoint - _points[1]).dot(normal) < 0)
		return closestNormalOnEdge(_points[1], _points[2], _normals[1], _normals[2], otherPoint);
	if ((_points[0] - _points[2]).cross(projectedPoint - _points[2]).dot(normal) < 0)
		return closestNormalOnEdge(_points[2], _points[0], _normals[2], _normals[0], otherPoint);
	return normal;
}

template<int Dim>
BoundingBox<Dim> Triangle<Dim>::boundingBox() const
{
	BoundingBox<Dim> bound(_points[0], _points[1]);
	bound.merge(_points[2]);
	return bound;
}

template<int Dim>
void Triangle<Dim>::getClosestIntersection(const Ray<Dim>& ray, SurfaceRayIntersection<Dim>& intersection) const
{
}

template<int Dim>
Triangle<Dim>::VectorDr Triangle<Dim>::closestPointOnEdge(
	const VectorDr& p1, const VectorDr& p2, const VectorDr& otherPoint) const
{
	real lengthSquared = (p2 - p1).squaredNorm();
	if (lengthSquared <= MathFunc::sqr(eps))
		return p1;
	real t = (otherPoint - p1).dot(p2 - p1) / lengthSquared;
	if (t < 0) return p1;
	if (t > 1) return p2;
	return p1 + t * (p2 - p1);
}

template<int Dim>
Triangle<Dim>::VectorDr Triangle<Dim>::closestNormalOnEdge(
	const VectorDr& p1, const VectorDr& p2,
	const VectorDr& n1, const VectorDr& n2, const VectorDr& otherPoint) const
{
	real lengthSquared = (p2 - p1).squaredNorm();
	if (lengthSquared <= MathFunc::sqr(eps))
		return p1;
	real t = (otherPoint - p1).dot(p2 - p1) / lengthSquared;
	if (t < 0) return n1;
	if (t > 1) return n2;
	return MathFunc::normalized<VectorDr>(n1 + t * (n2 - n1));
}

template class Triangle<3>;

_FLUID_ENGINE_END