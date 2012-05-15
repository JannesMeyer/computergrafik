#include "Interpolation.h"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

Interpolation::Interpolation() {
	// Create empty points vectors
	x = vector<double>();
	y = vector<double>();
	z = vector<double>();
}

Interpolation::~Interpolation(void) {
}

void Interpolation::add(double newX, double newY, double newZ) {
	/*if (points.empty()) {
	throw runtime_error("Number of elements of the appended vector does not match");*/

	// Append the point
	x.push_back(newX);
	y.push_back(newY);
	z.push_back(newZ);
}

void Interpolation::printContent() {
	for (auto value : x) {
		cout << value << " ";
	}
	cout << endl;
	for(auto value : y) {
		cout << value << " ";
	}
	cout << endl;
	for(auto value : z) {
		cout << value << " ";
	}
	cout << endl;
}

// Calculate lagrange polynomials
double Interpolation::interpolateLagrange(double t, vector<double> f) {
	/*
	double zaehler = 1;
	double nenner = 1;
	
	for (int j = 0; j < n; ++j) {
		if (j == i) { continue; }
		zaehler *= (x - )
	}*/

	double result = 0;
	// L0
	result += f[0] + (-9.0/2 * pow(t, 3) + 9.0 * pow(t, 2) - 11.0/2 * t + 1);
	// L1
	result += f[1] + (27.0/2 * pow(t, 3) - 45.0/2 * pow(t, 2) + 9.0 * t);
	// L2
	result += f[2] + (-27.0/2 * pow(t, 3) + 18.0 * pow(t, 2) - 9.0/2 * t);
	// L3
	result += f[3] + (9.0/2 * pow(t, 3) - 9.0/2 * pow(t, 2) + t);
	return result;
}

LineStrip&& Interpolation::getLineStrip(int precision) {
	LineStrip line = LineStrip();

	int n = x.size(), i, j;
	double t, tLowerBound, tUpperBound;
	double tStep = 1.0 / ((n - 1) * precision);
	double xt, yt, zt;
	
	// n-1 Abschnitte
	for (i = 0; i < (n-1); ++i) {
		tLowerBound = ((double) i) / (n - 1);
		tUpperBound = ((double) (i + 1)) / (n - 1);

		// Abschnitt Berechnen
		for (j = 0; j < precision; ++j) {
			// Calculate t
			t = tLowerBound + (j * tStep);
			if (j == 0) {
				// Erster Punkt eines Abschnitts
			}
			cout << "Current t: " << t << " (" << j << ")" << endl;
		}
	}
	// Letzter Punkt
	t = 1.0;
	cout << "Last t: " << t << endl;

	
	for (int i = 0, len = x.size(); i < len; ++i) {
		line.add(Vec3(x[i], y[i], z[i]), true);
	}
	return move(line); // C++11: std::move
}