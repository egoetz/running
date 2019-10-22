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

// Constants
const GLfloat PI = 3.1415926f;
const GLfloat TWO_PI = 2.0 * PI;
const GLfloat RAD_TO_DEGREE = 180 / PI;
const GLfloat TRACK_INNER_RADIUS = 50.0;
const GLfloat TRACK_WIDTH = 15.0;
const GLfloat TRACK_MIDDLE = TRACK_INNER_RADIUS + 0.5 * TRACK_WIDTH;

// Global variables.
GLfloat runnerDirection = 0.0;
GLfloat runnerXPos = 0.0;
GLfloat runnerYPos = 57.5;
GLfloat zoom = 50.0;
GLint windowWidth = 1600;
GLint windowHeight = 1200;
GLfloat runnerColor[3] = {0.0, 0.0, 0.0};

/* Display callback function
 * Preconditions: OpenGL state must be initialized
 * Postconditions: Displays a track with a stick figure running around it
 */
void display (void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		100.0, 10.0, 10.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 1.0 );
	trackGL track;
	glTranslatef(0.0, 0.0, 0.6);
	glRotatef(90, 1.0, 0.0, 0.0);
	//glRotatef(RAD_TO_DEGREE * runnerDirection, 0.0, 0.0, -1.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, runnerColor);
	Person runner(runnerXPos,runnerYPos, 15, runnerDirection);
	glutSwapBuffers();
}

/* Sets the projection when zoom or window shape change
 * Preconditions: A glut window must exist and have been initialized
 * Postconditions: Sets new gluPerspective based on current zoom and
 * window shape
 */
void set_projection () {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(zoom, GLfloat(windowWidth) / GLfloat(windowHeight),
		1.0, 500.0);
}

/* Reshape callback function
 * Preconditions: A glut window must exist and have been initialized
 * Postconditions: Reshapes the image to match the new window shape
 */
void reshape (GLint new_width, GLint new_height) {
	windowWidth = new_width;
	windowHeight = new_height;
	glViewport(0, 0, windowWidth, windowHeight);
	set_projection();
}

/* Keyboard callback function
 * Preconditions: glutKeyboardFunc(keyboard) must be called
 * Postconditions: User can exit the program by pressing the escape key
 */
void keyboard (unsigned char key, int x, int y) {
	switch (key) {
		case 27:
			exit(0);
	}
}

/* Initialize openGL state
 * Preconditions: Glut window management must have been set
 * Postconditions: Color and depth buffers are cleared and lighting is set
 */
void init(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.529, 0.808, 0.922, 1.0);

	GLfloat light_position[] = { 0.0, 0.0, 25.0, 0.0 };

	GLfloat light_ambient[] = {1.0,1.0,1.0,1.0};


	glShadeModel (GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);

	set_projection();

}

/* Idle callback function
 * Preconditions: glutIdleFunc(run) must be called
 * Postconditions: Changes the position of the runner to relocate it
 * around the track
 */
void run(){
	runnerDirection += 0.001f;
	if(runnerDirection > TWO_PI){
		runnerDirection -= TWO_PI;
	}
	runnerXPos = TRACK_MIDDLE * sin(runnerDirection);
	runnerYPos = TRACK_MIDDLE * cos(runnerDirection);

	glutPostRedisplay();
}

/*
 * Preconditions: Glut and OpenGL must be installed
 * Postconditions: Creates a glut window that displays a stick-figure runner
 * running around a track
 */
int main (int argc, char *argv[]) {

	// Initialize GLUT.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Run");

	// Register callbacks.
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(run);
	glutPassiveMotionFunc(mouse);
	glutKeyboardFunc(keyboard);

	glEnable(GL_DEPTH_TEST);

	init();

	glutMainLoop();
	return 0;
}
