#pragma once
#include "../RenderObject.h"
#include <GL/glew.h>
#include <vector>

struct Coord {
	double x;
	double y;
	double z;
};

class Mesh : public RenderObject
{
private:
	std::vector<std::vector<Coord>> points;
	GLfloat width;
	bool readonly;
	int currentLine;
	GLuint displayList;
	void initDisplayList();
public:
	Mesh(GLfloat width = 2);
	void newLine();
	void add(double x, double y, double z);
	void draw();
};

