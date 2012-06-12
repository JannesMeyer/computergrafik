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

	//LineStrip(const LineStrip&); // copy constructor, unnamed parameter
	//const LineStrip& operator=(const LineStrip&); // zuweisungsoperator, unnamed parameter
	void readFromFile(const std::string& filename);
public:
	std::vector<vec3> points;
	Color color;
	GLfloat width;
	GLenum lineMode;

	//LineStrip(LineStrip&&); // move constructor, unnamed parameter
	LineStrip(const std::string& filename, Color color, GLfloat width = 1);
	LineStrip(std::vector<vec3> points, Color color, GLfloat width = 1);
	void draw();
	void setMode(GLenum mode);
};