#pragma once
#include "../RenderObject.h"
#include "../Point.h"
#include "TriangleMesh.h"
#include <GL/glew.h>
#include <vector>


class Mesh : public RenderObject
{
private:
	std::vector<std::vector<Point>> points;
	GLfloat width;
	GLuint displayList;

	void readFromFile(std::string filename);
	void initDisplayList();
public:
	Mesh(std::string filename, GLfloat width = 1);
	void draw();
	std::shared_ptr<TriangleMesh> createTriangleMesh();
};

