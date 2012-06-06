#pragma once

// A structure that holds a point
struct Point {
	double x, y, z;
	 
	// Constructor
	Point() : x(0), y(0), z(0) {}

	// Constructor
	Point(const double a, const double b, const double c) : x(a), y(b), z(c) {}

	// Copy constructor
	//Point(const Point& p) : x(p.x), y(p.y), z(p.z) {}

	// Cross product
	friend Point operator%(Point& a, Point& b) {
		double x, y, z;
		x = a.y * b.z - a.z * b.y;
		y = a.z * b.x - a.x * b.z;
		z = a.x * b.y - a.y * b.x;
		return Point(x, y, z);
	}
};