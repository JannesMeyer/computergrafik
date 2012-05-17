#include "LineStrip.h"

#include <iostream>

LineStrip::LineStrip(GLfloat width) : width(width) {
	//points = std::vector<std::pair<Vec3, bool>>(); // Wird nicht ben�tigt
}

LineStrip::~LineStrip() {
}

void LineStrip::add(Vec3 newPoint, bool highlight) {
#ifdef _DEBUG
	if (highlight) { std::cout << "Sample point: "; }
	newPoint.Print();
#endif

	// Add the values to the points vector as a pair
	points.emplace_back(newPoint, highlight); // C++11
}

void LineStrip::draw() {
	// Draw lines
	glColor3f(0, 0, 0);
	glLineWidth(width);
	glBegin(GL_LINE_STRIP);
	for (auto& point : points) {
		glVertex3dv(point.first.p);
	}
	glEnd();

	// Draw markers
	glColor3f(1, 0, 0);
	glPointSize(width * 4);
	glBegin(GL_POINTS);
	for (auto& point : points) {
		// If highlight is true for this point
		if (point.second) {
			glVertex3dv(point.first.p);
		}
	}
	glEnd();
}