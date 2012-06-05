#include "TriangleMesh.h"
#include "GL/glew.h"
#include <fstream>
#include <iostream>

TriangleMesh::TriangleMesh(std::vector<std::shared_ptr<Point>> points, std::vector<Triangle> triangles) : points(points), triangles(triangles) {
	// TODO: normalenvektoren berechnen
}

void TriangleMesh::draw() {
	// Draw all triangles
	glBegin(GL_TRIANGLES);
	for (auto& triangle : triangles) {
		std::shared_ptr<Point> p;

		p = triangle.points[0];
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
	// Open the file for writing
	ofstream file (filename);

	if (!file) {
		throw std::runtime_error("Unable to open file");
	}
	cout << "Writing '" << filename << "'" << endl;

	// Output number of points
	file << points.size() << endl;
	// Output points
	for (auto& point : points) {
		file << point->x << " " << point->y << " " << point->z << endl;
	}

	// Output number of triangles
	file << endl << triangles.size() << endl;
	// Output triangles with point indices
	auto pFirst = begin(points);
	auto pLast = end(points);
	int p1, p2, p3;
	for (auto& triangle : triangles) {
		p1 = distance(pFirst, find(pFirst, pLast, triangle.points[0]));
		p2 = distance(pFirst, find(pFirst, pLast, triangle.points[1]));
		p3 = distance(pFirst, find(pFirst, pLast, triangle.points[2]));
		file << p1 << " " << p2 << " " << p3 << endl;
	}
}