#include "Scene.h"

Scene::Scene() {
	rotation = 0;
	scale = 1;
}

void Scene::add(std::shared_ptr<RenderObject> object) {
	renderObjects.push_back(object);
}

void Scene::lighting() {
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

void Scene::setMaterialColor(GLfloat r, GLfloat g, GLfloat b) {
	GLfloat dif[4] = {r, g, b, 1};
	GLfloat amb[4] = {0.5f * r, 0.5f * g, 0.5f * b, 1};
	//GLfloat spe[4] = {0.6, 0.6, 0.6, 1};

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spe);
	//glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 20);
}

void Scene::draw() {
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
	glRotatef(rotation, 0, 1, 0);

	glTranslatef(0, -2, 0);
	glScalef(scale, scale, scale);

	setMaterialColor(1, 1, 1);
	//gluSphere(gluNewQuadric(), 2, 50, 50);

	// Objects
	for (auto& object : renderObjects) {
		object->draw();
	}
}
