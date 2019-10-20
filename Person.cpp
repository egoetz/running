#include "Person.h"
#include <iostream>

const int SLICES = 50;
const int STACKS = 50;

using namespace std;

Person::Person(int x, int z, float height): x(x), z(z), height(height){
	headHeight = height / 8;
	bodyHeight = headHeight * (2 + 6)/ 3;
	upperArmHeight = headHeight * 5 / 3;
	forearmHeight = headHeight * 4 / 3;
	handHeight = headHeight * 2 / 3;
	thighHeight = headHeight * 2;
	calfHeight = headHeight * 5 / 3;
	footHeight = headHeight * 1 / 3;

	float headY = footHeight + calfHeight + thighHeight + bodyHeight;
	float bodyY = footHeight + calfHeight + thighHeight + bodyHeight / 2;
	float upperArmY = footHeight + calfHeight + thighHeight / 4 +
				handHeight + forearmHeight + upperArmHeight / 2;
	float forearmY = footHeight + calfHeight + thighHeight / 4 +
				handHeight + forearmHeight / 2;
	float handY = footHeight + calfHeight + thighHeight / 4 +
				handHeight / 2;
	float thighY = footHeight + calfHeight + thighHeight / 2;
	float calfY =  footHeight + calfHeight / 2;
	float footY = footHeight/2;

	
	drawHead(headY);
	drawBody(bodyY);
	drawArms(upperArmY, forearmY, handY);
	drawLegs(thighY, calfY, footY);
}
Person::~Person(){}

void Person::drawHead(float headY){
	GLUquadric *quad = gluNewQuadric();
	gluQuadricDrawStyle(quad, GLU_FILL);
	float radius = headHeight / 2;
	glPushMatrix();
		glTranslatef(x, headY, z);
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
	float handRadius = radius / 3;
	for(int i = -1; i <= 1; i += 2){
		glPushMatrix();
			glTranslatef(x + i * (radius + upperArmRadius / 2), upperArmY, z);
			glRotatef(90,1,0,0);
			gluCylinder(quad, upperArmRadius, forearmRadius, upperArmHeight, SLICES, STACKS);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(x + i * (radius + upperArmRadius / 2), forearmY, z);
			glRotatef(90,1,0,0);
			gluCylinder(quad, forearmRadius, forearmRadius, forearmHeight, SLICES, STACKS);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(x + i * (radius + upperArmRadius / 2), handY, z);
			glRotatef(90,1,0,0);
			gluCylinder(quad, handRadius, handRadius, handHeight, SLICES, STACKS);
		glPopMatrix();
	}
}


void Person::drawLegs(float thighY, float calfY, float footY){
	GLUquadric *quad = gluNewQuadric();
	gluQuadricDrawStyle(quad, GLU_FILL);

	float radius = headHeight / 2;
	float thighRadius = radius / 2;
	float calfRadius = thighRadius * 3 / 4;
	float footRadius = thighRadius * 2 / 3;
	for(int i = -1; i <= 1; i += 2){
		glPushMatrix();
			glTranslatef(x + i * thighRadius / 2, thighY, z);
			glRotatef(90,1,0,0);
			gluCylinder(quad, thighRadius, calfRadius, thighHeight, SLICES, STACKS);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(x + i * thighRadius / 2, calfY, z);
			glRotatef(90,1,0,0);
			gluCylinder(quad, calfRadius, footRadius, calfHeight, SLICES, STACKS);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(x + i * thighRadius / 2, footY, z);
			glRotatef(90,1,0,0);
			gluCylinder(quad, footRadius, footRadius, footHeight, SLICES, STACKS);
		glPopMatrix();
	}
}
