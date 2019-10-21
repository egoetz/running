// Implementation of trackClass

#include "trackClass.h"

/* Constructor
 * Preconditions: None
 * Postconditions: Draws a track using gluDisks
*/
trackGL:: trackGL() {
  GLUquadricObj *quad = gluNewQuadric();
  gluQuadricDrawStyle(quad, GLU_FILL);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, innerColor);
	gluDisk(quad, 0.0, TRACK_INNER_RADIUS, 50, 5);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, trackColor);
	gluDisk(quad, TRACK_INNER_RADIUS, TRACK_INNER_RADIUS + TRACK_WIDTH, 50, 5);
}
