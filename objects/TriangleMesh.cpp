#include "TriangleMesh.h"
#include "GL/glew.h"
#include <iostream>

TriangleMesh::TriangleMesh(std::vector<std::shared_ptr<Point>> points, std::vector<Triangle> triangles) : points(points), triangles(triangles) {
	// TODO: normalenvektoren berechnen
	//points[8]->z = 6;
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
		glVertex3d(p->x, p->z, p->y);
		
		p = triangle.points[1];
		glVertex3d(p->x, p->z, p->y);

		p = triangle.points[2];
		glVertex3d(p->x, p->z, p->y);
	}
	glEnd();
}