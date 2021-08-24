#pragma once

#include <array>
#include "Surface.h"

_FLUID_ENGINE_BEGIN

template <int Dim>
class Triangle : public Surface<Dim> {
	static_assert(Dim == 3, "Dimension of Triangle must be 3.");
	DECLARE_DIM_TYPES(Dim)

	/*
	* Three points of this triangle
	* note: the order decides the direction of the face normal
	*	Right hand law according to _points[0] -> _points[1] -> _points[2]
	*/
	std::array<VectorDr, 3> _points;
	/* Normals at the three points */
	std::array<VectorDr, 3> _normals;
	/* Uv coordinates */
	std::array<Vector2r, 3> _uvs;
public:
	Triangle(
		const std::array<VectorDr, 3>& points,
		const std::array<VectorDr, 3>& normals,
		const std::array<Vector2r, 3>& uvs);

	const VectorDr& points(int i) const { return _points[i]; }
	const VectorDr& normals(int i) const { return _normals[i]; }
	const Vector2r& uvs(int i) const { return _uvs[i]; }

	/* Returns the face normal of this triagle */
	VectorDr faceNormal() const;
	/* Returns the area of this triangle */
	real area() const;
	/* Set the three normals to the face normal */
	void setNormalsToFaceNormal();

	virtual VectorDr closestPoint(const VectorDr& otherPoint) const override;
	virtual VectorDr closestNormal(const VectorDr& otherPoint) const override;
	virtual BoundingBox<Dim> boundingBox() const override;
	virtual void getClosestIntersection(const Ray<Dim>& ray, SurfaceRayIntersection<Dim>& intersection) const override;
private:
	/* Helper functions */

	/* Returns the closest point on the edge (p1, p2) to given point */
	VectorDr closestPointOnEdge(const VectorDr& p1, const VectorDr& p2, const VectorDr& otherPoint) const;
	/* Returns the closest normal on the edge (p1, p2) (with normals n1 and n2) to given point */
	VectorDr closestNormalOnEdge(const VectorDr& p1, const VectorDr& p2,
		const VectorDr& n1, const VectorDr& n2, const VectorDr& otherPoint) const;
};

_FLUID_ENGINE_END