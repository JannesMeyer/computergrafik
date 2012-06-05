#include "Triangle.h"
#include <iostream>

Triangle::Triangle(std::shared_ptr<Point> p1, std::shared_ptr<Point> p2, std::shared_ptr<Point> p3, Point normal) : normal(normal) {
	points[0] = p1;
	points[1] = p2;
	points[2] = p3;
	std::cout << "Constructor Triangle" << std::endl;
}

Triangle::~Triangle() {
	std::cout << "Destructor Triangle" << std::endl;
}

void Triangle::draw() {

}