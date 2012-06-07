#pragma once
#include "../RenderObject.h"
#include "../Point.h"
#include "../Triangle.h"
#include <vector>
#include <memory>
#include <string>

class TriangleMesh : public RenderObject
{
private:
	std::vector<std::shared_ptr<Point>> points;
	std::vector<Triangle> triangles;
	void readFromFile(std::string filename);
	void calculateNormals();
public:
	TriangleMesh(std::vector<std::shared_ptr<Point>> points, std::vector<Triangle> triangles);
	TriangleMesh(std::string filename);
	void draw();
	void saveToFile(std::string filename);
};