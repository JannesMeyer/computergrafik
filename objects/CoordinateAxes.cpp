#include "CoordinateAxes.h"

#include <GL/glew.h>

// Draws coordinate axes
void CoordinateAxes::draw() {
	// Disable lighting and depth test
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	// Draw axes
	glColor3f(0.5f, 0.5f, 0.5f);
	glLineWidth(1);
	glBegin(GL_LINES);
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 1);
	glEnd();

	// Disable lighting and depth test
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}