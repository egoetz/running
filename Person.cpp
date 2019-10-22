#include "Person.h"
#include <iostream>

#define PI 3.14159265
const GLfloat RAD_TO_DEGREE = 180 / PI;
const int SLICES = 50;
const int STACKS = 50;

using namespace std;

/* Constructor
 * Preconditions: None
 * Postconditions: Creates a person object with the given attributes
 */
Person::Person(int x, int z, float height, float runnerDirection): x(x), z(z), height(height), runnerDirection(runnerDirection){
	headHeight = height / 8;
	bodyHeight = headHeight * (2 + 6)/ 3;
	upperArmHeight = headHeight * 5 / 3;
	forearmHeight = headHeight * 4 / 3;
	handHeight = headHeight * 1 / 5;
	thighHeight = headHeight * 2;
	calfHeight = headHeight * 5 / 3;
	footHeight = headHeight * 1 / 3;


	float headY = footHeight + calfHeight + thighHeight + bodyHeight;
	float bodyY = footHeight + calfHeight + thighHeight + bodyHeight / 2;
	float upperArmY = footHeight + calfHeight + thighHeight * 4 / 9 +
				handHeight + forearmHeight + upperArmHeight / 2;
	float forearmY = footHeight + calfHeight + thighHeight * 4 / 9 +
				handHeight + forearmHeight / 2;
	float handY = footHeight + calfHeight + thighHeight * 4 / 9	 +
				handHeight / 2;
	float thighY = footHeight + calfHeight + thighHeight / 2;
	float calfY =  footHeight + calfHeight / 2;
	float footY = footHeight/2;

	glPushMatrix();
		drawHead(headY);
		drawBody(bodyY);
		drawArms(upperArmY, forearmY, handY);
		drawLegs(thighY, calfY, footY);
	glPopMatrix();
}

/* Destructor
 * Preconditions: Person object must have been instantiated
 * Postconditions: None - no variables were dynamically allocated
 */
Person::~Person(){}

/* Draws the head of the stick figure
 * Preconditions: Constructor must be called
 * Post conditions: Creates the head of a stick figure using a sphere
 */
void Person::drawHead(float headY){
	GLUquadric *quad = gluNewQuadric();
	gluQuadricDrawStyle(quad, GLU_FILL);
	float radius = headHeight / 2;
	glPushMatrix();
		glTranslatef(x, headY, z);
		glRotatef(-90 + RAD_TO_DEGREE * runnerDirection, 0.0, 1.0, 0.0);
		glScalef(radius / headHeight, 1, 1);
		gluSphere(quad, headHeight, SLICES, STACKS);
	glPopMatrix();
}

/* Draws the body of the stick figure
 * Preconditions: Constructor must be called
 * Post conditions: Creates the body of a stick figure using a cylinder
 */
void Person::drawBody(float bodyY){
	GLUquadric *quad = gluNewQuadric();
	gluQuadricDrawStyle(quad, GLU_FILL);
	float radius = headHeight / 2;
	glPushMatrix();
		glTranslatef(x, bodyY, z);
		glRotatef(-90 + RAD_TO_DEGREE * runnerDirection, 0.0, 1.0, 0.0);
		glRotatef(90,1,0,0);
		gluCylinder(quad, radius, radius, bodyHeight, SLICES, STACKS);
	glPopMatrix();
}

/* Draws the arms of the stick figure
 * Preconditions: Constructor must be called
 * Post conditions: Creates the arms of a stick figure using cylinders
 */
void Person::drawArms(float upperArmY, float forearmY, float handY){
	GLUquadric *quad = gluNewQuadric();
	gluQuadricDrawStyle(quad, GLU_FILL);

	float radius = headHeight / 2;
	float upperArmRadius = radius / 4;
	float forearmRadius = radius / 5;
	float handRadius = radius * 1 / 2;
	for(int i = -1; i <= 1; i += 2){
		float upperArmX = x + i * (radius + upperArmRadius / 2);
		float upperArmDegrees = 90 + (i * 45 * sin(15*runnerDirection));

		glPushMatrix();
			glTranslatef(upperArmX, upperArmY, z);
			glRotatef(-90 + RAD_TO_DEGREE * runnerDirection, 0.0, 1.0, 0.0);
			glRotatef(upperArmDegrees,1,0,0);
			glPushMatrix();
				glTranslatef(0, 0, upperArmHeight);
				glRotatef(90+ (-i * 35 * sin(15*runnerDirection)),1,0,0);

				glPushMatrix();
					glTranslatef(0, 0, forearmHeight + 3 * handRadius);
					glRotatef(90,0,1,0);
					glScalef(2, 1, 1);

					gluCylinder(quad, handRadius, handRadius, handHeight, SLICES, STACKS);
				glPopMatrix();

				gluCylinder(quad, forearmRadius, forearmRadius, forearmHeight, SLICES, STACKS);
			glPopMatrix();

			gluCylinder(quad, upperArmRadius, forearmRadius, upperArmHeight, SLICES, STACKS);
		glPopMatrix();
	}
}

/* Draws the legs of the stick figure
 * Preconditions: Constructor must be called
 * Post conditions: Creates the legs of a stick figure using cylinders
 */
void Person::drawLegs(float thighY, float calfY, float footY){
	GLUquadric *quad = gluNewQuadric();
	gluQuadricDrawStyle(quad, GLU_FILL);

	float radius = headHeight / 2;
	float thighRadius = radius / 2;
	float calfRadius = thighRadius * 3 / 4;
	float footRadius = thighRadius * 2;

	for(int i = -1; i <= 1; i += 2){
		float thighX = x + i * (radius / 2 + thighRadius / 2);
		float thighDegrees = 120 + (-i * 30 * sin(15*runnerDirection));

		glPushMatrix();
			glTranslatef(thighX, thighY, z);
		glRotatef(-90 + RAD_TO_DEGREE * runnerDirection, 0.0, 1.0, 0.0);
			glRotatef(thighDegrees,1,0,0);
			glPushMatrix();
				glTranslatef(0, 0, thighHeight);
				glRotatef(-90 + (-i * 35 * sin(15*runnerDirection)),1,0,0);

				glPushMatrix();
					glTranslatef(0, -calfRadius, calfHeight);
					glRotatef((-i * 15 * sin(15*runnerDirection)),1,0,0);
					glScalef(.3, 1, 1);

					gluCylinder(quad, footRadius, footRadius, footHeight, SLICES, STACKS);
				glPopMatrix();

				gluCylinder(quad, calfRadius, calfRadius, calfHeight, SLICES, STACKS);
			glPopMatrix();

			gluCylinder(quad, thighRadius, calfRadius, thighHeight, SLICES, STACKS);
		glPopMatrix();
	}
}
