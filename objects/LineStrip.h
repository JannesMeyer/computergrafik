#pragma once
#include "../LTObject.h"
#include <vec3.h>

#include <GL/glew.h>
#include <vector>

class LineStrip : public LTObject
{
private:
	std::vector<std::pair<Vec3, bool>> points;
	GLfloat width;
	//LineStrip(const LineStrip&); // copy constructor
	//const LineStrip& operator=(const LineStrip&); // zuweisungsoperator
public:
	//LineStrip(LineStrip&&); // move constructor
	LineStrip(GLfloat width = 2);
	~LineStrip();
	void add(Vec3 newPoint, bool highlight = false);
	void draw();
};