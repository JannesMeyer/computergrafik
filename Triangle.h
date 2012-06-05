#pragma once
#include "Point.h"
#include <vector>
#include <memory>

struct Triangle
{
public:
	std::vector<std::shared_ptr<Point>> points;
	Point normal;
	Triangle(std::vector<std::shared_ptr<Point>> points, Point normal = Point(0, 0, 0));
};

