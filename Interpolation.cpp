#include "Interpolation.h"
#include <iostream>
#include <vector>
using namespace std;

Interpolation::Interpolation() {
	// Create an empty points vector
	points = vector<Vec3>();
	numCoordinates = 0;
}

Interpolation::Interpolation(vector<Vec3> points) : points(points) {
	numCoordinates = points.size();
}


Interpolation::~Interpolation(void) {
}

void Interpolation::add(double x, double y, double z) {
	// Is this the first element added?
	if (points.empty()) {
		numCoordinates = 3;
	} else if (numCoordinates != 3) {
		throw runtime_error("Number of elements of the appended vector does not match");
	}
	// Append the point as Vec3
	points.push_back(Vec3(x, y, z));
}

LineStrip&& Interpolation::getLineStrip() {
	LineStrip line = LineStrip();
	for (auto i = begin(points); i != end(points); ++i) { // C++11: non-member begin() and end()
		line.add(*i);
	}
	return move(line); // C++11: std::move
}

void Interpolation::printContent() {
	/*for (auto i = begin(points); i != end(points); ++i) {
		Vec3 point = (Vec3)*i;
		int length = sizeof point;
		for (int j = 0; j < length; ++j) {
			cout <<  << endl;
		}
	}*/
	vector<Vec3>::size_type i;
	for(i = 0; i != points.size(); i++) {
		cout << points[i].p[0] << " ";
	}
	cout << endl;

	for(i = 0; i != points.size(); i++) {
		cout << points[i].p[1] << " ";
	}
	cout << endl;

	for(i = 0; i != points.size(); i++) {
		cout << points[i].p[2] << " ";
	}
	cout << endl;
}