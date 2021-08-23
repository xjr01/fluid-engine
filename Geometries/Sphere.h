#pragma once

#include "Surface.h"

_FLUID_ENGINE_BEGIN

template <int Dim>
class Sphere : public Surface<Dim> {
	DECLARE_DIM_TYPES(Dim)

	VectorDr _center;
	real _radius;
public:
	Sphere(const VectorDr& center, const real& radius);

	const VectorDr& center() const { return _center; }
	VectorDr& center() { return _center; }
	const real& radius() const { return _radius; }
	real& radius() { return _radius; }

	virtual VectorDr closestPoint(const VectorDr& otherPoint) const override;
	virtual VectorDr closestNormal(const VectorDr& otherPoint) const override;
	virtual BoundingBox<Dim> boundingBox() const override;
	virtual void getClosestIntersection(const Ray<Dim>& ray, SurfaceRayIntersection<Dim>& intersection) const override;
};

_FLUID_ENGINE_END