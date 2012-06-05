#include "TriangleMesh.h"
#include "GL/glew.h"
#include <iostream>

TriangleMesh::TriangleMesh(std::vector<Triangle> triangles) : triangles(triangles) {
	// TODO: normalenvektoren berechnen
	std::cout << "Constructor TriangleMesh" << std::endl;
}

TriangleMesh::~TriangleMesh() {
	std::cout << "Destructor TriangleMesh" << std::endl;
}

void TriangleMesh::draw() {
	// Draw all triangles
	glBegin(GL_TRIANGLES);
	for (auto& triangle : triangles) {
		auto p = triangle.points[0];
		glVertex3d(p->x, p->y, p->z);
		
		p = triangle.points[1];
		glVertex3d(p->x, p->y, p->z);

		p = triangle.points[2];
		glVertex3d(p->x, p->y, p->z);
	}
	glEnd();
}
