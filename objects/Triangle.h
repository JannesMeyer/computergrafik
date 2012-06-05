#pragma once
#include "../Point.h"
#include "../RenderObject.h"
#include <vector>
#include <memory>

class Triangle : public RenderObject
{
public:
	std::shared_ptr<Point> points[3];
	Point normal;

	// Constructor
	Triangle(std::shared_ptr<Point> p1, std::shared_ptr<Point> p2, std::shared_ptr<Point> p3, Point normal = Point(0, 0, 0));
	// Destructor
	~Triangle();

	void draw();
};

