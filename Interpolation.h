#pragma once
#include "LineStrip.h"
#include <vec3.h>
#include <vector>
using namespace std;

class Interpolation
{
private:
	vector<Vec3> points;
	int numCoordinates;
public:
	Interpolation();
	Interpolation(vector<Vec3> points);
	~Interpolation();
	void printContent();
	void add(double x, double y, double z);
	LineStrip&& getLineStrip(); // C++11
};