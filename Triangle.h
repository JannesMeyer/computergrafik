#pragma once
#include "Point.h"
#include <vector>
#include <memory>

/*
 * Triangle class
 * Author: Jannes Meyer
 */

struct Triangle {
	std::shared_ptr<Point> points[3];
	vec3 normal;

	Triangle(std::shared_ptr<Point> p1,
	         std::shared_ptr<Point> p2,
             std::shared_ptr<Point> p3,
             vec3 normal = vec3(0, 0, 0))
		: normal(normal)
	{
		points[0] = p1;
		points[1] = p2;
		points[2] = p3;
	}

	// Q: How to avoid too many temporary objects?
	/*~Triangle() {
		std::cout << "Destructor of Triangle" << std::endl;
	}*/

	// Only compute normals when we actually need them
	void Triangle::calculateNormal() {
		normal = (points[1]->coord - points[0]->coord) %
		         (points[2]->coord - points[0]->coord);
	}
};