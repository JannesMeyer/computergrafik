#pragma once
#include "LineStrip.h"
#include <vector>
using namespace std;

class Interpolation
{
private:
	vector<double> x, y, z;
public:
	Interpolation();
	~Interpolation();
	void add(double x, double y, double z);
	void printContent();
	double interpolateLagrange(double t, vector<double>* f);
	LineStrip&& getLineStrip(int precision); // C++11
};