#pragma once
#include "objects/Mesh.h"
#include <vector>
#include <memory>

class BicubicInterpolation
{
private:
	std::vector<std::vector<double>> points;
	int xMax;
	int yMax;
	const int numPoints;
	int currentPoints;
public:
	BicubicInterpolation(int width, int height);
	~BicubicInterpolation();
	void add(double z);
	std::shared_ptr<Mesh> getMesh(int precision);
};