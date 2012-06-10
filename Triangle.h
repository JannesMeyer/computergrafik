#pragma once
#include "Point.h"
#include <vector>
#include <memory>
#include <iostream>

struct Triangle {
	std::shared_ptr<Point> points[3];
	Point normal;

	// Constructor
	Triangle(std::shared_ptr<Point> p1, std::shared_ptr<Point> p2, std::shared_ptr<Point> p3, Point normal = Point(0, 0, 0)) : normal(normal) {
		points[0] = p1;
		points[1] = p2;
		points[2] = p3;
	}

	// Destructor
	//~Triangle() {
	//	std::cout << "Destructor of Triangle" << std::endl;
	//}

	// Only compute normals when we actually need them
	void Triangle::calculateNormal() {
		//std::cout << "1: " << *points[0] << std::endl;
		//std::cout << "2: " << *points[1] << std::endl;
		//std::cout << "3: " << *points[2] << std::endl;


		//std::cout << (*points[1] - *points[0]) << std::endl;
		//std::cout << (*points[2] - *points[0]) << std::endl;

		normal = (*points[1] - *points[0]) % (*points[2] - *points[0]);
		//normal = normal / normal.length();
		//std::cout << "Normal: " << normal << std::endl;
	}
};