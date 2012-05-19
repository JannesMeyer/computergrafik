#include "BicubicInterpolation.h"

BicubicInterpolation::BicubicInterpolation(int width, int height) : xMax(width), yMax(height), numPoints(width * height) {
	currentPoints = 0;
	points.resize(xMax, std::vector<double>(yMax));
}

void BicubicInterpolation::add(double z) {
	if (currentPoints >= numPoints) {
		throw std::runtime_error("Too many points.");
	}

	++currentPoints;
	int x = (currentPoints - 1) % xMax;
	int y = (currentPoints - 1) / xMax;

	//points[x][y] = z;
	points.at(x).at(y) = z;
}

// Calculate lagrange polynomials with a vector
double BicubicInterpolation::interpolateLagrange(double s, std::vector<double>& f) {
	double result = 0;
	result += f[0] * (-9.0/2 * pow(s, 3) + 9.0 * pow(s, 2) - 11.0/2 * s + 1);
	result += f[1] * (27.0/2 * pow(s, 3) - 45.0/2 * pow(s, 2) + 9.0 * s);
	result += f[2] * (-27.0/2 * pow(s, 3) + 18.0 * pow(s, 2) - 9.0/2 * s);
	result += f[3] * (9.0/2 * pow(s, 3) - 9.0/2 * pow(s, 2) + s);
	return result;
}

double BicubicInterpolation::interpolateLagrange(double s, double t) {
	double result = 0;
	result += interpolateLagrange(s, points[0]) * (-9.0/2 * pow(t, 3) + 9.0 * pow(t, 2) - 11.0/2 * t + 1);
	result += interpolateLagrange(s, points[1]) * (27.0/2 * pow(t, 3) - 45.0/2 * pow(t, 2) + 9.0 * t);
	result += interpolateLagrange(s, points[2]) * (-27.0/2 * pow(t, 3) + 18.0 * pow(t, 2) - 9.0/2 * t);
	result += interpolateLagrange(s, points[3]) * (9.0/2 * pow(t, 3) - 9.0/2 * pow(t, 2) + t);
	return result;
}

std::shared_ptr<Mesh> BicubicInterpolation::createMesh(int precision) {
	std::shared_ptr<Mesh> mesh(new Mesh);
	double s, t;

	for (s = 0; s < 1.0; s += 0.02) {
		mesh->newLine();
		for (t = 0; t < 1.0; t += 0.02) {
			// Now we have values for s and t that correspond to positions on the grid
			// Calculate x, y, and z
			mesh->add(s * 4, t * 4, interpolateLagrange(s, t));
		}
	}

	return mesh;
}