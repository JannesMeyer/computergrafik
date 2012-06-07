#include "TriangleMesh.h"
#include "GL/glew.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glfw.h>

TriangleMesh::TriangleMesh(std::vector<std::shared_ptr<Point>> points, std::vector<Triangle> triangles) : points(points), triangles(triangles) {
	calculateNormals();
}

TriangleMesh::TriangleMesh(std::string filename) {
	readFromFile(filename);
	calculateNormals();
}

void TriangleMesh::calculateNormals() {
	std::cout << "Calculating normals" << std::endl;
	// TODO
}

void TriangleMesh::readFromFile(std::string filename) {
	std::ifstream file (filename);
	std::string line;
	std::stringstream sstream;
	unsigned int num;

	if (!file) {
		throw std::runtime_error("Unable to open file");
	}

	// Read #points
	file >> num;
	
	double t1 = glfwGetTime();

	// Read points
	std::cout << "Reading points" << std::endl;
	for (unsigned int i = 0; i < num; ++i) {
		if (!file.good()) {
			throw std::runtime_error("Unexpected end of file");
		}

		double x, y, z;
		file >> x >> y >> z;
		points.push_back(std::make_shared<Point>(x, y, z));
	}
	double t2 = glfwGetTime();
	std::cout << (t2-t1) << std::endl;

	// Read #triangles
	file >> num;

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
	int p1, p2, p3;
	for (auto& triangle : triangles) {
		p1 = distance(pFirst, find(pFirst, pLast, triangle.points[0]));
		p2 = distance(pFirst, find(pFirst, pLast, triangle.points[1]));
		p3 = distance(pFirst, find(pFirst, pLast, triangle.points[2]));
		file << p1 << " " << p2 << " " << p3 << endl;
	}
}

void TriangleMesh::draw() {
	// Draw all triangles
	glScalef(100, 100, 100);
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
	//auto z = &points[8]->z;
	//*z += 0.01;
	//if (*z > 6) { *z = 2; }
}