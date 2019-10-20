// Implementation of trackClass

#include "trackClass.h"

/* Constructor
 * Preconditions: None
 * Postconditions: Draws a track using gluDisks
*/
trackGL:: trackGL() {
  GLUquadricObj *quad = gluNewQuadric();
  gluQuadricDrawStyle(quad, GLU_FILL);
  glColor3fv(innerColor);
	gluDisk(quad, 0.0, TRACK_INNER_RADIUS, 50, 5);
	glColor3fv(trackColor);
	gluDisk(quad, TRACK_INNER_RADIUS, TRACK_INNER_RADIUS + TRACK_WIDTH, 50, 5);
}
