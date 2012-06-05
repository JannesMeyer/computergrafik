#pragma once
#include "../RenderObject.h"
#include "../Point.h"
#include "../Triangle.h"
#include <vector>
#include <memory>

class TriangleMesh : public RenderObject
{
private:
	std::vector<Triangle> triangles;
public:
	TriangleMesh(std::vector<Triangle> triangles);
	void draw();
};

