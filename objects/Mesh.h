#pragma once
#include "../RenderObject.h"
#include "../Point.h"
#include <GL/glew.h>
#include <vector>

class Mesh : public RenderObject
{
private:
	std::vector<std::vector<Point>> points;
	GLfloat width;
	GLuint displayList;
	void initDisplayList();
public:
	Mesh(std::string filename, GLfloat width = 2);
	void draw();
};

