#pragma once
#include "objects/LineStrip.h"

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
	double interpolateLagrange(double t, std::vector<double>& f); // call by reference
	std::shared_ptr<LineStrip> createLineStrip(int precision); // C++11: shared pointer
};