// Demonstration of different viewpoints.

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif
#ifdef _WIN32
#include <GL/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

// Dimensions, etc.
const GLfloat PI = 3.1415926f;
const GLfloat TWO_PI = 2.0 * PI;
const GLfloat RAD_TO_DEG = 180.0 / PI;
const GLfloat INNER_RADIUS = 90.0;
const GLfloat TRACK_WIDTH = 20.0;
const GLfloat TRACK_MIDDLE = INNER_RADIUS + 0.5 * TRACK_WIDTH;

// Colours
GLfloat grass[] = { 0.0, 0.8f, 0.1f };
GLfloat road[] = { 0.2f, 0.2f, 0.2f };
GLfloat car_body[] = { 0.2f, 0.0, 0.9f };
GLfloat car_axle[] = { 0.4f, 0.4f, 0.4f };
GLfloat car_wheel[] = { 1.0, 0.0, 0.0 };
GLfloat house_wall[] = { 0.7f, 0.4f, 0.2f };
GLfloat house_roof[] = { 0.8f, 0.0, 0.2f };
GLfloat fog[4] = { 0.7f, 0.7f, 0.7f, 1.0 };

enum myview{	// Constants for different views
	DISTANT, INSIDE, OUTSIDE, DRIVER, HOUSE,
	OTHER, BESIDE, BALLOON, HELICOPTER, AUTO
};
 
myview  view = DISTANT;

GLUquadricObj *p;				// Pointer for quadric objects.

// Global variables.
GLfloat car_direction = 0.0;	// Variables for moving car.
GLfloat car_x_pos = 100.0;
GLfloat car_y_pos = 0.0;
GLfloat car_z_pos = 0.0;
GLfloat height = 5.0;			// Viewer's height
GLfloat zoom = 50.0;			// Camera zoom setting
GLfloat mouse_x = 0.0;			// Mouse coordinates
GLfloat mouse_y = 0.0;
GLint win_width = 400;			// Window dimensions
GLint win_height = 300;
bool movie_mode = false;		// Change viewpoint periodically.
long int myclock = 0;
long next_switch_time = 0;
bool fog_enabled = false;		// Fog data.
GLfloat fog_density = 0.01f;
GLfloat bumpiness = 0.0;		// Bumpy road.


void draw_car() {
	// Draw the car: body first.  The car is facing +X,
	// and up is +Z.  Save current transformation.
	glPushMatrix();
		glTranslatef(0.0, 0.0, 3.0);
		glRotatef(95.0, 0.0, 1.0, 0.0);
		glColor3fv(car_body);
		gluCylinder(p, 2.0, 1.0, 12.0, 10, 12);
		gluDisk(p, 0.0, 2.0, 25, 5);
		glTranslatef(0.0, 0.0, 12.0);
		gluDisk(p, 0.0, 1.0, 20, 5);
	glPopMatrix();
	// Rear axle and wheels.
	glPushMatrix();
		glColor3fv(car_axle);
		glTranslatef(3.0, -3.0, 2.0);
		glRotatef(90.0, -1.0, 0.0, 0.0);
		gluCylinder(p, 0.5, 0.5, 6.0, 10, 1);
		glColor3fv(car_wheel);
		gluDisk(p, 0.0, 2.0, 25, 5);
		glTranslatef(0.0, 0.0, 6.0);
		gluDisk(p, 0.0, 2.0, 25, 5);
	glPopMatrix();
	// Front axle and wheels.
	glPushMatrix();
		glTranslatef(9.0, -2.0, 1.0);
		glRotatef(90.0, -1.0, 0.0, 0.0);
		glColor3fv(car_axle);
		gluCylinder(p, 0.3f, 0.3f, 4.0, 10, 1);
		glColor3fv(car_wheel);
		gluDisk(p, 0.0, 1.0, 20, 5);
		glTranslatef(0.0, 0.0, 4.0);
		gluDisk(p, 0.0, 1.0, 20, 5);
	glPopMatrix();
}

