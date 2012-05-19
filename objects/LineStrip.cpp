#include "LineStrip.h"

LineStrip::LineStrip(GLfloat width) : width(width) {
	readonly = false;
	displayList = glGenLists(1);
}

void LineStrip::add(Vec3 newPoint, bool highlight) {
	if (readonly) {
		throw std::runtime_error("This object is read-only.");
	}
	// Add the values to the points vector as a pair
	points.emplace_back(newPoint, highlight); // C++11
}

void LineStrip::initDisplayList() {
	readonly = true;

	glNewList(displayList, GL_COMPILE);
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
	glEndList();
}

void LineStrip::draw() {
	if (!readonly) {
		initDisplayList();
	}
	glCallList(displayList);
}