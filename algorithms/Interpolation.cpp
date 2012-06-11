#include "Interpolation.h"
#include "../Vector.h"
#include <cmath>

Interpolation::Interpolation(std::vector<vec3> points) : points(points)
{
	// Create separate vectors for each coord
	for (auto& p : points) {
		x.push_back(p.x);
		y.push_back(p.y);
		z.push_back(p.z);
	}
}

// Calculate lagrange polynomials
double Interpolation::interpolateLagrange(double t, std::vector<double>& f) {
	double result = 0;
	// L0
	result += f[0] * (-9.0/2 * pow(t, 3) + 9.0 * pow(t, 2) - 11.0/2 * t + 1);
	// L1
	result += f[1] * (27.0/2 * pow(t, 3) - 45.0/2 * pow(t, 2) + 9.0 * t);
	// L2
	result += f[2] * (-27.0/2 * pow(t, 3) + 18.0 * pow(t, 2) - 9.0/2 * t);
	// L3
	result += f[3] * (9.0/2 * pow(t, 3) - 9.0/2 * pow(t, 2) + t);
	return result;
}

std::shared_ptr<LineStrip> Interpolation::createLineStrip(int precision, Color color) {
	const int n = x.size();
	const int numSections = n - 1;

	const double tSectionStep = 1.0 / numSections;
	const double tStep = tSectionStep / precision;

	std::vector<vec3> linepoints;

	// Go through each of the n-1 sections
	for (int i = 0; i < numSections; ++i) {
		double tLowerBound = tSectionStep * i;
		double tUpperBound = tSectionStep * (i + 1);

		// Create as many elements in each section as the precision dictates
		for (int j = 0; j < precision; ++j) {
			// Calculate t
			double t = tLowerBound + (j * tStep);
			// Calculate point
			linepoints.emplace_back(interpolateLagrange(t, x),
			                        interpolateLagrange(t, y),
			                        interpolateLagrange(t, z));
		}
	}
	// Don't forget the last point t = 1.0
	linepoints.emplace_back(points.back());

	return std::make_shared<LineStrip>(linepoints, color);
}