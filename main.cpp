#include <GL/glew.h>
#include <GL/glfw.h>

const GLuint scene = 1;
int windowWidth = 800, windowHeight = 600;


void initDisplayList() {
	glNewList(scene, GL_COMPILE);
	glEndList();
}

void draw() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glCallList(scene);
}

void handleInput() {
	if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS) {
		glfwCloseWindow();
		return;
	}
}

int main () {
	// Initialize GL for Windows
	if (glfwInit() != GL_TRUE) {
		return 1;
	}
	// 8x AA
	//glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 8);
	// Open a window
	if (glfwOpenWindow(windowWidth, windowHeight, 8, 8, 8, 8, 24, 0, GLFW_WINDOW) != GL_TRUE) {
		glfwTerminate();
		return 1;
	}
	glfwSetWindowTitle("Lines");
	// Buffer key presses
	glfwEnable(GLFW_STICKY_KEYS);

	// Initialize GL extension wrangler
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return 1;
	}

	// Init lighting
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// Init display list
	initDisplayList();
	
	// Main loop
	do {
		// Clear the buffer with the background color
		glClear(GL_COLOR_BUFFER_BIT);
		
		// Draw the scene
		draw();

		// Swap buffers and handle input
		glfwSwapBuffers();
		handleInput();
	} while(glfwGetWindowParam(GLFW_OPENED));

	return 0;
}