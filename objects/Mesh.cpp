#include "Mesh.h"
#include <vec3.h>
#include <GL/glew.h>

Mesh::Mesh(GLfloat width) : width(width), readonly(false), currentLine(-1)
{
	displayList = glGenLists(1);
}

void Mesh::newLine() {
	points.push_back(std::vector<Coord>());
	++currentLine;
}

void Mesh::add(double x, double y, double z) {
	if (readonly) {
		throw std::runtime_error("This object is read-only.");
	}

	Coord newPoint = {x, y, z};
	points[currentLine].push_back(newPoint);
}

void Mesh::initDisplayList() {
	readonly = true;

	glNewList(displayList, GL_COMPILE);
		glColor3f(0, 0, 0);
		glPointSize(width);
		glBegin(GL_POINTS);
		for (auto& line : points) {
			for (auto& point : line) {
				glVertex3d(point.x, point.z, point.y);
			}
		}
		glEnd();
	glEndList();
}

/*
void Mesh::draw() {
	int line, len, i, len2;
	Coord* p1;
	Coord* p2;

	glPointSize(4);
	glLineWidth(2);

	// Skip the last element
	for (line = 0, len= points.size() - 1; line < len; ++line) {
		glBegin(GL_QUAD_STRIP);
		for (i = 0, len2 = points[line].size(); i < len2; ++i) {
			p1 = &points[line][i];
			p2 = &points[line + 1][i];
			glVertex3d(p1->x, p1->z, p1->y);
			glVertex3d(p2->x, p2->z, p2->y);
		}
		glEnd();
	}

	//std::vector<Coord>::iterator nextLine;
	//for (auto line = begin(points); line != end(points) - 1; ++line)
	//	auto nextLine = line;
	//	++nextLine;
}
*/

void Mesh::draw() {
	if (!readonly) {
		initDisplayList();
	}
	glCallList(displayList);
}