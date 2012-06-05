#include "TriangleMesh.h"
#include "GL/glew.h"
#include <iostream>

TriangleMesh::TriangleMesh(std::vector<std::shared_ptr<Point>> points, std::vector<Triangle> triangles) : points(points), triangles(triangles) {
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
		glVertex3d(p->x, p->z, p->y);
		
		p = triangle.points[1];
		glVertex3d(p->x, p->z, p->y);

		p = triangle.points[2];
		glVertex3d(p->x, p->z, p->y);
	}
	glEnd();
	// Some stupid test animation
	auto z = &points[8]->z;
	*z += 0.01;
	if (*z > 6) { *z = 2; }
}

void TriangleMesh::saveToFile(std::string filename) {
	// Use the STL namespace this time
	using namespace std;

	cout << endl << "Dateiausgabe: '" << filename << "'" << endl;
	cout << points.size() << endl;
	for (auto& point : points) {
		cout << point->x << " " << point->y << " " << point->z << endl;
	}
	// Find all triangles
	auto pFirst = begin(points);
	auto pLast = end(points);
	int p1, p2, p3;
	
	cout << triangles.size() << endl;
	for (auto& triangle : triangles) {
		p1 = distance(pFirst, find(pFirst, pLast, triangle.points[0]));
		p2 = distance(pFirst, find(pFirst, pLast, triangle.points[1]));
		p3 = distance(pFirst, find(pFirst, pLast, triangle.points[2]));
		cout << p1 << " " << p2 << " " << p3 << endl;
	}
}