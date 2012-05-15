#include "Interpolation.h"
#include "LineStrip.h"
#include <iostream>
#include <vec3.h>
#include <GL/glew.h>
#include <GL/glfw.h>


int windowWidth, windowHeight;
GLfloat alpha;
LineStrip linestrip;

void initGLContext(int width, int height) {
	windowWidth = width;
	windowHeight = height;
	// Initialize GLFW
	if (glfwInit() != GL_TRUE) {
		throw runtime_error("Couldn't initialize GLFW");
	}
	// Open a window with 8x AA
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 8);
	if (glfwOpenWindow(width, height, 8, 8, 8, 8, 24, 0, GLFW_WINDOW) != GL_TRUE) {
		glfwTerminate();
		throw runtime_error("Couldn't open an OpenGL window");
	}
	glfwSetWindowTitle("Kubische Interpolation");
	glfwEnable(GLFW_STICKY_KEYS); // Buffer key presses

	// Initialize GL extension wrangler
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		throw runtime_error("Couldn't initialize the GL extension wrangler");
	}
}

void init() {
	auto kurve = Interpolation();
	kurve.add(2.0, 1.0, 0);
	kurve.add(1.0, 2.0, 0);
	kurve.add(4.0, 3.0, 0);
	kurve.add(3.0, 4.0, 0);
	kurve.printContent();

	linestrip = kurve.getLineStrip(10);
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
	glScalef(2, 2, 2);
	glRotatef(alpha, 0, 1, 0);

	// Objects
	linestrip.draw();
}

void handleInput() {
	// Close
	if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS) {
		glfwCloseWindow();
		return;
	}
	// Rotate
	if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
		alpha += 2;
	} else if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
		alpha -= 2;
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