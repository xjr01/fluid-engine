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

	VectorDr q01 = (_points[1] - _points[0]).cross(projectedPoint - _points[0]);
	if (q01.dot(normal) < 0)
		return closestPointOnEdge(_points[0], _points[1], otherPoint);
	VectorDr q12 = (_points[2] - _points[1]).cross(projectedPoint - _points[1]);
	if (q12.dot(normal) < 0)
		return closestPointOnEdge(_points[1], _points[2], otherPoint);
	VectorDr q20 = (_points[0] - _points[2]).cross(projectedPoint - _points[2]);
	if (q20.dot(normal) < 0)
		return closestPointOnEdge(_points[2], _points[0], otherPoint);

	real sum = area(),
		b01 = (real).5 * q01.norm() / sum,
		b12 = (real).5 * q12.norm() / sum,
		b20 = (real).5 * q20.norm() / sum;
	return b12 * _points[0] + b20 * _points[1] + b01 * _points[2];
}

template<int Dim>
Triangle<Dim>::VectorDr Triangle<Dim>::closestNormal(const VectorDr& otherPoint) const
{
	VectorDr normal = faceNormal();
	real signedDistanceToPlane = (otherPoint - _points[0]).dot(normal);
	VectorDr projectedPoint = otherPoint - signedDistanceToPlane * normal;

	VectorDr q01 = (_points[1] - _points[0]).cross(projectedPoint - _points[0]);
	if (q01.dot(normal) < 0)
		return closestNormalOnEdge(_points[0], _points[1], _normals[0], _normals[1], otherPoint);
	VectorDr q12 = (_points[2] - _points[1]).cross(projectedPoint - _points[1]);
	if (q12.dot(normal) < 0)
		return closestNormalOnEdge(_points[1], _points[2], _normals[1], _normals[2], otherPoint);
	VectorDr q20 = (_points[0] - _points[2]).cross(projectedPoint - _points[2]);
	if (q20.dot(normal) < 0)
		return closestNormalOnEdge(_points[2], _points[0], _normals[2], _normals[0], otherPoint);

	real sum = area(),
		b01 = (real).5 * q01.norm() / sum,
		b12 = (real).5 * q12.norm() / sum,
		b20 = (real).5 * q20.norm() / sum;
	return MathFunc::normalized<VectorDr>(b12 * _normals[0] + b20 * _normals[1] + b01 * _normals[2]);
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
	VectorDr normal = faceNormal();
	real nd = normal.dot(ray.direction());

	intersection.isIntersecting = true;

	if (nd < eps) intersection.isIntersecting = false; // parallel
	intersection.t = (_points[0] - ray.origin()).dot(normal) / nd;
	intersection.point = ray.origin() + intersection.t * ray.direction();

	VectorDr q01 = (_points[1] - _points[0]).cross(intersection.point - _points[0]);
	if (q01.dot(normal) < 0)
		intersection.isIntersecting = false;
	VectorDr q12 = (_points[2] - _points[1]).cross(intersection.point - _points[1]);
	if (q12.dot(normal) < 0)
		intersection.isIntersecting = false;
	VectorDr q20 = (_points[0] - _points[2]).cross(intersection.point - _points[2]);
	if (q20.dot(normal) < 0)
		intersection.isIntersecting = false;

	if (intersection.isIntersecting) {
		real sum = area(),
			b01 = (real).5 * q01.norm() / sum,
			b12 = (real).5 * q12.norm() / sum,
			b20 = (real).5 * q20.norm() / sum;
		intersection.normal = MathFunc::normalized<VectorDr>(b12 * _normals[0] + b20 * _normals[1] + b01 * _normals[2]);
	}
	else {
		intersection.t = std::numeric_limits<real>::infinity();
		intersection.point = intersection.normal = VectorDr::Zero();
	}
	return;
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