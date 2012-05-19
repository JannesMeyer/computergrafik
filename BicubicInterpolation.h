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
	void add(double z);
	double interpolateLagrange(double s, std::vector<double>& f);
	double interpolateLagrange(double s, double t);
	std::shared_ptr<Mesh> createMesh(int precision);
};