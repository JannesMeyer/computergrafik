#pragma once
#include "LineStrip.h"
#include <vec3.h>
#include <vector>
using namespace std;

class Interpolation
{
private:
	//vector<Vec3> points;
	vector<double> x, y, z;
public:
	Interpolation();
	~Interpolation();
	double lagrangePolynom(int i);
	void add(double x, double y, double z);
	LineStrip&& getLineStrip(); // C++11
	void printContent();
};