#include "Interpolation.h"
#include "RenderObject.h"
#include "objects/LineStrip.h"
#include "objects/Mesh.h"
#include <vec3.h>

#include <GL/glew.h>
#include <GL/glfw.h>
#include <memory>
#ifdef _DEBUG
#include <iostream>
#endif

int windowWidth = 800;
int windowHeight = 600;
GLfloat alpha = 0;
GLfloat scale = 2;
std::vector<std::shared_ptr<RenderObject>> renderObjects;

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

void initGLContext() {
	// Initialize GLFW
	if (glfwInit() != GL_TRUE) {
		throw std::runtime_error("Couldn't initialize GLFW");
	}
	// Open a window with 8x AA
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 8);
	if (glfwOpenWindow(windowWidth, windowHeight, 8, 8, 8, 8, 24, 0, GLFW_WINDOW) != GL_TRUE) {
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

void draw() {
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

// Rounding function
inline int round(float x) {
	return (int)(x + 0.5);
}

void main() {
	// Viewport
	glViewport(0, 0, windowWidth, windowHeight);
	// Create an OpenGL context
	initGLContext();

	// Initialize the drawing code
	init();

	// Initialize time
	glfwSwapInterval(0); // Disable vsync
	double oldTime = glfwGetTime();
	double currentTime;
	double timeDelta;
	double fps;
	int frameCounter = 0;

	// Main loop
	do {
		// Draw the scene
		draw();
		glfwSwapBuffers();
		// Handle input
		handleInput();
		// Calculate fps
		++frameCounter;
		currentTime = glfwGetTime();
		timeDelta = currentTime - oldTime;
		if (timeDelta > 1.0) {
			fps = frameCounter / timeDelta;
			std::cout << round(fps) << " fps" << std::endl;
			// Reset everything
			oldTime = currentTime;
			frameCounter = 0;
		}
	} while(glfwGetWindowParam(GLFW_OPENED));
}