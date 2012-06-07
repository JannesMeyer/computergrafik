#include "TriangleMesh.h"
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include <GL/glfw.h>

TriangleMesh::TriangleMesh(std::vector<std::shared_ptr<Point>> points, std::vector<Triangle> triangles) : points(points), triangles(triangles) {
	calculateNormals();
}

TriangleMesh::TriangleMesh(std::string filename) {
	double t1 = glfwGetTime();
	readFromFile(filename);
	double t2 = glfwGetTime();
	std::cout << (t2 - t1) << " seconds" << std::endl;
	calculateNormals();
}

void TriangleMesh::readFromFile(std::string filename) {
	std::ifstream file (filename);
	if (!file) {
		throw std::runtime_error("Unable to open file");
	}

	// Read #points
	unsigned int num;
	file >> num;
	points.reserve(num);
	// Read points
	std::cout << "Reading points" << std::endl;
	for (unsigned int i = 0; i < num; ++i) {
		if (!file.good()) {
			throw std::runtime_error("Unexpected end of file");
		}
		double x, y, z;
		file >> x >> y >> z;
		points.push_back(std::make_shared<Point>(x, y, z));
		//points[i] = std::make_shared<Point>(x, y, z);
	}

	// Read #triangles
	file >> num;
	triangles.reserve(num);
	// Read triangles
	std::cout << "Reading triangles" << std::endl;
	for (unsigned int i = 0; i < num; ++i) {
		if (!file.good()) {
			throw std::runtime_error("Unexpected end of file");
		}
		int p1, p2, p3;
		file >> p1 >> p2 >> p3;
		triangles.push_back(Triangle(points[p1], points[p2], points[p3]));
	}
}

void TriangleMesh::calculateNormals() {
	std::cout << "Calculating normals" << std::endl;
	// TODO
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
	file << triangles.size() << endl;
	// Output triangles with point indices
	auto pFirst = begin(points);
	auto pLast = end(points);
	for (auto& triangle : triangles) {
		int p1 = distance(pFirst, find(pFirst, pLast, triangle.points[0]));
		int p2 = distance(pFirst, find(pFirst, pLast, triangle.points[1]));
		int p3 = distance(pFirst, find(pFirst, pLast, triangle.points[2]));
		file << p1 << " " << p2 << " " << p3 << endl;
	}
}

void TriangleMesh::draw() {
	glScalef(100, 100, 100);
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
}