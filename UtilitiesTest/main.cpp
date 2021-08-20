#include <iostream>
#include <Utilities/Types.h>
#include <Geometries/Sphere.h>
#include <Geometries/Ray.h>

std::ostream& operator << (std::ostream& os, const FluidEngine::Vector2d& vec) {
	os << '(';
	for (int i = 0; i < 2; ++i) os << vec(i) << (i < 2 - 1 ? ',' : ')');
	return os;
}

int main() {
	using namespace FluidEngine;
	Sphere<2> sphere(Vector2r(1, 2), 4);
	Ray<2> ray(Vector2r(1, -1), Vector2r(4, 3));

	std::cout << ray.direction() << std::endl;

	auto intersection = sphere.closestIntersection(ray);
	std::cout << intersection.isIntersecting << " | "
		<< intersection.point << " " << intersection.normal << std::endl;
	std::cout << sphere.closestPoint(Vector2r(1, 0)) << " " << sphere.closestNormal(Vector2r(1, 0)) << std::endl;

	return 0;
}