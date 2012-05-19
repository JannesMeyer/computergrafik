#pragma once
#include "RenderObject.h"
#include <GL/glew.h>
#include <memory>
#include <vector>

class Scene
{
private:
	std::vector<std::shared_ptr<RenderObject>> renderObjects;
public:
	GLfloat rotation;
	GLfloat scale;

	Scene();
	void add(std::shared_ptr<RenderObject> object);
	void lighting();
	void setMaterialColor(GLfloat r, GLfloat g, GLfloat b);
	void draw();
};

