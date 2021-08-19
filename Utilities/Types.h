#pragma once

#include "Macros.h"

#include <Eigen/Dense>
#include <Eigen/Sparse>

_FLUID_ENGINE_BEGIN

template <typename Scalar, int Dim> using Vector = Eigen::Matrix<Scalar, Dim, 1>;
template <typename Scalar, int Dim> using Matrix = Eigen::Matrix<Scalar, Dim, Dim>;

/*
* Define types Vector[2,3,4]
*/
#define DECLARE_VECTOR_TYPE_WITH_DIMENSION(Dim)								\
	template <typename Scalar> using Vector##Dim = Vector<Scalar, Dim>;

DECLARE_VECTOR_TYPE_WITH_DIMENSION(2)
DECLARE_VECTOR_TYPE_WITH_DIMENSION(3)
DECLARE_VECTOR_TYPE_WITH_DIMENSION(4)

#undef DECLARE_VECTOR_TYPE_WITH_DIMENSION

/*
* Define types Vector[2,3,4][i,f,d]
*/
#define DECLARE_VECTOR_TYPE_WITH_SCALAR_TYPE(Scalar, initial)				\
	using Vector2##initial = Eigen::Vector2##initial;						\
	using Vector3##initial = Eigen::Vector3##initial;						\
	using Vector4##initial = Eigen::Vector4##initial;

DECLARE_VECTOR_TYPE_WITH_SCALAR_TYPE(int, i)
DECLARE_VECTOR_TYPE_WITH_SCALAR_TYPE(float, f)
DECLARE_VECTOR_TYPE_WITH_SCALAR_TYPE(double, d)

#undef DELARE_VECTOR_TYPE_WITH_SCALAR_TYPE

/*
* Define types Matrix[2,3,4]
*/
#define DECLARE_MATRIX_TYPE_WITH_DIMENSION(Dim)								\
	template <typename Scalar> using Matrix##Dim = Matrix<Scalar, Dim>;

DECLARE_MATRIX_TYPE_WITH_DIMENSION(2)
DECLARE_MATRIX_TYPE_WITH_DIMENSION(3)
DECLARE_MATRIX_TYPE_WITH_DIMENSION(4)

#undef DECLARE_MATRIX_TYPE_WITH_DIMENSION

/*
* Define types Matrix[2,3,4][f,d]
*/
#define DECLARE_MATRIX_TYPE_WITH_SCALAR_TYPE(Scalar, initial)				\
	using Matrix2##initial = Eigen::Matrix2##initial;						\
	using Matrix3##initial = Eigen::Matrix3##initial;						\
	using Matrix4##initial = Eigen::Matrix4##initial;						\
	using Triplet##initial = Eigen::Triplet<Scalar>;						\
	using SparseMatrix##initial = Eigen::SparseMatrix<Scalar>;

DECLARE_MATRIX_TYPE_WITH_SCALAR_TYPE(float, f)
DECLARE_MATRIX_TYPE_WITH_SCALAR_TYPE(double, d)

#undef DECLARE_MATRIX_TYPE_WITH_SCALAR_TYPE

/*
* Define types [real,[Vector,Matrix][2,3,4]r]
*/
#define DECLARE_REAL_TYPE(Type, initial)									\
	using real = Type;														\
	using Vector2r = Eigen::Vector2##initial;								\
	using Vector3r = Eigen::Vector3##initial;								\
	using Vector4r = Eigen::Vector4##initial;								\
	using Matrix2r = Eigen::Matrix2##initial;								\
	using Matrix3r = Eigen::Matrix3##initial;								\
	using Matrix4r = Eigen::Matrix4##initial;								\
	using Tripletr = Triplet##initial;										\
	using SparseMatrixr = SparseMatrix##initial;

#ifdef USING_FLOAT
DECLARE_REAL_TYPE(float, f)
#else
DECLARE_REAL_TYPE(double, d)
#endif

#undef DECLARE_REAL_TYPE

/*
* Define types [VectorD[r,i],MatrixDr] whenever needed
*/
#define DECLARE_DIM_TYPES(Dim)												\
	static_assert(2 <= Dim && Dim <= 3, "Dimension must be 2 or 3.");		\
	using VectorDr = Vector<real, Dim>;										\
	using VectorDi = Vector<int, Dim>;										\
	using MatrixDr = Matrix<real, Dim>;

using uchar = unsigned char;
using ushort = unsigned short;
using uint = unsigned int;
using llong = long long;
using ullong = unsigned long long;
using std::size_t;

_FLUID_ENGINE_END