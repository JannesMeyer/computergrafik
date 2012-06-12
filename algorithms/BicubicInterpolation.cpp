#include "BicubicInterpolation.h"
#include <fstream>
#include <sstream>

BicubicInterpolation::BicubicInterpolation(std::vector<std::vector<double>> points) : points(points)
{
	xMax = points[0].size();
	yMax = points.size();
}

BicubicInterpolation::BicubicInterpolation(std::string filename) {
	readFromFile(filename);
	xMax = points[0].size();
	yMax = points.size();
}

void BicubicInterpolation::readFromFile(std::string filename) {
	std::ifstream file (filename);
	if (!file) {
		throw std::runtime_error("Unable to open file");
	}

	int zeilen, spalten;
	file >> zeilen;
	file >> spalten;

	std::string line;
	std::getline(file, line); // I don't know why this is necessary

	while (file.good()) {
		// Read one line from the file
		std::getline(file, line);
		// Parse the line using a stringstream
		std::stringstream sstream (line);
		// Add the values to a row vector
		std::vector<double> row;
		for (int i = 0; i < spalten; ++i) {
			double value;
			sstream >> value;
			row.push_back(value);
		}
		points.push_back(row);
	}
}

// Calculate lagrange polynomial using the other interpolation function
double BicubicInterpolation::interpolateLagrange(double s, double t) {
	double result = 0;
	result += interpolateLagrange(s, points[0]) * (-9.0/2 * pow(t, 3) + 9.0 * pow(t, 2) - 11.0/2 * t + 1);
	result += interpolateLagrange(s, points[1]) * (27.0/2 * pow(t, 3) - 45.0/2 * pow(t, 2) + 9.0 * t);
	result += interpolateLagrange(s, points[2]) * (-27.0/2 * pow(t, 3) + 18.0 * pow(t, 2) - 9.0/2 * t);
	result += interpolateLagrange(s, points[3]) * (9.0/2 * pow(t, 3) - 9.0/2 * pow(t, 2) + t);
	return result;
}

// Calculate lagrange polynomial using a vector
double BicubicInterpolation::interpolateLagrange(double s, std::vector<double>& f) {
	double result = 0;
	result += f[0] * (-9.0/2 * pow(s, 3) + 9.0 * pow(s, 2) - 11.0/2 * s + 1);
	result += f[1] * (27.0/2 * pow(s, 3) - 45.0/2 * pow(s, 2) + 9.0 * s);
	result += f[2] * (-27.0/2 * pow(s, 3) + 18.0 * pow(s, 2) - 9.0/2 * s);
	result += f[3] * (9.0/2 * pow(s, 3) - 9.0/2 * pow(s, 2) + s);
	return result;
}

// Create an interpolated Mesh
std::shared_ptr<Mesh> BicubicInterpolation::createMesh(int precision) {
	std::vector<std::vector<Point>> points;
	double stepSize = 1.0 / precision;

	for (double s = 0; s < 1.0; s += stepSize) {
		std::vector<Point> row;
		for (double t = 0; t < 1.0; t += stepSize) {
			// Now we have values for s and t that correspond to positions on the grid, so we can calculate x, y, and z
			row.emplace_back(s * 4,
			                 interpolateLagrange(s, t),
			                 t * 4);
		}
		points.push_back(row);
	}

	return std::make_shared<Mesh>(points);
}