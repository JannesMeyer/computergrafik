#pragma once

#include <vec3.h>

#include <gl/glew.h>
#include <vector>
using namespace std;

class LineStrip
{
private:
	vector<Vec3>* points;
	vector<bool>* highlights;
	GLfloat width;
public:
	LineStrip(GLfloat width = 2);
	~LineStrip();
	void add(Vec3 newPoint, bool highlight = false);
	void draw();
};