#include "CoordinateAxes.h"
#include <GL/glew.h>

// Draws coordinate axes
void CoordinateAxes::draw() {
	glColor3f(0.5, 0.5, 0.5);
	glLineWidth(1);
	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 1);
	glEnd();
}