#include "Mesh.h"
#include <vec3.h>
#include <vector>
#include <GL/glew.h>
#include <iostream>

void setMaterialColor(float r, float g, float b) {
	float dif[4] = {r, g, b, 1};
	float amb[4] = {0.5 * r, 0.5 * g, 0.5 * b, 1};
	//float spe[4] = {0.6, 0.6, 0.6, 1};

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
	//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
}

Mesh::Mesh(void) {
	currentLine = -1;
}


Mesh::~Mesh(void) {
}

void Mesh::newLine() {
	points.push_back(std::vector<Coord>());
	++currentLine;
}

void Mesh::add(double x, double y, double z) {
	Coord a = {x, y, z};
	std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
	points[currentLine].push_back(a);
}

void Mesh::draw() {
	int line, length, i, length2;
	Coord* p1;
	Coord* p2;

	//glColor3d(0, 0, 0);
	glPointSize(4);
	glLineWidth(2);

	// Skip the last element
	for (line = 0, length = points.size() - 1; line < length; ++line) {
		glBegin(GL_QUAD_STRIP);
		for (i = 0, length2 = points[line].size(); i < length2; ++i) {
			p1 = &points[line][i];
			p2 = &points[line + 1][i];
			glVertex3d(p1->x, p1->y, p1->z);
			glVertex3d(p2->x, p2->y, p2->z);
		}
		glEnd();
	}

	//std::vector<Coord>::iterator nextLine;
	//for (auto line = begin(points); line != end(points) - 1; ++line)
	//	auto nextLine = line;
	//	++nextLine;
}
