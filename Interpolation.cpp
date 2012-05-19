#include "Interpolation.h"
#include <vec3.h>
#include <cmath>

Interpolation::Interpolation() {
	// Not necessary
	//x = vector<double>();
	//y = vector<double>();
	//z = vector<double>();
}

void Interpolation::add(double newX, double newY, double newZ) {
	// Append the point
	x.push_back(newX);
	y.push_back(newY);
	z.push_back(newZ);
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

std::shared_ptr<LineStrip> Interpolation::createLineStrip(int precision) {
	int i, j;
	const int n = x.size();
	const int numSections = n - 1;

	double t, tLowerBound, tUpperBound;
	Vec3 interpolatedPoint;
	const double tSectionStep = 1.0 / numSections;
	const double tStep = tSectionStep / precision;

	std::shared_ptr<LineStrip> linestrip(new LineStrip); // const?

	// n-1 sections
	for (i = 0; i < numSections; ++i) {
		tLowerBound = tSectionStep * i;
		tUpperBound = tSectionStep * (i + 1);

		// Precision elements in each section
		for (j = 0; j < precision; ++j) {
			// Calculate t
			t = tLowerBound + (j * tStep);
			// Calculate point
			interpolatedPoint = Vec3(interpolateLagrange(t, x),
			                         interpolateLagrange(t, y),
									 interpolateLagrange(t, z));
			// Diesen Punkt hervorheben, wenn es der erste eines Abschnitts ist (j == 0)
			linestrip->add(interpolatedPoint, j == 0);
		}
	}
	// Don't forget the last point t = 1.0
	linestrip->add(Vec3(x.back(), y.back(), z.back()), true);

	return linestrip;
}