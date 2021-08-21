#pragma once

#include "Ray.h"
#include <Utilities/Types.h>

_FLUID_ENGINE_BEGIN

/*
* BoundingBoxRayIntersection<Dim>
*	a structure that stores intersection info
*/
template <int Dim>
class BoundingBoxRayIntersection {
	DECLARE_DIM_TYPES(Dim)
public:
	/* Whether the ray is intersecting the surface */
	bool isIntersecting;
	/* Distance to the first intersection point, if there's no intersection this is infinity */
	real tNear;
	/* Distance to the second intersection point, if none this is infinity */
	real tFar;
};

/*
* BoundingBox<Dim>
*	a class of bounding box
*/
template <int Dim>
class BoundingBox {
	DECLARE_DIM_TYPES(Dim)

	/* Lower coordinates on each dimension */
	VectorDr _lowerCorner;
	/* Upper coordinates of each dimension */
	VectorDr _upperCorner;
public:
	BoundingBox() = default;
	~BoundingBox() = default;

	BoundingBox(const VectorDr& lowerCorner, const VectorDr& upperCorner);

	/* Returns width of the box in given axis */
	real width(int axis) const;

	/* Returns true if this box and other box overlaps */
	bool overlaps(const BoundingBox& otherBox) const;
	/* Returns true if point is inside of the box */
	bool contains(const VectorDr& point) const;

	/* Returns true if the input ray is intersecting with this box */
	bool intersects(const Ray& ray) const { return closestIntersection(ray).isIntersecting; }
	/* Returns the closest intersection info of ray and this surface */
	BoundingBoxRayIntersection<Dim> closestIntersection(const Ray<Dim>& ray) const {
		BoundingBoxRayIntersection<Dim> intersection;
		getClosestIntersection(ray, intersection);
		return intersection;
	}
	/* Calculates the closest intersection info of ray and this surface and stores to intersection */
	void getClosestIntersection(const Ray<Dim>& ray, BoundingBoxRayIntersection<Dim>& intersection) const;

	/* Returns the mid-point of this box */
	VectorDr midPoint() const;

	/* Returns diagonal length of this box */
	real diagonalLength() const;
	/* Returns squared diagonal length of this box */
	real diagonalLengthSquared() const;

	/* Merges point to this box */
	void merge(const VectorDr& point);
	/* Merges otherBox to this box */
	void merge(const BoundingBox& otherBox);

	/* Expands this box by delta to all direction */
	void expand(real delta);

	/* Returns the clamped point w.r.t. this box */
	VectorDr clamped(const VectorDr& point) const;

	/* Returns true if the box is empty */
	bool isEmpty() const;
};

_FLUID_ENGINE_END