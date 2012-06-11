#pragma once
#include "../objects/Mesh.h"
#include <vector>
#include <memory>

class BicubicInterpolation
{
private:
	std::vector<std::vector<double>> points;
	int xMax;
	int yMax;

	void readFromFile(std::string filename);

public:
	BicubicInterpolation(std::vector<std::vector<double>> points);
	BicubicInterpolation(std::string filename);
	double interpolateLagrange(double s, std::vector<double>& f);
	double interpolateLagrange(double s, double t);
	std::shared_ptr<Mesh> createMesh(int precision);
};