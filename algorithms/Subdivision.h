#pragma once
#include "../objects/LineStrip.h"
#include <memory>

class Subdivision {
private:
	std::shared_ptr<LineStrip> line;

public:
	Subdivision(std::shared_ptr<LineStrip> line);
	void increaseDetail();
	void decreaseDetail();
};