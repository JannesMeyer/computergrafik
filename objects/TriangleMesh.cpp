#include "TriangleMesh.h"
#include "GL/glew.h"

TriangleMesh::TriangleMesh(std::vector<Triangle> triangles) : triangles(triangles) {
	// TODO: normalenvektoren berechnen
}

void TriangleMesh::draw() {
	glBegin(GL_TRIANGLES);
	for (auto& triangle : triangles) {
		for (auto& p : triangle.points) {
			glVertex3d(p->x, p->y, p->z);
		}
	}
	glEnd();
}
