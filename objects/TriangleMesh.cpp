#include "TriangleMesh.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <GL/glew.h>
#include <GL/glfw.h>

TriangleMesh::TriangleMesh(const std::string& filename, GLfloat scale) : scale(scale) {
	// Measure the loading time
	double t1 = glfwGetTime();

	// Read triangles
	readFromFile(filename);
	calculateNormals();
	
	// Print load time
	double t2 = glfwGetTime();
	std::cout << (t2 - t1) << " seconds" << std::endl << std::endl;
}

TriangleMesh::TriangleMesh(std::vector<std::shared_ptr<Point>> points, std::vector<Triangle> triangles, GLfloat scale)
	: points(points), triangles(triangles), scale(scale)
{
	calculateNormals();
}

void TriangleMesh::readFromFile(const std::string& filename) {
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
		// Q: points[i] = std::make_shared<Point>(x, y, z);
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
	for (auto& t : triangles) {
		// Compute normals for the triangles
		t.calculateNormal();
		// And add them to all of their points
		t.points[0]->normal += t.normal;
		t.points[1]->normal += t.normal;
		t.points[2]->normal += t.normal;
	}
	// Normalize every point's normal
	for (auto& p : points) {
		p->normal.normalize();
	}
}

void TriangleMesh::saveToFile(const std::string& filename) {
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
	for (auto& p : points) {
		file << p->coord.x << " " << p->coord.y << " " << p->coord.z << endl;
	}

	// Output number of triangles
	file << triangles.size() << endl;
	// Output triangles with point indices
	auto pFirst = begin(points);
	auto pLast = end(points);
	for (auto& t : triangles) {
		int p1 = distance(pFirst, find(pFirst, pLast, t.points[0]));
		int p2 = distance(pFirst, find(pFirst, pLast, t.points[1]));
		int p3 = distance(pFirst, find(pFirst, pLast, t.points[2]));
		file << p1 << " " << p2 << " " << p3 << endl;
	}
}

void TriangleMesh::draw() {
	glTranslatef(0, -2, 0);

	// Scale factor for very small models
	glScalef(scale, scale, scale);

	// Draw all triangles
	glBegin(GL_TRIANGLES);
	for (auto& t : triangles) {
		std::shared_ptr<Point> p;
		//glNormal3d(t.normal.x, t.normal.y, t.normal.z);
		p = t.points[0];
		glNormal3d(p->normal.x, p->normal.y, p->normal.z);
		glVertex3d(p->coord.x, p->coord.y, p->coord.z);

		p = t.points[1];
		glNormal3d(p->normal.x, p->normal.y, p->normal.z);
		glVertex3d(p->coord.x, p->coord.y, p->coord.z);

		p = t.points[2];
		glNormal3d(p->normal.x, p->normal.y, p->normal.z);
		glVertex3d(p->coord.x, p->coord.y, p->coord.z);
	}
	glEnd();
}