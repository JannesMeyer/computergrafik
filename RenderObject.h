#pragma once

// Abstract class that represents an object which can be rendered
class RenderObject
{
public:
	virtual void draw() = 0;
};