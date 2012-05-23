#include "Scene.h"

Scene::Scene() : rotation(0), scale(1) {
}

void Scene::add(std::shared_ptr<RenderObject> object) {
	renderObjects.push_back(object);
}

const void Scene::lighting() {
	GLfloat lp1[4] = {10, 5, 10,  1};
	GLfloat white[4] = {1.0f,  1.0f,  1.0f,  1.0f};
	GLfloat ambient[4] = {0.3f,  0.3f,  0.3f,  1.0f};

	glLightfv(GL_LIGHT1, GL_POSITION, lp1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  white);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
}

const void Scene::setMaterialColor(GLfloat r, GLfloat g, GLfloat b) {
	GLfloat dif[4] = {r, g, b, 1};
	GLfloat amb[4] = {0.5f * r, 0.5f * g, 0.5f * b, 1.0f};
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
}

const void Scene::draw() {
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

	// Modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Camera
	glTranslatef(0, 0, -10); // Move 10 units backwards in z, since camera is at origin
	// Rotation
	glRotatef(10, 1, 0, 0);
	glRotatef(rotation, 0, 1, 0);
	// Translation
	glTranslatef(0, -2, 0);
	// Scale
	glScalef(scale, scale, scale);

	// Objects
	setMaterialColor(0, 1, 1);
	//gluSphere(gluNewQuadric(), 2, 50, 50);
	for (auto& object : renderObjects) {
		object->draw();
	}
}