#include "Mesh.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <GL/glew.h>

Mesh::Mesh(std::vector<std::vector<Point>> points, GLfloat width) : points(points), width(width)
{
	// Generate a display list
	displayList = glGenLists(1);
	initDisplayList();
}

Mesh::Mesh(std::string filename, GLfloat width) : width(width)
{
	// Read points from file
	readFromFile(filename);
	// Generate a display list
	displayList = glGenLists(1);
	initDisplayList();
}

void Mesh::readFromFile(std::string filename) { // Q: Should this be called by reference?
	std::ifstream file (filename);
	if (!file) {
		throw std::runtime_error("Unable to open file");
	}

	int zeilen, spalten;
	file >> zeilen;
	file >> spalten;

	std::string line;
	std::getline(file, line); // I don't know why this is necessary

	while (file.good()) {
		// Read one line from the file
		std::getline(file, line);
		// Parse the line using a stringstream
		std::stringstream sstream (line);
		// Create the points and add them to a vector
		std::vector<Point> zeile;
		for (int i = 0; i < spalten; ++i) {
			double value;
			sstream >> value;
			zeile.push_back(Point(i, points.size(), value));
		}
		points.push_back(zeile);
	}
}

void Mesh::initDisplayList() {
	glNewList(displayList, GL_COMPILE);
		glPointSize(width);

		// Skip the last element
		int rows = points.size() - 1;
		int columns = points[0].size();
		for (int y = 0; y < rows; ++y) {
			glBegin(GL_QUAD_STRIP);
			for (int x = 0; x < columns; ++x) {
				Point* p;

				p = &points[y][x];
				glVertex3d(p->coord.x, p->coord.y, p->coord.z);

				p = &points[y + 1][x];
				glVertex3d(p->coord.x, p->coord.y, p->coord.z);
			}
			glEnd();
		}
	glEndList();
}

void Mesh::draw() {
	// Draw this object without lighting, because we didn't calculate normals
	glDisable(GL_LIGHTING);
	glColor3f(0.2f, 0.2f, 0.2f);

	glCallList(displayList);

	glEnable(GL_LIGHTING);
}

std::shared_ptr<TriangleMesh> Mesh::createTriangleMesh() {
	std::vector<Triangle> triangles;

	// Create a copy of all Points as shared pointers
	std::vector<std::vector<std::shared_ptr<Point>>> pointsNew;
	for (auto& zeile : points) {
		std::vector<std::shared_ptr<Point>> zeileNew;
		for (auto& point : zeile) {
			zeileNew.push_back(std::shared_ptr<Point>(new Point(point)));
		}
		pointsNew.push_back(zeileNew);
	}

	// Create triangles
	for (unsigned int i = 0; i < pointsNew.size() - 1; ++i) {
		for (unsigned int j = 0; j < pointsNew[i].size() - 1; ++j) {
			auto p1 = pointsNew[i][j];
			auto p2 = pointsNew[i+1][j+1];
			auto p3 = pointsNew[i+1][j];
			auto p4 = pointsNew[i][j+1];
			// First triangle
			triangles.push_back(Triangle(p1, p2, p3));
			// Second triangle
			triangles.push_back(Triangle(p2, p1, p4));
		}
	}

	// Create a flattened version of the points array
	std::vector<std::shared_ptr<Point>> pointsFlat;
	for (auto& zeile : pointsNew) {
		for (auto& point : zeile) {
			pointsFlat.push_back(point);
		}
	}
	return std::shared_ptr<TriangleMesh>(new TriangleMesh(pointsFlat, triangles));
}

