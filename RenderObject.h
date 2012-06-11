#pragma once
#include <GL/glew.h>

// Abstract class that represents an object which can be rendered
class RenderObject
{
public:
	GLenum mode;

	virtual void draw() = 0;
	RenderObject(GLenum mode = GL_FILL) : mode(mode) {}
};