void draw_house (GLfloat x, GLfloat y, GLfloat size) {
	// Draw a house.  Save current transformation.
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glScalef(size, size, size);
	glBegin(GL_QUADS);
		glColor3fv(house_wall);
		glVertex3f(1.0, -1.0, 0.0);		// Wall 1
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glVertex3f(1.0, -1.0, 0.0);		// Wall 2
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(-1.0, 1.0, 0.0);		// Wall 3
		glVertex3f(-1.0, 1.0, 1.0);
		glVertex3f(1.0, 1.0, 1.0);
		glVertex3f(1.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, 1.0);	// Wall 4
		glVertex3f(-1.0, 1.0, 1.0);
		glVertex3f(-1.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glColor3fv(house_roof);			// Roof side 1
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(0.0, -1.0, 1.5);
		glVertex3f(0.0, 1.0, 1.5);
		glVertex3f(1.0, 1.0, 1.0);		// Roof side 2
		glVertex3f(-1.0, -1.0, 1.0);
		glVertex3f(0.0, -1.0, 1.5);
		glVertex3f(0.0, 1.0, 1.5);
		glVertex3f(-1.0, 1.0, 1.0);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex3f(-1.0, -1.0, 1.0);	// Roof end 1
		glVertex3f(0.0, -1.0, 1.5);
		glVertex3f(1.0, -1.0, 1.0);
		glVertex3f(-1.0, 1.0, 1.0);		// Roof end 2
		glVertex3f(0.0, 1.0, 1.5);
		glVertex3f(1.0, 1.0, 1.0);
	glEnd();
	glPopMatrix();
}

void draw_scenery () {
	// Draw a patch of grass, a circular road, and some houses.
	glColor3fv(grass);
	gluDisk(p, 0.0, INNER_RADIUS, 50, 5);
	glColor3fv(road);
	gluDisk(p, INNER_RADIUS, INNER_RADIUS + TRACK_WIDTH, 50, 5);
	draw_house(-20.0, 50.0, 5.0);
	draw_house(0.0, 70.0, 10.0);
	draw_house(20.0, -10.0, 8.0);
	draw_house(40.0, 120.0, 10.0);
	draw_house(-30.0, -50.0, 7.0);
	draw_house(10.0, -60.0, 10.0);
	draw_house(-20.0, 75.0, 8.0);
	draw_house(-40.0, 140.0, 10.0);
}

void set_viewpoint () {
	// Use the current viewpoint to display.
	switch (view) {

	case DISTANT:
		// F1 : Static viewpoint and stationary camera.
		//Center observer relative to window width (play with this a bit),
		//at a slight elevation. The observer should be looking at the origin.
		gluLookAt( 
			250.0, 0.0, 20.0 * height,
			0.0, 0.0, 0.0, 
			0.0, 0.0, 1.0 );		draw_scenery();
		// Move to position of car.
		glTranslatef(car_x_pos, car_y_pos, car_z_pos);
		// Rotate so car stays parallel to track.
		glRotatef(RAD_TO_DEG * car_direction, 0.0, 0.0, -1.0);
		draw_car();
		break;
	
	case INSIDE:
		// F2: Static viewpoint inside the track (play with this a bit-
		//where should the observer be located in x, y, z to be
		//inside the track, at the height of the track?; 
		//the camera follows car so use the car's position in x and y.
		gluLookAt( 
			0.0, 0.0, 20.0 * height, 
			car_x_pos, car_y_pos, car_z_pos,
			0.0, 0.0, 1.0 );
		draw_scenery();
		glTranslatef(car_x_pos, car_y_pos, car_z_pos);
		glRotatef(RAD_TO_DEG * car_direction, 0.0, 0.0, -1.0);
		draw_car();
		break;
	
	case OUTSIDE:
		//F3:  Static viewpoint outside the track (play with this a bit-
		//where should the observer be located in x, y, z to be
		//outide the track but at the height of the track; 
		//the camera follows car so use the car's position in x and y;
		gluLookAt( 
			250.0, 0.0, 20.0 * height, 
			car_x_pos, car_y_pos, car_z_pos,
			0.0, 0.0, 1.0 );
		draw_scenery();
		glTranslatef(car_x_pos, car_y_pos, car_z_pos);
		glRotatef(RAD_TO_DEG * car_direction, 0.0, 0.0, -1.0);
		draw_car();
		break;
	
	case DRIVER:
		// F4: Driver's point of view.  gluLookAt() is defined in "car space". Here the
		// camera is fixed to the back of the car (a cylinder centered at (2,0,12)
		//and the driver is looking forward a bit in the positive x direction.
		// After drawing the car, we use inverse transformations to show
		// the scenery.  The same idea is used for OTHER and BESIDE.
		gluLookAt(
			2, 0, 12,
			12, 0, 8,
			0.0, 0.0, 1.0 );
		draw_car();
		glRotatef(RAD_TO_DEG * car_direction, 0.0, 0.0, 1.0);
		glTranslatef(- car_x_pos, - car_y_pos, car_z_pos);
		draw_scenery();
		break;

	case HOUSE:
		//F5: Drive around while looking at a house.  The first rotation
		// couteracts the rotation of the car.  gluLookAt() looks from
		// the driver's position (same as in F4) to the house at (40,120). Be careful
		//when setting the eye position of the camera - you must take into account
		//the current position of the car.
		glRotatef(RAD_TO_DEG * car_direction, 0.0, -1.0, 0.0);
		gluLookAt(
			2, 0, 12,
			40 - car_x_pos, 120 - car_y_pos, 8 - car_z_pos,
			0.0, 0.0, 1.0 );
		draw_car();
		glRotatef(RAD_TO_DEG * car_direction, 0.0, 0.0, 1.0);
		glTranslatef(- car_x_pos, - car_y_pos, car_z_pos);
		draw_scenery();
		break;

	case OTHER:
		//F6: View looking backwards from another car. 
		//Here you want to position the camera in front of the car centered at
		//2,0,12. The x position determines where the car is on the track.
		//you want to look back at the car whose origin is at 0,0 in x,y.
		gluLookAt(
			35, 0, 8,
			0, 0, 8,
			0.0, 0.0, 1.0 );
		draw_car();
		glRotatef(RAD_TO_DEG * car_direction, 0.0, 0.0, 1.0);
		glTranslatef(- car_x_pos, - car_y_pos, 0.0);
		draw_scenery();
		break;
	
	case BESIDE:
		//F7: View from beside the car and outside the track. Position the camera
		// at the side of the car. This requires a positive movement from center of car
		//in x and y. Look at the car from the same x position but use its center in y
		//and its current z position.
		gluLookAt(
			12, 100, 8,
			12, 0, 0,
			0.0, 0.0, 1.0 );
		draw_car();
		glRotatef(RAD_TO_DEG * car_direction, 0.0, 0.0, 1.0);
		glTranslatef(- car_x_pos, - car_y_pos, 0.0);
		draw_scenery();
		break;
	
	case BALLOON:
		//F8: View from a balloon using the mouse position in x and y for camera
		//eye position.Position the camera above the scene looking down to eye position.
		gluLookAt(
			12, 0, 300,
			mouse_x, mouse_y, 8,
			0.0, 0.0, 1.0 );
		draw_scenery();
		glTranslatef(car_x_pos, car_y_pos, car_z_pos);
		glRotatef(RAD_TO_DEG * car_direction, 0.0, 0.0, -1.0);
		draw_car();
		break;

	case HELICOPTER:
		// F9:View from a helicopter. Position using mouse in x and y,
		//always looking at the origin.
		gluLookAt(
			mouse_x, mouse_y, 8,
			0, 0, 0,
			0.0, 0.0, 1.0 );
		draw_scenery();
		glTranslatef(car_x_pos, car_y_pos, car_z_pos);
		glRotatef(RAD_TO_DEG * car_direction, 0.0, 0.0, -1.0);
		draw_car();
		break;
	}
}

void display (void) {
	// The display callback function.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	set_viewpoint();
	glutSwapBuffers();
}

void set_projection () {
	// Reset the projection when zoom setting or window shape changes.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(zoom, GLfloat(win_width) / GLfloat(win_height), 
		1.0, 500.0);
}

