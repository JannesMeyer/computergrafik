#include "LineStrip.h"

LineStrip::LineStrip(std::vector<Point> points, Color color, GLfloat width) : points(points), width(width), color(color) {
	// Set the default polygon mode
	mode = GL_FILL;
}

void LineStrip::draw() {
	// Set color
	glColor3f(color.r, color.g, color.b);

	// Begin drawing
	if (mode == GL_POINT) {
		glPointSize(width * 4);
		glBegin(GL_POINTS);
	} else {
		glLineWidth(width * 2);
		glBegin(GL_LINE_STRIP);
	}

	// Draw lines
	for (auto& point : points) {
		glVertex3d(point.x, point.y, point.z);
	}
	glEnd();
}