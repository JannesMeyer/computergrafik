#include "LineStrip.h"
#include <fstream>
#include <sstream>

// Get points from memory
LineStrip::LineStrip(std::vector<vec3> points, Color color, GLfloat width)
	: points(points), color(color), width(width), lineMode(GL_FILL) {}

// Get points from file
LineStrip::LineStrip(const std::string& filename, Color color, GLfloat width)
	: color(color), width(width), lineMode(GL_FILL)
{
	readFromFile(filename);
}

void LineStrip::readFromFile(const std::string& filename) {
	std::ifstream file (filename);
	if (!file) {
		throw std::runtime_error("Unable to open file");
	}

	while (file.good()) {
		std::string line;
		double x, y, z;
		// Read one line from the file
		std::getline(file, line);
		// Parse the line using a stringstream
		std::stringstream sstream (line);
		sstream >> x >> y >> z;
		points.push_back(vec3(x, y, z));
	}
}

void LineStrip::draw() {
	// Disable lighting and depth test
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);

	// Set color
	glColor3f(color.r, color.g, color.b);

	if (lineMode == GL_POINT) {
		// Draw only points
		glPointSize(width * 4);
		glBegin(GL_POINTS);
	} else {
		// Draw lines
		glLineWidth(width * 2);
		glBegin(GL_LINE_STRIP);
	}

	// Draw vertices
	for (auto& p : points) {
		glVertex3d(p.x, p.y, p.z);
	}
	glEnd();

	// Re-enable lighting and depth test
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

void LineStrip::setMode(GLenum mode) {
	// do nothing
}