void reshape (GLint new_width, GLint new_height) {
	// Window reshaping function.
	win_width = new_width;
	win_height = new_height;
	glViewport(0, 0, win_width, win_height);
	set_projection();
}

void drive () {
	// Idle callback function moves the car.  Since this function 
	// posts redisplay whenever there is nothing else to do, 
	// we do not need any other calls to glutPostRedisplay().
	car_direction += 0.0005f;
	if (car_direction > TWO_PI) 
		car_direction -= TWO_PI;
	car_x_pos = TRACK_MIDDLE * sin(car_direction);
	car_y_pos = TRACK_MIDDLE * cos(car_direction);
	car_z_pos = (bumpiness * rand()) / RAND_MAX;
	if (movie_mode) {
		myclock++;
		if (myclock > next_switch_time) {
			next_switch_time += 2000 + rand() % 200;
			cout << 
				"Time: " << clock() << 
				".  Next change: " << next_switch_time << 
				'.' << endl;
			switch (rand() % 7) {
			case 0:
				view = DISTANT;
				break;
			case 1:
				view = INSIDE;
				break;
			case 2:
				view = OUTSIDE;
				break;
			case 3:
				view = DRIVER;
				break;
			case 4:
				view = HOUSE;
				break;
			case 5:
				view = OTHER;
				break;
			case 6:
				view = BESIDE;
				break;
			}
		}
	}
	glutPostRedisplay();
}

void mouse (int x, int y) {
	// Get mouse position and scale values to [-1, 1].
	mouse_x = (2.0 * x) / win_width - 1.0;
	mouse_y = (2.0 * y) / win_height - 1.0;
}

void set_fog_density (GLfloat density) {
	// Helper function for keyboard callback.
	fog_density = density;
	cout << "Fog density: " << fog_density << endl;
	glFogf(GL_FOG_DENSITY, fog_density);
}

