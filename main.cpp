#include "Point.h"
#include "Color.h"
#include "Scene.h"
#include "RenderObject.h"
#include "algorithms/Subdivision.h"
#include "objects/CoordinateAxes.h"
#include "objects/LineStrip.h"
#include "objects/Mesh.h"
#include "FpsCounter.h"

#include <GL/glfw.h>
#include <memory>
#include <vector>
#include <string>
#include <exception>
#include <iostream>

struct Settings {
	int width;
	int height;
	bool wireframeEnabled;
	bool vsyncEnabled;
};
// Default settings
Settings settings = {800, 600, false, true};

std::shared_ptr<Scene> scene;
std::shared_ptr<Subdivision> subdivision;

/*
 * Exercise 6.1
 * Polygonzug einlesen, mittels Chaikin's Algorithmus unterteilen und zeichnen.
 * Es muss viermal die + Taste gedrückt werden, um eine viermalige Unterteilung zu bekommen.
 */
void initLab61() {
	// Create a scene
	scene = std::make_shared<Scene>();
	scene->add(std::make_shared<CoordinateAxes>());

	// Define some colors
	Color black (0, 0, 0);
	Color red (1, 0, 0);

	// Read LineStrip from file
	auto line = std::make_shared<LineStrip>("data/points.txt", black);
	// Create a copy for the red control points
	auto controlPoints = std::make_shared<LineStrip>(*line);
	controlPoints->lineMode = GL_POINT;
	controlPoints->color = red;
	controlPoints->width = 2;
	// Add them to the scene
	scene->add(line);
	scene->add(controlPoints);

	// Setup the subdivision algorithm
	subdivision = std::make_shared<Subdivision>(line);
}

/*
 * Exercise 6.2
 * Rechtecksgitter einlesen und zeichnen
 */
void initLab62() {
	// Create a scene
	scene = std::make_shared<Scene>();
	scene->add(std::make_shared<CoordinateAxes>());

	// Read Mesh from file
	scene->add(std::make_shared<Mesh>("data/mesh.txt"));
}

/*
 * Exercise 7.1
 * Rechtecksgitter einlesen, Dreieckgsgitter berechnen und speichern
 */
void initLab71() {
	// Create a scene
	scene = std::make_shared<Scene>();
	scene->add(std::make_shared<CoordinateAxes>());
	
	// Read Mesh from file
	Mesh mesh ("data/mesh.txt");
	// Create TriangleMesh
	auto triangleMesh = mesh.createTriangleMesh();
	scene->add(triangleMesh);
	// Save the TriangleMesh to a file
	triangleMesh->saveToFile("data/trianglemesh.txt");
}

/*
 * Exercise 7.2
 * Dreiecksgitter einlesen, Punktnormalen berechnen und zeichnen
 */
void initLab72() {
	// Create a scene
	scene = std::make_shared<Scene>();
	scene->add(std::make_shared<CoordinateAxes>());

	// Read TriangleMesh from file and scale it by a factor of 50
	auto triangleMesh = std::make_shared<TriangleMesh>("data/bunny1.txt", 50.0f);
	scene->add(triangleMesh);
}









/*
 * Listen to key events
 */
void GLFWCALL onKeyEvent(int key, int action) {
	// Toggle wireframe mode
	if (key == 'W' && action == GLFW_PRESS) {
		settings.wireframeEnabled = !settings.wireframeEnabled;
		scene->setPolygonMode(settings.wireframeEnabled ? GL_LINE : GL_FILL);
	}
	// Toggle vsync
	if (key == 'V' && action == GLFW_PRESS) {
		settings.vsyncEnabled = !settings.vsyncEnabled;
		glfwSwapInterval(static_cast<int>(settings.vsyncEnabled));
	}
	
	// If a subdivision algorithm is active
	if (subdivision != nullptr) {
		// Increase level of detail
		if ((key == '+' || key == 'A') && action == GLFW_PRESS) {
			std::cout << "Increasing detail" << std::endl;
			subdivision->increaseDetail();
		}
		// Decrease level of detail
		if ((key == '-' || key == 'D') && action == GLFW_PRESS) {
			std::cout << "Decreasing detail" << std::endl;
			subdivision->decreaseDetail();
		}
	}

	// Close window
	if (key == GLFW_KEY_ESC && action == GLFW_PRESS) {
		glfwCloseWindow();
		return;
	}
}

/*
 * These key events are executed continuously while the key
 * is held down, not just once per key press.
 */
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

/*
 * Create an OpenGL context and a window
 */
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
	glfwSetWindowTitle("Projekt 2");
	glfwEnable(GLFW_STICKY_KEYS);
	glfwSetKeyCallback(onKeyEvent);

	// Initialize GL extension wrangler
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		throw std::runtime_error("Couldn't initialize the GL extension wrangler");
	}

	// Print OpenGL version
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl << std::endl;

	// Disable vsync if wanted
	if (!settings.vsyncEnabled) {
		glfwSwapInterval(0);
	}
}

/*
 * Setup the viewport and projection matrix
 */
void onReshape() {
	// Set viewport
	glViewport(0, 0, settings.width, settings.height);
	
	// Projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -7.5, 7.5, -10, 60);
}





/*
 * Main function
 */
int main() {
	// Initialize OpenGL
	try {
		onInit();
		onReshape();
	} catch(std::exception& e) {
		std::cout << e.what() << std::endl;
		system("pause");
		return 1;
	}

	// Scene setup
	try {
		// INITIALIZATION FUNCTION GOES HERE:
		//initLab61();
		//initLab62();
		//initLab71();
		//initLab72();
	} catch(std::exception& e) {
		std::cout << e.what() << std::endl;
		system("pause");
		return 1;
	}

	// Main loop
	FpsCounter fps;
	do {
		// Draw the scene and swap buffers
		scene->draw();
		glfwSwapBuffers();

		// Handle input
		onInput();
		
		// Signal a completed frame to the FpsCounter
		fps.tick();
	} while (glfwGetWindowParam(GLFW_OPENED));

	return 0;
}