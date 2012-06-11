#pragma once
#include "../RenderObject.h"
#include "../Vector.h"
#include "../Color.h"
#include <GL/glew.h>
#include <vector>

class LineStrip : public RenderObject
{
private:
	GLuint displayList;

	//LineStrip(const LineStrip&); // copy constructor (Q: when to use this?)
	//const LineStrip& operator=(const LineStrip&); // zuweisungsoperator (Q: when to use this?)
	void readFromFile(std::string filename);
public:
	std::vector<vec3> points;
	Color color;
	GLfloat width;
	GLenum lineMode;

	//LineStrip(LineStrip&&); // move constructor (Q: when to use this?)
	LineStrip(std::string filename, Color color, GLfloat width = 1);
	LineStrip(std::vector<vec3> points, Color color, GLfloat width = 1);
	void draw();
	void setMode(GLenum mode);
};