void keyboard (unsigned char key, int x, int y) {
	// Keyboard callback function.
	switch (key) {
	case 'b':
		// Bumpiness control.
		if (bumpiness == 0.0) {
			cout << "Bumpy road!  Use '<' and '>' to change bumpiness." << endl;
			bumpiness = 0.1f;
		}
		else {
			cout << "Smooth road again!" << endl;
			bumpiness = 0.0;
		}
		break;
	case '<':
		// less bumpiness.
		bumpiness /= 2.0;
		break;
	case '>':
		// more bumpiness.
		bumpiness *= 2.0;
		break;

	case 'f':
		// Fog control.
		if (fog_enabled) {
			glDisable(GL_FOG);
			cout << "It's a clear day!" << endl;
			fog_enabled = false;
		}
		else {
			glEnable(GL_FOG);
			cout << "It's foggy: use +/- to change fog density." << endl;
			set_fog_density(0.01f);
			fog_enabled = true;
		}
		break;
	case '+':
		// Increase fog density.
		set_fog_density(2.0 * fog_density);
		break;
	case '-':
		// Decrease fog density.
		set_fog_density(0.5f * fog_density);
		break;
	
	case 27:
		exit(0);
	}
}

void keys (int key, int x, int y) {
	// Set viewpoint from function keys.
	switch (key) {
	
	case GLUT_KEY_LEFT:
		zoom *= 1.2f;
		cout << "Zoom angle = " << zoom << endl;
		set_projection();
		break;
	
	case GLUT_KEY_RIGHT:
		zoom /= 1.2f;
		cout << "Zoom angle = " << zoom << endl;
		set_projection();
		break;
	
	case GLUT_KEY_UP:
		height += 1.0;
		cout << "Height = " << height << endl;
		break;
	
	case GLUT_KEY_DOWN:
		height -= 1.0;
		cout << "Height = " << height << endl;
		break;
	
	case GLUT_KEY_F1:
		movie_mode = false;
		view = DISTANT;
		cout << "Distant, fixed viewpoint." << endl;
		break;
	
	case GLUT_KEY_F2:
		movie_mode = false;
		cout << "View from a panning camera inside the track." << endl;
		view = INSIDE;
		break;
	
	case GLUT_KEY_F3:
		movie_mode = false;
		cout << "View from a panning camera outside the track." << endl;
		view = OUTSIDE;
		break;
	
	case GLUT_KEY_F4:
		movie_mode = false;
		view = DRIVER;
		height = 6.0;
		zoom = 75.0;
		set_projection();
		cout << "View from the driver's seat." << endl;
		break;
	
	case GLUT_KEY_F5:
		movie_mode = false;
		view = HOUSE;
		cout << "Looking at a house while driving around." << endl;
		break;
	
	case GLUT_KEY_F6:
		movie_mode = false;
		view = OTHER;
		cout << "Looking back from the car in front." << endl;
		break;
	
	case GLUT_KEY_F7:
		movie_mode = false;
		view = BESIDE;
		cout << "View from another car." << endl;
		break;
	
	case GLUT_KEY_F8:
		movie_mode = false;
		view = BALLOON;
		cout << "View from a balloon: use mouse to change viewing direction." << endl;
		break;

	case GLUT_KEY_F9:
		movie_mode = false;
		view = HELICOPTER;
		cout << "View from a helicopter: move mouse to fly around." << endl;
		break;
	
	case GLUT_KEY_F10:
		movie_mode = true;
		myclock = 0;
		next_switch_time = 0;
		cout << "Movie mode: views change at random intervals." << endl;
		break;
	
	case GLUT_KEY_END:
		exit(0);
	}
}


int main (int argc, char *argv[]) {

	// Initialize GLUT.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowSize(win_width, win_height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("An OpenGL Window");

	// Register callbacks.
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(drive);
	glutPassiveMotionFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keys);

	// Select GL options.
	glEnable(GL_DEPTH_TEST);
	p = gluNewQuadric();
	gluQuadricDrawStyle(p, GLU_FILL);
	glFogi(GL_FOG_MODE, GL_EXP);
	glFogfv(GL_FOG_COLOR, fog);
	glFogf(GL_FOG_DENSITY, fog_density);
	glClearColor(fog[0], fog[1], fog[2], fog[3]);

	// Initialize projection.
	set_projection();

	// Instruct user.
	cout <<
		"Change view point:"									<< endl <<
		"   Press keys F1, F2, ..., F9.  Movie mode: F10."		<< endl <<
		"Bumpiness:"											<< endl <<
		"   Press 'b' to toggle bumpy road conditions."			<< endl <<
		"   Press '<' ('>') to decrease (increase) bumpiness."	<< endl <<
		"Fog:"													<< endl <<
		"   Press 'f' to toggle fog effect."					<< endl << 
		"   Press '+' ('-') to increase (decrease) fog."		<< endl <<
		"Quit:"													<< endl <<
		"   Press ESC to stop program."							<< endl <<
		"Keep window small for fast action!"					<< endl;

	// "Drive!" he said.
	glutMainLoop();
	return 0;
}
