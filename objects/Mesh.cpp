#include "Mesh.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <GL/glew.h>

//Mesh("dateiname.txt", 2)

Mesh::Mesh(std::string filename, GLfloat width) : width(width) {
	int zeilen, spalten;
	std::ifstream file;
	std::string line; // Cloaks the global variable "line", but who cares

	file.open(filename);

	if (!file) {
		throw std::runtime_error("Unable to open file");
	}

	file >> zeilen;
	file >> spalten;
	// I don't know why this is necessary
	std::getline(file, line);

	// Read all lines
	while (file.good()) {
		// Read one line from the file
		std::getline(file, line);
		// Parse the line using a stringstream
		std::stringstream sstream (line);
		std::vector<Point> zeile;
		double value;
		for (int i = 0; i < spalten; ++i) {
			sstream >> value;
			zeile.push_back(Point(i, points.size(), value));
		}
		points.push_back(zeile);
	}

	// Generate a display list
	displayList = glGenLists(1);
	initDisplayList();
}

void Mesh::initDisplayList() {
	int line, len, i, len2;
	Point* p1;
	Point* p2;

	glNewList(displayList, GL_COMPILE);
		glPointSize(width);

		// Skip the last element
		for (line = 0, len = points.size() - 1; line < len; ++line) {
			glBegin(GL_QUAD_STRIP);
			for (i = 0, len2 = points[line].size(); i < len2; ++i) {
				p1 = &points[line][i];
				p2 = &points[line + 1][i];
				glVertex3d(p1->x, p1->z, p1->y);
				glVertex3d(p2->x, p2->z, p2->y);
			}
			glEnd();
		}
	glEndList();
}

void Mesh::draw() {
	glCallList(displayList);
}

std::shared_ptr<TriangleMesh> Mesh::createTriangleMesh() {
	std::vector<Triangle> triangles;

	for (unsigned int i = 0; i < points.size() - 1; ++i) {
		std::vector<std::shared_ptr<Point>> triangle1;
		triangle1.push_back(std::shared_ptr<Point>(&points[i][0]));
		triangle1.push_back(std::shared_ptr<Point>(&points[i+1][0+1]));
		triangle1.push_back(std::shared_ptr<Point>(&points[i+1][0]));
		// Add the triangle to the list
		triangles.push_back(triangle1);

		//std::vector<std::shared_ptr<Point>> triangle2;
		//triangle2.emplace_back(points[i+1][0+1]);
		//triangle2.emplace_back(points[i][0]);
		//triangle2.emplace_back(points[i][0+1]);
		//triangles.push_back(triangle2);
	}

	return std::shared_ptr<TriangleMesh>(new TriangleMesh(triangles));
}