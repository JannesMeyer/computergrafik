#pragma once
#include <vec3.h>

#include <gl/glew.h>
#include <vector>

class LineStrip
{
private:
	std::vector<std::pair<Vec3, bool>> points;
	GLfloat width;
	LineStrip(const LineStrip&); // Hä?
	const LineStrip& operator=(const LineStrip&); // Hä?
public:
	LineStrip(LineStrip&&); // Hä?
	LineStrip(GLfloat width = 2);
	~LineStrip();
	void add(Vec3 newPoint, bool highlight = false);
	void draw();
};