#pragma once
#include "Point.h"
#include <vector>
#include <memory>

struct Triangle {
	std::shared_ptr<Point> points[3];
	Point normal;

	// Constructor
	Triangle(std::shared_ptr<Point> p1, std::shared_ptr<Point> p2, std::shared_ptr<Point> p3, Point normal = Point(0, 0, 0)) : normal(normal) {
		points[0] = p1;
		points[1] = p2;
		points[2] = p3;
		//std::cout << "Constructor Triangle" << std::endl;
	}

	// Destructor
	//~Triangle() {
	//	std::cout << "Destructor Triangle" << std::endl;
	//}
};