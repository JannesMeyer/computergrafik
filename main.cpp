#include "Point.h"
#include "Color.h"
#include "Scene.h"
#include "RenderObject.h"
#include "objects/CoordinateAxes.h"
#include "objects/LineStrip.h"
#include "objects/Mesh.h"
#include "FpsCounter.h"

#include <GL/glfw.h>
#include <memory>
#include <vector>
#include <string>
#include <exception>
#include <fstream>
#include <sstream>
#include <iostream>

struct {
	int width;
	int height;
	bool wireframeEnabled;
	bool vsyncEnabled;
} settings;

std::shared_ptr<Scene> scene;
std::shared_ptr<LineStrip> line;

// Reads three-dimensional points from a file
std::vector<Point> readPointsFromFile(std::string filename) {
	double x, y, z;
	std::vector<Point> points;
	std::ifstream file (filename);

	if (!file) {
		throw std::runtime_error("Unable to open file");
	}

	// Read all lines
	while (file.good()) {
		// Read one line from the file
		std::string line;
		std::getline(file, line);
		// Parse the line using a stringstream
		std::stringstream sstream (line);
		sstream >> x >> y >> z;
		points.push_back(Point(x, y, z));
	}
	return points;
}

// Labor 6.1
void initLab61() {
	// Add coordinate axes
	scene->add(std::make_shared<CoordinateAxes>());

	// Read the point data
	auto points = readPointsFromFile("data/points.txt");

	// Polygonzug erstellen
	Color black (0, 0, 0);
	line = std::make_shared<LineStrip>(points, black);
	scene->add(line);

	// Ursprüngliche Punkte erstellen
	Color red (1, 0, 0);
	std::shared_ptr<LineStrip> kontrollpunkte (new LineStrip(points, red, 2));
	kontrollpunkte->mode = GL_POINT; // Als Punkte rendern, und nicht als verbundene Linie
	scene->add(kontrollpunkte);
}

void initLab62() {
	// Add coordinate axes
	scene->add(std::make_shared<CoordinateAxes>());

	// Rechtecksgitter aus einer Datei einlesen
	std::shared_ptr<Mesh> rechtecksgitter (new Mesh("data/mesh.txt", 2));
	//auto rechtecksgitter = std::make_shared<Mesh>("data/mesh.txt", 2);
	scene->add(rechtecksgitter);
}

void initLab71() {
	// Add coordinate axes
	scene->add(std::make_shared<CoordinateAxes>());
	
	// Rechtecksgitter aus einer Datei einlesen
	//Mesh mesh ("data/mesh.txt", 2);
	//auto triangleMesh = mesh.createTriangleMesh();
	// Dreiecksgitter in eine Datei speichern
	//triangleMesh->saveToFile("data/dreiecke.txt");

	// Dreiecksgitter aus einer Datei einlesen
	auto triangleMesh = std::make_shared<TriangleMesh>("data/billard1.txt");
	scene->add(triangleMesh);
}

// When we increase the level of detail we will have to re-create the points
// array inserting the new intermediate points into it.
//
//	Basically the subdivision works like this. each line,
//
//            A  *------------*  B
//
//	will be split into 2 new points, Q and R.
//
//                   Q    R
//            A  *---|----|---*  B
//
//	Q and R are given by the equations :
//
// 		Q = 3/4*A + 1/4*B
// 		R = 3/4*B + 1/4*A
//
void increaseDetail() {
	unsigned int i;
	std::vector<Point> newPoints;

	// keep the first point
	newPoints.push_back(line->points.front());
	for (i = 0; i < (line->points.size() - 1); ++i) {
	
		// get 2 original points
		const Point& p0 = line->points[i];
		const Point& p1 = line->points[i+1];
		Point Q;
		Point R;

		// average the 2 original points to create 2 new points
		Q.x = 0.75 * p0.x + 0.25 * p1.x;
		Q.y = 0.75 * p0.y + 0.25 * p1.y;
		Q.z = 0.75 * p0.z + 0.25 * p1.z;

		R.x = 0.25 * p0.x + 0.75 * p1.x;
		R.y = 0.25 * p0.y + 0.75 * p1.y;
		R.z = 0.25 * p0.z + 0.75 * p1.z;

		newPoints.push_back(Q);
		newPoints.push_back(R);
	}
	// keep the last point
	newPoints.push_back(line->points.back());

	// update the points array
	line->points = newPoints;
}

