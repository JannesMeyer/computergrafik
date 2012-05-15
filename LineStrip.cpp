#include "LineStrip.h"
#include <gl/glew.h>

LineStrip::LineStrip(GLfloat width) : width(width) {
	points = new vector<Vec3>();
}


LineStrip::~LineStrip() {
}

void LineStrip::add(Vec3 newPoint, bool highlight) {
	points->push_back(newPoint);
}

void LineStrip::draw() {
	glColor3f(0, 0, 0);
	glLineWidth(width);
	glBegin(GL_LINE_STRIP);
	for (auto i = begin(*points); i != end(*points); ++i) {
		glVertex3dv(i->p);
	}
	glEnd();

	glColor3f(0.9f, 0, 0);
	glPointSize(width * 4);
	glBegin(GL_POINTS);
	for (auto i = begin(*points); i != end(*points); ++i) {
		glVertex3dv(i->p);
	}
	glEnd();
}