#pragma once
#include "../RenderObject.h"
#include "../Point.h"
#include "../Triangle.h"
#include <vector>
#include <memory>
#include <string>
#include <GL/glew.h>

class TriangleMesh : public RenderObject
{
private:
	std::vector<std::shared_ptr<Point>> points;
	std::vector<Triangle> triangles;
	float scale;

	void readFromFile(std::string filename);
	void calculateNormals();
public:
	TriangleMesh(std::string filename, GLfloat scale = 1);
	TriangleMesh(std::vector<std::shared_ptr<Point>> points, std::vector<Triangle> triangles, GLfloat scale = 1);
	void draw();
	void saveToFile(std::string filename);
};