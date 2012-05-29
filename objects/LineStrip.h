#pragma once
#include "../RenderObject.h"
#include "../Point.h"
#include "../Color.h"

#include <GL/glew.h>
#include <vector>

class LineStrip : public RenderObject
{
private:
	GLfloat width;
	Color color;
	GLuint displayList;
	//LineStrip(const LineStrip&); // copy constructor
	//const LineStrip& operator=(const LineStrip&); // zuweisungsoperator
public:
	std::vector<Point> points;
	//LineStrip(LineStrip&&); // move constructor
	LineStrip(std::vector<Point> points, Color color, GLfloat width = 1);
	void draw();
};