#pragma once
#include "../RenderObject.h"
#include <vector>

void setMaterialColor(float r, float g, float b);

struct Coord {
	double x;
	double y;
	double z;
};

class Mesh : public RenderObject
{
private:
	std::vector<std::vector<Coord>> points;
	int currentLine;
public:
	Mesh(void);
	~Mesh(void);
	void newLine();
	void add(double x, double y, double z);
	void draw();
};

