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

		float headHeight;
		float bodyHeight;
		float upperArmHeight;
		float forearmHeight;
		float handHeight;
		float thighHeight;
		float calfHeight;
		float footHeight;

		/* Constructor
		 * Preconditions: None
		 * Postconditions: Creates a person object with the given attributes
		 */
		Person(int x, int z, float height, float runnerDirection);

		/* Destructor
		 * Preconditions: Person object must have been instantiated
		 * Postconditions: None - no variables were dynamically allocated
		 */
		~Person();

		/* Draws the head of the stick figure
		 * Preconditions: Constructor must be called
		 * Post conditions: Creates the head of a stick figure using a sphere
		 */
		void drawHead(float headY);

		/* Draws the body of the stick figure
		 * Preconditions: Constructor must be called
		 * Post conditions: Creates the body of a stick figure using a cylinder
		 */
		void drawBody(float bodyY);

		/* Draws the arms of the stick figure
		 * Preconditions: Constructor must be called
		 * Post conditions: Creates the arms of a stick figure using cylinders
		 */
		void drawArms(float upperArmY, float forearmY, float handY);

		/* Draws the legs of the stick figure
		 * Preconditions: Constructor must be called
		 * Post conditions: Creates the legs of a stick figure using cylinders
		 */
		void drawLegs(float thighY, float calfY, float footY);

	private:
		float height;
		float runnerDirection;
		float runningAngle;
		int x;
		int z;
};

#endif
