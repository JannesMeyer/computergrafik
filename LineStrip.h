#pragma once
#include <vec3.h>

#include <gl/glew.h>
#include <vector>

class LineStrip
{
private:
	std::vector<std::pair<Vec3, bool>> points;
	GLfloat width;
	LineStrip(const LineStrip&); // H�?
	const LineStrip& operator=(const LineStrip&); // H�?
public:
	LineStrip(LineStrip&&); // H�?
	LineStrip(GLfloat width = 2);
	~LineStrip();
	void add(Vec3 newPoint, bool highlight = false);
	void draw();
};