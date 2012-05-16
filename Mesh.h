#pragma once
class Mesh
{
private:
	double points[3][3];
	int stepX, stepY;
public:
	Mesh(void);
	~Mesh(void);
	void add(int xpos, int ypos, double z);
	void draw();
};

