#include "Person.h"
#include <iostream>

#define PI 3.14159265
const GLfloat RAD_TO_DEGREE = 180 / PI;
const int SLICES = 50;
const int STACKS = 50;

using namespace std;

Person::Person(int x, int z, float height, float time): x(x), z(z), height(height), time(time){
	headHeight = height / 8;
	bodyHeight = headHeight * (2 + 6)/ 3;
	upperArmHeight = headHeight * 5 / 3;
	forearmHeight = headHeight * 4 / 3;
	handHeight = headHeight * 1 / 5;
	thighHeight = headHeight * 2;
	calfHeight = headHeight * 5 / 3;
	footHeight = headHeight * 1 / 3;

	runningAngle = 0;// RAD_TO_DEGREE * time;

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
		//glRotatef(-time,0.0, 1.0, 0.0);
		drawHead(headY);
		drawBody(bodyY);
		drawArms(upperArmY, forearmY, handY);
		drawLegs(thighY, calfY, footY);
	glPopMatrix();
}
Person::~Person(){}

void Person::drawHead(float headY){
	GLUquadric *quad = gluNewQuadric();
	gluQuadricDrawStyle(quad, GLU_FILL);
	float radius = headHeight / 2;
	glPushMatrix();
		glTranslatef(x, headY, z);
		//glRotatef(runningAngle,0,1,0);
		glScalef(radius / headHeight, 1, 1);
		gluSphere(quad, headHeight, SLICES, STACKS);
	glPopMatrix();
}


void Person::drawBody(float bodyY){
	GLUquadric *quad = gluNewQuadric();
	gluQuadricDrawStyle(quad, GLU_FILL);
	float radius = headHeight / 2;
	//cout << headHeight << ' ' << bodyHeight << ' ' << radius << endl;
	glPushMatrix();
		glTranslatef(x, bodyY, z);
		//glRotatef(runningAngle,0,-1,0);
		glRotatef(90,1,0,0);
		gluCylinder(quad, radius, radius, bodyHeight, SLICES, STACKS);
	glPopMatrix();
}


void Person::drawArms(float upperArmY, float forearmY, float handY){
	GLUquadric *quad = gluNewQuadric();
	gluQuadricDrawStyle(quad, GLU_FILL);

	float radius = headHeight / 2;
	float upperArmRadius = radius / 4;
	float forearmRadius = radius / 5;
	float handRadius = radius * 1 / 2;
	for(int i = -1; i <= 1; i += 2){
		float upperArmX = x + i * (radius + upperArmRadius / 2);
		float upperArmDegrees = 90 + (i * 45 * sin(15*time));

		glPushMatrix();
			glTranslatef(upperArmX, upperArmY, z);
			//glRotatef(runningAngle,0,1,0);
			glRotatef(upperArmDegrees,1,0,0);
			glPushMatrix();
				glTranslatef(0, 0, upperArmHeight);
				glRotatef(90+ (-i * 35 * sin(15*time)),1,0,0);

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


void Person::drawLegs(float thighY, float calfY, float footY){
	GLUquadric *quad = gluNewQuadric();
	gluQuadricDrawStyle(quad, GLU_FILL);

	float radius = headHeight / 2;
	float thighRadius = radius / 2;
	float calfRadius = thighRadius * 3 / 4;
	float footRadius = thighRadius * 2;
	
	for(int i = -1; i <= 1; i += 2){
		float thighX = x + i * (radius / 2 + thighRadius / 2);
		float thighDegrees = 120 + (-i * 30 * sin(15*time));

		glPushMatrix();
			glTranslatef(thighX, thighY, z);
			//glRotatef(runningAngle,0,1,0);
			glRotatef(thighDegrees,1,0,0);
			glPushMatrix();
				glTranslatef(0, 0, thighHeight);
				glRotatef(-90 + (-i * 35 * sin(15*time)),1,0,0);

				glPushMatrix();
					glTranslatef(0, -calfRadius, calfHeight);
					glRotatef((-i * 15 * sin(15*time)),1,0,0);
					glScalef(.3, 1, 1);

					gluCylinder(quad, footRadius, footRadius, footHeight, SLICES, STACKS);
				glPopMatrix();

				gluCylinder(quad, calfRadius, calfRadius, calfHeight, SLICES, STACKS);
			glPopMatrix();
			
			gluCylinder(quad, thighRadius, calfRadius, thighHeight, SLICES, STACKS);
		glPopMatrix();
	}
}
