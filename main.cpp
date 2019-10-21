#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "trackClass.h"
#include "Person.h"

using namespace std;

// Dimensions, etc.
const GLfloat PI = 3.1415926f;
const GLfloat TWO_PI = 2.0 * PI;
const GLfloat TRACK_INNER_RADIUS = 50.0;
const GLfloat TRACK_WIDTH = 15.0;
const GLfloat TRACK_MIDDLE = TRACK_INNER_RADIUS + 0.5 * TRACK_WIDTH;

enum myview{	// Constants for different views
	DISTANT, INSIDE, OUTSIDE, DRIVER, HOUSE,
	OTHER, BESIDE, BALLOON, HELICOPTER, AUTO
};

myview  view = DISTANT;

GLUquadricObj *p;				// Pointer for quadric objects.

// Global variables.
GLfloat runnerDirection = 0.0;	// Variables for moving car.
GLfloat runnerXPos = 57.5;
GLfloat runnerYPos = 0.0;
GLfloat runnerZPos = 0.0;
GLfloat height = 5.0;			// Viewer's height
GLfloat zoom = 50.0;			// Camera zoom setting
GLfloat mouseX = 0.0;			// Mouse coordinates
GLfloat mouseY = 0.0;
GLint windowWidth = 400;			// Window dimensions
GLint windowHeight = 300;
GLfloat runnerColor[3] = {0.0, 0.0, 0.0};


void display (void) {
	// The display callback function.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		100.0, -50, 10.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 1.0 );

	glPushMatrix();
	glRotatef(90, 1.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, runnerColor);
	Person runner(runnerXPos,runnerYPos, 15, runnerDirection);
	glPopMatrix();

	trackGL track;
	glutSwapBuffers();
}

void set_projection () {
	// Reset the projection when zoom setting or window shape changes.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(zoom, GLfloat(windowWidth) / GLfloat(windowHeight),
		1.0, 500.0);
}

void reshape (GLint new_width, GLint new_height) {
	// Window reshaping function.
	windowWidth = new_width;
	windowHeight = new_height;
	glViewport(0, 0, windowWidth, windowHeight);
	set_projection();
}

void mouse (int x, int y) {
	// Get mouse position and scale values to [-1, 1].
	mouseX = (2.0 * x) / windowWidth - 1.0;
	mouseY = (2.0 * y) / windowHeight - 1.0;
}

void keyboard (unsigned char key, int x, int y) {
	// Keyboard callback function.
	switch (key) {
		case 27:
			exit(0);
	}
}

void init(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.529, 0.808, 0.922, 1.0);

	GLfloat light_position[] = { 0.0, 0.0, 25.0, 0.0 };

	GLfloat light_ambient[] = {1.0,1.0,1.0,1.0};


	glShadeModel (GL_SMOOTH); //smooth shaded polygons

	glLightfv(GL_LIGHT0, GL_POSITION, light_position); //light position

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient); //a slightly red ambient light

	glEnable(GL_LIGHTING); //enable lighting

	glEnable(GL_LIGHT0); //enable the first light = light0

	glEnable(GL_DEPTH_TEST); //depth test performed

	glEnable(GL_NORMALIZE); //if scaling is used then renormalize normals

	// Initialize projection.
	set_projection();

}

void run(){
	runnerDirection += 0.005f;
	if(runnerDirection > TWO_PI){
		runnerDirection -= TWO_PI;
	}
	runnerXPos = TRACK_MIDDLE * sin(runnerDirection);
	runnerYPos = TRACK_MIDDLE * cos(runnerDirection);

	glutPostRedisplay();
}

int main (int argc, char *argv[]) {

	// Initialize GLUT.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Window");

	// Register callbacks.
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(run);
	glutPassiveMotionFunc(mouse);
	glutKeyboardFunc(keyboard);

	// Select GL options.
	glEnable(GL_DEPTH_TEST);
	p = gluNewQuadric();
	gluQuadricDrawStyle(p, GLU_FILL);

	init();



	// "Drive!" he said.
	glutMainLoop();
	return 0;
}
