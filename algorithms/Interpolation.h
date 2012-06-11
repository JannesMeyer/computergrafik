#pragma once
#include "../objects/LineStrip.h"
#include "../Color.h"
#include <vector>
#include <memory>

class Interpolation
{
private:
	std::vector<double> x, y, z;
	std::vector<vec3> points;
public:
	Interpolation(std::vector<vec3> points);
	double interpolateLagrange(double t, std::vector<double>& f); // call by reference
	std::shared_ptr<LineStrip> createLineStrip(int precision, Color color); // C++11: shared pointer
};