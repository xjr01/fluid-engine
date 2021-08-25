#pragma once

#include <array>
#include <vector>
#include "Triangle.h"

_FLUID_ENGINE_BEGIN

template <int Dim>
class TriangleMesh : public Surface<Dim> {
	static_assert(Dim == 3, "Dimension of TriangleMesh must be 3.")
	DECLARE_DIM_TYPES(Dim)

	std::vector<VectorDr> _points;
	std::vector<VectorDr> _normals;
	std::vector<Vector2r> _uvs;
	std::vector<std::array<int, 3>> _indecies;
public:
	TriangleMesh(
		const std::vector<VectorDr>& points,
		const std::vector<VectorDr>& normals,
		const std::vector<Vector2r>& uvs,
		const std::vector<std::array<int, 3>>& indecies);

	const VectorDr& points(int i) { return _points[i]; }
	const VectorDr& normals(int i) { return _normals[i]; }
	const Vector2r& uvs(int i) { return _uvs[i]; }
	const std::array<int, 3>& indecies(int i) { return _indecies[i]; }
	const int& index(int i, int j) { return _indecies[i][j]; }

	virtual VectorDr closestPoint(const VectorDr& otherPoint) const override;
	virtual VectorDr closestNormal(const VectorDr& otherPoint) const override;
	virtual BoundingBox<Dim> boundingBox() const override;
	virtual void getClosestIntersection(const Ray<Dim>& ray, SurfaceRayIntersection<Dim>& intersection) const override;
};

_FLUID_ENGINE_END