#pragma once

#include "Utilities/Types.h"

_FLUID_ENGINE_BEGIN

template <int Dim>
class Field {
public:
	Field() = default;
	virtual ~Field() = default;
};

template <int Dim>
class ScalarField : public Field<Dim> {
	DECLARE_DIM_TYPES(Dim)
public:
	ScalarField() = default;
	virtual ~ScalarField() = default;

	virtual real sample(const VectorDr& x) const = 0;
	virtual VectorDr gradient(const VectorDr& x) const = 0;
	virtual real laplacian(const VectorDr& x) const = 0;
};

template <int Dim> class VectorField;

template <>
class VectorField<3> : public Field<3> {
public:
	VectorField() = default;
	virtual ~VectorField() = default;

	virtual Vector3r sample(const Vector3r& x) const = 0;
	virtual real divergence(const Vector3r& x) const = 0;
	virtual Vector3r curl(const Vector3r& x) const = 0;
};

template <>
class VectorField<2> : public Field<2> {
public:
	VectorField() = default;
	virtual ~VectorField() = default;

	virtual Vector2r sample(const Vector2r& x) const = 0;
	virtual real divergence(const Vector2r& x) const = 0;
	virtual real curl(const Vector2r& x) const = 0;
};

_FLUID_ENGINE_END