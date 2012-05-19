#pragma once
#include "../RenderObject.h"
#include <vec3.h>
#include <GL/glew.h>
#include <vector>

class LineStrip : public RenderObject
{
private:
	std::vector<std::pair<Vec3, bool>> points;
	GLfloat width;
	bool readonly;
	GLuint displayList;
	//LineStrip(const LineStrip&); // copy constructor
	//const LineStrip& operator=(const LineStrip&); // zuweisungsoperator
	void initDisplayList();
public:
	//LineStrip(LineStrip&&); // move constructor
	LineStrip(GLfloat width = 2);
	void add(Vec3 newPoint, bool highlight = false);
	void draw();
};