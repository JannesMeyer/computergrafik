#include "Interpolation.h"
#include "BicubicInterpolation.h"
#include "RenderObject.h"
#include "objects/CoordinateAxes.h"
#include "objects/LineStrip.h"
#include "objects/Mesh.h"
#include <vec3.h>

#include <GL/glew.h>
#include <GL/glfw.h>
#include <memory>
#include <iostream>
#ifdef _DEBUG
#endif

int windowWidth = 800;
int windowHeight = 600;
GLfloat alpha = 0;
GLfloat scale = 1;
std::vector<std::shared_ptr<RenderObject>> renderObjects;
bool wireframeEnabled = false;
bool vsyncEnabled = true;

/*/ Toggle here
void init() {
	renderObjects.emplace_back(new CoordinateAxes);

	Interpolation kurve;
	kurve.add(2, 2, 2);
	kurve.add(1, 2, 0);
	kurve.add(4, 3, 1);
	kurve.add(3, 4, 0);
	
	renderObjects.push_back(kurve.createLineStrip(10));

	Interpolation kurve2;
	kurve2.add(1, 1, 1);
	kurve2.add(1, -2, 0);
	kurve2.add(-4, 3, 1);
	kurve2.add(2, 4, 0);

	renderObjects.push_back(kurve2.createLineStrip(15));
}
/*/
void init() {
	renderObjects.emplace_back(new CoordinateAxes);

	// Interpolate a 4x4 matrix of points
	BicubicInterpolation gitter = BicubicInterpolation(4, 4);
	// First row
	gitter.add(2.0);
	gitter.add(1.0);
	gitter.add(1.0);
	gitter.add(1.0);
	// Second row
	gitter.add(1.0);
	gitter.add(0.5);
	gitter.add(1.0);
	gitter.add(1.0);
	// Third row
	gitter.add(2.0);
	gitter.add(1.2);
	gitter.add(1.3);
	gitter.add(2.0);
	// Fourth row
	gitter.add(1.0);
	gitter.add(1.0);
	gitter.add(1.8);
	gitter.add(2.0);

	renderObjects.push_back(gitter.getMesh(10));

	//std::shared_ptr<Mesh> mesh(new Mesh);
	//mesh->add(0, 0, 2);
	//mesh->add(0, 1, 2);
	//mesh->add(0, 2, 2);
	//mesh->add(1, 0, 2);
	//mesh->add(1, 1, 2);
	//mesh->add(1, 2, 2);
	//mesh->add(2, 0, 2);
	//mesh->add(2, 1, 2);
	//mesh->add(2, 2, 2);
}
/**/

void GLFWCALL keyHandler(int key, int action) {
	// Toggle wireframe mode
	if (key == 'W' && action == GLFW_PRESS) {
		wireframeEnabled = !wireframeEnabled;
		glPolygonMode(GL_FRONT_AND_BACK, wireframeEnabled ? GL_LINE : GL_FILL);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}
	// Toggle vsync
	if (key == 'V' && action == GLFW_PRESS) {
		vsyncEnabled = !vsyncEnabled;
		glfwSwapInterval(static_cast<int>(vsyncEnabled));
	}
	// Close window
	if (key == GLFW_KEY_ESC && action == GLFW_PRESS) {
		glfwCloseWindow();
		return;
	}
}

void handleInput() {
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

void initGLContext() {
	// Initialize GLFW
	if (glfwInit() != GL_TRUE) {
		throw std::runtime_error("Couldn't initialize GLFW");
	}
	// Open a window with 8x AA
	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	if (glfwOpenWindow(windowWidth, windowHeight, 8, 8, 8, 8, 24, 0, GLFW_WINDOW) != GL_TRUE) {
		glfwTerminate();
		throw std::runtime_error("Couldn't open an OpenGL window");
	}
	glfwSetWindowTitle("Kubische Interpolation");
	glfwEnable(GLFW_STICKY_KEYS); // Buffer key presses
	glfwSetKeyCallback(keyHandler);

	// Initialize GL extension wrangler
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		throw std::runtime_error("Couldn't initialize the GL extension wrangler");
	}

	// Disable vsync if wanted
	if (!vsyncEnabled) {
		glfwSwapInterval(0);
	}
}

// set viewport transformations and draw objects
void lighting()
{
	GLfloat lp1[4] = { 10, 5, 10,  1};
	GLfloat lp2[4] = { -5, 5, -10,  1};
	GLfloat white[4] = { 1.0f,  1.0f,  1.0f,  1};
	GLfloat ambient[4] = { 0.3f,  0.3f,  0.3f,  1};

	//glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, 1);
	//glEnable(GL_COLOR_MATERIAL);
	//glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT1, GL_POSITION, lp1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  white);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, white);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	//glLightfv(GL_LIGHT2, GL_POSITION, lp2);
	//glLightfv(GL_LIGHT2, GL_AMBIENT, white);
	//glLightfv(GL_LIGHT2, GL_DIFFUSE,  white);
	//glLightfv(GL_LIGHT2, GL_SPECULAR, white);
	//glEnable(GL_LIGHT2);

	   // const float amb1 = 2.0;
    //const float LightAmbient[][4]  = {  { amb1, amb1, amb1, 1.0f },
    //                                    { amb1, amb1, amb1, 1.0f }
    //                                };
    //const float LightDiffuse[] [4] = {  { 1.0f, 1.0f, 1.0f, 1.0f },
    //                                    { 1.0f, 1.0f, 1.0f, 1.0f }
    //                                };
    //const float LightPosition[][4] = {  { 1.0f,  4.0f, 2.0f, 0.0f },
    //                                    { 0.0f, 10.0f, 0.0f, 1.0f }
    //                                };

    //glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient[0]);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse[0]);
    //glLightfv(GL_LIGHT0, GL_POSITION, LightPosition[0]);

    ////glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    ////glEnable(GL_COLOR);
    ////glEnable(GL_COLOR_MATERIAL);
	
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
}

void draw() {
	// Clear buffers
	glClearColor(0, 0, 0, 1);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// Lighting
	lighting();
	
	// Projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -7.5, 7.5, -10, 60);
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

	setMaterialColor(1, 1, 1);
	//gluSphere(gluNewQuadric(), 2, 50, 50);

	// Objects
	for (auto& object : renderObjects) {
		object->draw();
	}
}

// Rounding function
template<class T>
int round(T x) {
	return static_cast<int>(x + 0.5);
}

void main() {
	// Viewport
	glViewport(0, 0, windowWidth, windowHeight);
	// Create an OpenGL context
	initGLContext();

	// Initialize the drawing code
	init();

	// Initialize time
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