#include "BicubicInterpolation.h"
#include <iostream>

BicubicInterpolation::BicubicInterpolation(int width, int height) : xMax(width), yMax(height), numPoints(width * height) {
	currentPoints = 0;
	points.resize(xMax, std::vector<double>(yMax));
}

BicubicInterpolation::~BicubicInterpolation() {
}

void BicubicInterpolation::add(double z) {
	if (currentPoints >= numPoints) {
		throw std::runtime_error("Too many points.");
	}

	++currentPoints;
	int x = (currentPoints - 1) % xMax;
	int y = (currentPoints - 1) / xMax;
	std::cout << "x: " << y << " y: " << x << std::endl;
	//points[x][y] = z;
	points.at(x).at(y) = z;
}

std::shared_ptr<Mesh> BicubicInterpolation::getMesh(int precision) {
	std::shared_ptr<Mesh> mesh(new Mesh);
	int i, j;
	for (i = 0; i < xMax; ++i) {
		mesh->newLine();
		for (j = 0; j < yMax; ++j) {
			mesh->add(i, j, points[i][j]);
		}
	}

	return mesh;
}