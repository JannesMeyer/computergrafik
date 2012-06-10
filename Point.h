#pragma once
#include <string>
#include <cmath>
#include <cassert>
#include <iostream>

// A structure that holds a point
struct Point {
	double x, y, z;
	// ...and optionally a normal
	double normalX, normalY, normalZ;
	 
	// Constructor
	Point() : x(0), y(0), z(0), normalX(0), normalY(0), normalZ(0) {}

	// Constructor
	Point(const double a, const double b, const double c) : x(a), y(b), z(c), normalX(0), normalY(0), normalZ(0) {}

	// Copy constructor
	//Point(const Point& p) : x(p.x), y(p.y), z(p.z) {}

	// Cross product
	static friend Point operator%(Point& a, Point& b) {
		double x, y, z;
		x =  (a.y * b.z) - (a.z * b.y);
		y = -(a.x * b.z) + (a.z * b.x);
		z =  (a.x * b.y) - (a.y * b.x);
		return Point(x, y, z);
	}

	// Addition
	static friend Point operator+(Point& a, Point& b) {
		return Point(a.x + b.x,
		             a.y + b.y,
					 a.z + b.z);
	}
	Point operator+=(Point& a) {
		x += a.x;
		y += a.y;
		z += a.z;
		return *this;
	}

	// Subtraction
	static friend Point operator-(Point& a, Point& b) {
		return Point(a.x - b.x,
		             a.y - b.y,
		             a.z - b.z);
	}

	// Division
	static friend Point operator/(Point& p, double denominator) {
		assert(denominator != 0.0);
		double x = p.x / denominator;
		double y = p.y / denominator;
		double z = p.z / denominator;
		return Point(x, y, z);
	}
	
	// Make the point printable
	static friend std::ostream& operator<<(std::ostream& out, const Point& p) {
		return out << "( " << p.x << ", " << p.y << ", " << p.z << " )";
	}

	// Compute the length
	double length() {
		return sqrt(x*x + y*y + z*z);
	}
};