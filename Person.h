#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifndef PERSON_H
#define PERSON_H

class Person{
	public:

		//everything of interest is done in the read
		float headHeight;
		float bodyHeight;
		float upperArmHeight;
		float forearmHeight;
		float handHeight;
		float thighHeight;
		float calfHeight;
		float footHeight;

		Person(int x, int z, float height, float time);
		~Person();
		void Run();

		void drawHead(float headY);
		void drawBody(float bodyY);
		void drawArms(float upperArmY, float forearmY, float handY);
		void drawLegs(float thighY, float calfY, float footY);
	private:
		float height;
		float time;
		float runningAngle;
		int x;
		int z;
};

#endif
