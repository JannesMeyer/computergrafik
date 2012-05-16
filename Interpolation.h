#pragma once
#include "LineStrip.h"

#include <vector>
#include <memory>

class Interpolation
{
private:
	std::vector<double> x, y, z;
public:
	Interpolation();
	~Interpolation();
	void add(double x, double y, double z);
	double interpolateLagrange(double t, std::vector<double>* f);
	std::unique_ptr<LineStrip> createLineStrip(int precision); // C++11
};