// When we decrease the level of detail, we can rather niftily get back
// to exactly what we had before. Since the original subdivision
// simply required a basic ratio of both points, we can simply
// reverse the ratios to get the previous point...
//
void decreaseDetail() {
	// make sure we dont loose any points!!
	if (line->points.size() <= 4) {
		return;
	}

	unsigned int i;
	std::vector<Point> newPoints;

	// keep the first point
	newPoints.push_back(line->points.front());

	// step over every 2 points
	for(i = 1; i < (line->points.size() - 1); i += 2) {

		// get last point found in reduced array
		const Point& pLast = newPoints.back();

		// get 2 original point
		const Point& p0 = line->points[i];
		Point Q;

		// calculate the original point
		Q.x = p0.x - 0.75 * pLast.x;
		Q.y = p0.y - 0.75 * pLast.y;
		Q.z = p0.z - 0.75 * pLast.z;

		Q.x *= 4.0;
		Q.y *= 4.0;
		Q.z *= 4.0;

		// add to new curve
		newPoints.push_back(Q);
	}

	// copy over points
	line->points = newPoints;
}

void GLFWCALL onKeyEvent(int key, int action) {
	// Toggle wireframe mode
	if (key == 'W' && action == GLFW_PRESS) {
		settings.wireframeEnabled = !settings.wireframeEnabled;
		//line->mode = settings.wireframeEnabled ? GL_POINT : GL_FILL;
		scene->setPolygonMode(settings.wireframeEnabled ? GL_LINE : GL_FILL);
	}
	// Toggle vsync
	if (key == 'V' && action == GLFW_PRESS) {
		settings.vsyncEnabled = !settings.vsyncEnabled;
		glfwSwapInterval(static_cast<int>(settings.vsyncEnabled));
	}
	/*// Increase level of detail
	if ((key == '+' || key == 'A') && action == GLFW_PRESS) {
		increaseDetail();
	}
	// Decrease level of detail
	if ((key == '-' || key == 'D') && action == GLFW_PRESS) {
		decreaseDetail();
	}*/
	// Close window
	if (key == GLFW_KEY_ESC && action == GLFW_PRESS) {
		glfwCloseWindow();
		return;
	}
}

void onInit() {
	// Initialize GLFW
	if (glfwInit() != GL_TRUE) {
		throw std::runtime_error("Couldn't initialize GLFW");
	}
	// Open a window with 8x AA
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	if (glfwOpenWindow(settings.width, settings.height, 8, 8, 8, 8, 24, 0, GLFW_WINDOW) != GL_TRUE) {
		glfwTerminate();
		throw std::runtime_error("Couldn't open an OpenGL window");
	}
	glfwSetWindowTitle("Exercise 7");
	glfwEnable(GLFW_STICKY_KEYS);
	glfwSetKeyCallback(onKeyEvent);

	// Initialize GL extension wrangler
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		throw std::runtime_error("Couldn't initialize the GL extension wrangler");
	}

	// Disable vsync if wanted
	if (!settings.vsyncEnabled) {
		glfwSwapInterval(0);
	}



	// Set the background color
	glClearColor(1, 1, 1, 1);
	// Depth buffer settings
	//glClearDepth(1.0);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);

	// Lighting
	//glDisable(GL_LIGHTING);
}

void onReshape() {
	// Set viewport
	glViewport(0, 0, settings.width, settings.height);
	
	// Projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -7.5, 7.5, -10, 60);
}

void onDraw() {
	scene->draw();
}

void onInput() {
	// Rotate
	if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
		scene->rotation += 1;
	} else if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
		scene->rotation -= 1;
	}
	// Zoom
	if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) {
		scene->scale += 0.01f;
	} else if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
		scene->scale -= 0.01f;
	}
}

int main() {
	// Some settings
	settings.wireframeEnabled = false;
	settings.vsyncEnabled = true;
	settings.width = 800;
	settings.height = 600;

	// Initialize OpenGL
	onInit();
	onReshape();
	// Create a scene container
	scene = std::shared_ptr<Scene>(new Scene);
	// Call the setup code
	try {
		initLab71();
	} catch(std::exception& e) {
		std::cout << e.what() << std::endl;
		system("pause");
		return 1;
	}

	// Main loop
	FpsCounter fps;
	do {
		onDraw();
		glfwSwapBuffers();

		onInput();
		
		fps.tick();
	} while (glfwGetWindowParam(GLFW_OPENED));

	return 0;
}