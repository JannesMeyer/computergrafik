#include "Interpolation.h"
#include <iostream>
#include <vector>
using namespace std;

Interpolation::Interpolation() {
	// Create an empty points vector
	x = vector<double>();
	y = vector<double>();
	z = vector<double>();
}

Interpolation::~Interpolation(void) {
}

double Interpolation::lagrangePolynom(int i) {
	int n = x.size();
	double tStep = 1.0 / n;
	double zaehler = 1;
	double nenner = 1;

	/*
	for (int j = 0; j < n; ++j) {
		if (j == i) { continue; }
		zaehler *= (x - )
	}*/
	return 0;
}

void Interpolation::add(double newX, double newY, double newZ) {
	/*if (points.empty()) {
	throw runtime_error("Number of elements of the appended vector does not match");*/

	// Append the point
	x.push_back(newX);
	y.push_back(newY);
	z.push_back(newZ);
}

LineStrip&& Interpolation::getLineStrip() {
	LineStrip line = LineStrip();
	for (int i = 0, len = x.size(); i < len; ++i) {
		line.add(Vec3(x[i], y[i], z[i]), true);
	}
	return move(line); // C++11: std::move
}

void Interpolation::printContent() {
	for (auto i = begin(x); i != end(x); ++i) {
		cout << *i << " ";
	}
	cout << endl;
	for(auto i = begin(y); i != end(y); ++i) {
		cout << *i << " ";
	}
	cout << endl;
	for(auto i = begin(z); i != end(z); ++i) {
		cout << *i << " ";
	}
	cout << endl;
}