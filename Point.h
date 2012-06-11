#pragma once
#include "Vector.h"
// Q: Why not "Vector"?

/*
 * Simple Point class that contains 3-dimensional coordinates and a normal vector
 * Author: Jannes Meyer
 */
struct Point {
	vec3 coord; // initialized with zeros
	vec3 normal;
	
	// Constructor
	Point() {}
	Point(vec3 v) : coord(v) {} // Q: Why not "const vec3 v"?
	Point(double x, double y, double z) {
		coord.x = x;
		coord.y = y;
		coord.z = z;
	}
	// Copy constructor (Q: What's this useful for?)
	/*Point(const Point& p) : x(p.x), y(p.y), z(p.z) {}*/
};