#include "Scene.h"
#include "Interpolation.h"
#include "BicubicInterpolation.h"
#include "RenderObject.h"
#include "objects/CoordinateAxes.h"
#include "objects/LineStrip.h"
#include "objects/Mesh.h"
#include <vec3.h>

#include <GL/glfw.h>
#include <memory>
#include <iostream>

std::shared_ptr<Scene> scene;
struct {
	int width;
	int height;
	bool wireframeEnabled;
	bool vsyncEnabled;
} settings;

// A simple rounding function
template<class T>
int round(T x) {
	return static_cast<int>(x + 0.5);
}

// Calculates frames per second
class FpsCounter
{
private:
	double oldTime;
	double currentTime;
	double timeDelta;
	int frameCounter;

public:
	FpsCounter() {
		oldTime = glfwGetTime();
		frameCounter = 0;
	}

	// Should be called for every frame
	void tick() {
		++frameCounter;
		if (frameCounter < 20) {
			return;
		}

		currentTime = glfwGetTime();
		timeDelta = currentTime - oldTime;
		if (timeDelta > 1.0) {
			printFps();
			// Reset state
			oldTime = currentTime;
			frameCounter = 0;
		}
	}

	// Calculates and prints the FPS value
	const void printFps() {
		double fps = frameCounter / timeDelta;
		std::cout << round(fps) << " fps" << std::endl;
	}
};

// Labor 4
void initLab4() {
	// Draw coordinate axes
	scene->add(std::shared_ptr<CoordinateAxes>(new CoordinateAxes));

	// Interpolate a line of 4 points
	Interpolation kurve;
	kurve.add(2, 2, 2);
	kurve.add(1, 2, 0);
	kurve.add(4, 3, 1);
	kurve.add(3, 4, 0);
	// Interpolate and add the results to the scene
	scene->add(kurve.createLineStrip(10));

	// Interpolate a line of 4 points
	Interpolation kurve2;
	kurve2.add(1, 1, 1);
	kurve2.add(1, -2, 0);
	kurve2.add(-4, 3, 1);
	kurve2.add(2, 4, 0);
	// Interpolate and add the results to the scene
	scene->add(kurve2.createLineStrip(15));
}

// Labor 5
void initLab5() {
	// Add coordinate axes to the scene
	scene->add(std::shared_ptr<CoordinateAxes>(new CoordinateAxes));

	// Interpolate a 4x4 matrix of points
	BicubicInterpolation matrix = BicubicInterpolation(4, 4);
	// First row
	matrix.add(2.0);
	matrix.add(1.0);
	matrix.add(1.0);
	matrix.add(1.0);
	// Second row
	matrix.add(1.0);
	matrix.add(0.5);
	matrix.add(3.0);
	matrix.add(1.0);
	// Third row
	matrix.add(2.0);
	matrix.add(1.2);
	matrix.add(1.3);
	matrix.add(2.0);
	// Fourth row
	matrix.add(1.2);
	matrix.add(1.0);
	matrix.add(1.8);
	matrix.add(2.0);
	// Interpolate and add the results to the scene
	scene->add(matrix.createMesh(50));
}

void initGLWindow(int width, int height) {
	// Some settings
	settings.wireframeEnabled = true;
	settings.vsyncEnabled = true;
	settings.width = width;
	settings.height = height;

	// Initialize GLFW
	if (glfwInit() != GL_TRUE) {
		throw std::runtime_error("Couldn't initialize GLFW");
	}
	// Open a window with 8x AA
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 8);
	if (glfwOpenWindow(settings.width, settings.height, 8, 8, 8, 8, 24, 0, GLFW_WINDOW) != GL_TRUE) {
		glfwTerminate();
		throw std::runtime_error("Couldn't open an OpenGL window");
	}
	glfwSetWindowTitle("Interpolation demo");
	glfwEnable(GLFW_STICKY_KEYS);

	// Initialize GL extension wrangler
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		throw std::runtime_error("Couldn't initialize the GL extension wrangler");
	}

	// Disable vsync if wanted
	if (!settings.vsyncEnabled) {
		glfwSwapInterval(0);
	}

	// Enable wireframe rendering if wanted
	glPolygonMode(GL_FRONT_AND_BACK, settings.wireframeEnabled ? GL_POINT : GL_FILL);

	// Set viewport
	glViewport(0, 0, settings.width, settings.height);

}

void handleInput() {
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

void GLFWCALL handleKeyEvent(int key, int action) {
	// Toggle wireframe mode
	if (key == 'W' && action == GLFW_PRESS) {
		settings.wireframeEnabled = !settings.wireframeEnabled;
		glPolygonMode(GL_FRONT_AND_BACK, settings.wireframeEnabled ? GL_POINT : GL_FILL);
	}
	// Toggle vsync
	if (key == 'V' && action == GLFW_PRESS) {
		settings.vsyncEnabled = !settings.vsyncEnabled;
		glfwSwapInterval(static_cast<int>(settings.vsyncEnabled));
	}
	// Close window
	if (key == GLFW_KEY_ESC && action == GLFW_PRESS) {
		glfwCloseWindow();
		return;
	}
}

int main() {
	initGLWindow(800, 600);
	scene = std::shared_ptr<Scene>(new Scene);
	// Initialize the drawing code
	initLab5();
	
	glfwSetKeyCallback(handleKeyEvent);

	// Main loop
	FpsCounter fps;
	do {
		scene->draw();
		glfwSwapBuffers();

		handleInput();
		
		fps.tick();
	} while(glfwGetWindowParam(GLFW_OPENED));

	return 0;
}