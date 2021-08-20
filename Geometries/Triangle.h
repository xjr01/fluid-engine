#pragma once

#include <array>
#include "Surface.h"

_FLUID_ENGINE_BEGIN

template <int Dim>
class Triangle : public Surface<Dim> {
	DECLARE_DIM_TYPES(Dim)

	std::array<VectorDr, 3> _points;
	std::array<VectorDr, 3> _normals;
	std::array<VectorDr, 3> _uvs;
public:
	Triangle(
		const std::array<VectorDr, 3>& points,
		const std::array<VectorDr, 3>& normals,
		const std::array<VectorDr, 3>& uvs);

	virtual VectorDr closestPoint(const VectorDr& otherPoint) const override;
	virtual VectorDr closestNormal(const VectorDr& otherPoint) const override;
	virtual void getClosestIntersection(const Ray<Dim>& ray, SurfaceRayIntersection<Dim>& intersection) const override;
};

_FLUID_ENGINE_END