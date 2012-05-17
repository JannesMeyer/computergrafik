#include "Interpolation.h"
#include "LTObject.h"
#include "objects/LineStrip.h"
#include "objects/Mesh.h"
#include <vec3.h>

#include <GL/glew.h>
#include <GL/glfw.h>
#include <iostream>
#include <memory>

int windowWidth, windowHeight;
GLfloat alpha = 0, scale = 2;
std::vector<std::shared_ptr<LTObject>> renderObjects;
//std::unique_ptr<LineStrip> linestrip, linestrip2;

void initGLContext(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	// Initialize GLFW
	if (glfwInit() != GL_TRUE) {
		throw std::runtime_error("Couldn't initialize GLFW");
	}
	// Open a window with 8x AA
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 8);
	if (glfwOpenWindow(width, height, 8, 8, 8, 8, 24, 0, GLFW_WINDOW) != GL_TRUE) {
		glfwTerminate();
		throw std::runtime_error("Couldn't open an OpenGL window");
	}
	glfwSetWindowTitle("Kubische Interpolation");
	glfwEnable(GLFW_STICKY_KEYS); // Buffer key presses

	// Initialize GL extension wrangler
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		throw std::runtime_error("Couldn't initialize the GL extension wrangler");
	}
}

// Toggle here
void init() {
	auto kurve = Interpolation(); // C++11: auto
	kurve.add(2, 2, 2);
	kurve.add(1, 2, 0);
	kurve.add(4, 3, 1);
	kurve.add(3, 4, 0);
	
	renderObjects.push_back(kurve.createLineStrip(10));

	auto kurve2 = Interpolation(); // C++11: auto
	kurve2.add(1, 1, 1);
	kurve2.add(1, -2, 0);
	kurve2.add(-4, 3, 1);
	kurve2.add(2, 4, 0);

	renderObjects.push_back(kurve2.createLineStrip(15));
}
/*/
void init() {
	std::shared_ptr<Mesh> mesh(new Mesh);
	mesh->add(0, 0, 2);
	mesh->add(0, 1, 2);
	mesh->add(0, 2, 2);
	mesh->add(1, 0, 2);
	mesh->add(1, 1, 2);
	mesh->add(1, 2, 2);
	mesh->add(2, 0, 2);
	mesh->add(2, 1, 2);
	mesh->add(2, 2, 2);

	renderObjects.push_back(mesh);
}
/**/

// Draws coordinate axes
void drawCoordinateAxes() {
	glColor3f(0.5, 0.5, 0.5);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
}

void draw() {
	// Viewport
	glViewport(0, 0, windowWidth, windowHeight);
	// Clear buffers
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClearDepth(1.0f);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);
	// Depth buffer
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	// Lighting
	glDisable(GL_LIGHTING);
	//glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
	// Projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -15, 15, -10, 60);
	//gluPerspective(60, aspectRatio, 0.1, 255.0);

	// Modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
	// Camera
	glTranslatef(0, 0, -10); // Move 10 units backwards in z, since camera is at origin
	// Rotation
	glRotatef(10, 1, 0, 0);
	glRotatef(alpha, 0, 1, 0);

	glTranslatef(0, -2, 0);
	glScalef(scale, scale, scale);

	// Objects
	glEnable(GL_LINE_SMOOTH);
	glShadeModel(GL_SMOOTH); // Enable Smooth Shading
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST); // Set Line Antialiasing
	drawCoordinateAxes();

	for (auto& object : renderObjects) {
		object->draw();
	}
}

void handleInput() {
	// Close
	if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS) {
		glfwCloseWindow();
		return;
	}
	// Rotate
	if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
		alpha += 1;
	} else if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
		alpha -= 1;
	}
	// Zoom
	if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS) {
		scale += 0.01f;
	} else if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
		scale -= 0.01f;
	}
}

void main() {
	// Create an OpenGL context
	initGLContext(800, 600);

	// Initialize the drawing code
	init();
	// Main loop
	do {
		// Draw the scene
		draw();
		glfwSwapBuffers();
		// Handle input
		handleInput();
	} while(glfwGetWindowParam(GLFW_OPENED));
}