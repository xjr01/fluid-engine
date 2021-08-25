#pragma once

#include "Surface.h"
#include "BoundingBox.h"

_FLUID_ENGINE_BEGIN

template <int Dim>
class Box : public Surface<Dim> {
	DECLARE_DIM_TYPES(Dim)

	BoundingBox<Dim> _bound;
public:
	explicit Box(const BoundingBox<Dim>& bound);
	Box(const VectorDr& lowerCorner, const VectorDr& upperCorner);

	const BoundingBox<Dim>& bound() const { return _bound; }
	BoundingBox<Dim>& bound() { return _bound; }
	const VectorDr& lowerCorner() const { return _bound.lowerCorner(); }
	VectorDr& lowerCorner() { return _bound.lowerCorner(); }
	const VectorDr& upperCorner() const { return _bound.upperCorner(); }
	VectorDr& upperCorner() { return _bound.upperCorner(); }

	virtual VectorDr closestPoint(const VectorDr& otherPoint) const override;
	virtual VectorDr closestNormal(const VectorDr& otherPoint) const override;
	virtual BoundingBox<Dim> boundingBox() const override;
	virtual void getClosestIntersection(const Ray<Dim>& ray, SurfaceRayIntersection<Dim>& intersection) const override;
};

template <int Dim>
class ImplicitBox : public ImplicitSurface<Dim> {
	DECLARE_DIM_TYPES(Dim)

	Box<Dim> _box;
public:
	explicit ImplicitBox(const BoundingBox<Dim>& bound);
	ImplicitBox(const VectorDr& lowerCorner, const VectorDr& upperCorner);

	const BoundingBox<Dim>& bound() const { return _box.bound(); }
	BoundingBox<Dim>& bound() { return _box.bound(); }
	const VectorDr& lowerCorner() const { return _box.lowerCorner(); }
	VectorDr& lowerCorner() { return _box.lowerCorner(); }
	const VectorDr& upperCorner() const { return _box.upperCorner(); }
	VectorDr& upperCorner() { return _box.upperCorner(); }

	virtual VectorDr closestPoint(const VectorDr& otherPoint) const override;
	virtual VectorDr closestNormal(const VectorDr& otherPoint) const override;
	virtual BoundingBox<Dim> boundingBox() const override;
	virtual void getClosestIntersection(const Ray<Dim>& ray, SurfaceRayIntersection<Dim>& intersection) const override;

	virtual real signedDistance(const VectorDr& otherPoint) const override;
	virtual real closestDistance(const VectorDr& otherPoint) const override;
	virtual bool isInside(const VectorDr& otherPoint) const override;
};

_FLUID_ENGINE_END