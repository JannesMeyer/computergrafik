#pragma once
#include "../RenderObject.h"
#include "../Point.h"
#include "Triangle.h"
#include <vector>
#include <memory>
#include <string>

class TriangleMesh : public RenderObject
{
private:
	std::vector<std::shared_ptr<Point>> points;
	std::vector<Triangle> triangles;
public:
	TriangleMesh(std::vector<std::shared_ptr<Point>> points, std::vector<Triangle> triangles);
	~TriangleMesh();
	void draw();
	void saveToFile(std::string filename);
};