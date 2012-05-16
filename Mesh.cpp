#include "Mesh.h"
#include <vec3.h>
#include <vector>
#include <GL/glew.h>
using namespace std;


Mesh::Mesh(void)
{
	//points = new double[3][3];
	stepX = 2;
	stepY = 2;
}


Mesh::~Mesh(void)
{
}

void Mesh::add(int xpos, int ypos, double z) {
	points[xpos][ypos] = z;
}

void Mesh::draw() {
	int i, j, len;

	glColor3d(0, 0, 0);
	glPointSize(4);
	glLineWidth(2);
	for (i = 0, len = 3; i < len; ++i) {
		glBegin(GL_LINE_STRIP);
		for (j = 0, len = 3; j < len; ++j) {
			glVertex3d(i * stepX, points[i][j], j * stepY);
		}
		glEnd();
		glBegin(GL_LINE_STRIP);
		for (j = 0, len = 3; j < len; ++j) {
			glVertex3d(j * stepY, points[i][j], i * stepX);
		}
		glEnd();
	}
	
}
