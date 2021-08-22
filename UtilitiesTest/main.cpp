#include <iostream>
#include <numeric>
#include <Utilities/Types.h>
#include <Geometries/Sphere.h>
#include <Geometries/Ray.h>
#include <Geometries/Box.h>

std::ostream& operator << (std::ostream& os, const FluidEngine::Vector2d& vec) {
	os << '(';
	for (int i = 0; i < 2; ++i) os << vec(i) << (i < 2 - 1 ? ',' : ')');
	return os;
}
std::ostream& operator << (std::ostream& os, const FluidEngine::Vector3d& vec) {
	os << '(';
	for (int i = 0; i < 3; ++i) os << vec(i) << (i < 3 - 1 ? ',' : ')');
	return os;
}

template <int Dim>
std::ostream& operator << (std::ostream& os, const FluidEngine::BoundingBox<Dim>& box) {
	os << '[' << box.lowerCorner() << ',' << box.upperCorner() << ']';
	return os;
}
template <int Dim>
std::ostream& operator << (std::ostream& os, const FluidEngine::Box<Dim>& box) {
	os << '[' << box.lowerCorner() << ',' << box.upperCorner() << ']';
	return os;
}

int main() {
	using namespace FluidEngine;
	Sphere<2> sphere(Vector2r(1, 2), 4);
	Ray<2> ray(Vector2r(1, -1), Vector2r(4, 3));
	BoundingBox<2> sphereBounding = sphere.boundingBox();

	std::cout << ray.direction() << std::endl;

	auto intersection = sphere.closestIntersection(ray);
	std::cout << intersection.isIntersecting << " | "
		<< intersection.point << " " << intersection.normal << std::endl;
	std::cout << sphere.closestPoint(Vector2r(1, 0)) << " " << sphere.closestNormal(Vector2r(1, 0)) << std::endl;
	std::cout << "Bounding box: " << sphereBounding << std::endl;
	std::cout << "Width: " << sphereBounding.width(0) << ' ' << sphereBounding.width(1) << std::endl;
	std::cout << "Overlaps: " << sphereBounding.overlaps(BoundingBox<2>(Vector2r(0, 0), Vector2r(99, 99))) << std::endl;
	std::cout << "Contains: " << sphereBounding.contains(Vector2r(5, -2.01)) << std::endl;
	std::cout << "Intersects: " << sphereBounding.intersects(ray);
	auto boundingIntersection = sphereBounding.closestIntersection(ray);
	std::cout << ' ' << boundingIntersection.tNear;
	if (boundingIntersection.tNear < std::numeric_limits<real>::infinity())
		std::cout << Vector2r(ray.origin() + boundingIntersection.tNear * ray.direction());
	std::cout << ' ' << boundingIntersection.tFar;
	if (boundingIntersection.tFar < std::numeric_limits<real>::infinity())
		std::cout << Vector2r(ray.origin() + boundingIntersection.tFar * ray.direction());
	std::cout << std::endl;
	std::cout << "MidPoint: " << sphereBounding.midPoint() << std::endl;
	std::cout << "DiagonalLength and squared: " << sphereBounding.diagonalLength() << ' ' << sphereBounding.diagonalLengthSquared() << std::endl;
	BoundingBox<2> addingPoint = sphereBounding, addingBox = sphereBounding;
	addingPoint.merge(Vector2r(-5, 0));
	addingBox.merge(BoundingBox<2>(Vector2r(-5, 0), Vector2r(-3, 20)));
	std::cout << "Merge: " << addingPoint << ' ' << addingBox << std::endl;
	std::cout << "Clamped: " << sphereBounding.clamped(Vector2r(-9, .2)) << std::endl;
	std::cout << "IsEmpty: " << sphereBounding.isEmpty() << ' ' << BoundingBox<3>(Vector3r(5, 9, 2), Vector3r(-2, 9, 1)).isEmpty() << std::endl;

	Box<2> box(sphereBounding);
	std::cout << "Closest point: " << box.closestPoint(Vector2r(2, 3)) << box.closestPoint(Vector2r(9, 8)) << std::endl;
	std::cout << "Closest normal: " << box.closestNormal(Vector2r(2, 3)) << box.closestNormal(Vector2r(9, 8)) << std::endl;

	return 0;
}