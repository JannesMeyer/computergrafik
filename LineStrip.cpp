#include "LineStrip.h"
#include <gl/glew.h>

LineStrip::LineStrip(GLfloat width) : width(width) {
	points = new vector<Vec3>();
	highlights = new vector<bool>();
}


LineStrip::~LineStrip() {
}

void LineStrip::add(Vec3 newPoint, bool highlight) {
	points->push_back(newPoint);
	highlights->push_back(highlight);
}

void LineStrip::draw() {
	// Draw lines
	glColor3f(0, 0, 0);
	glLineWidth(width);
	glBegin(GL_LINE_STRIP);
	for (auto &point : *points) {
		glVertex3dv(point.p);
	}
	glEnd();

	// Draw markers
	glColor3f(1, 0, 0);
	glPointSize(width * 4);
	glBegin(GL_POINTS);
	for (auto &point : *points) {
		glVertex3dv(point.p);
	}
	glEnd();
}