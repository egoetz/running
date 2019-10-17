// Class to create a running track for our stick figure to run around

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <math.h>
#include <stdlib.h>



class trackGL{

  public:
    // Pointer for quadric objects.

    // Constants
    const GLfloat TRACK_INNER_RADIUS = 50.0;
    const GLfloat TRACK_WIDTH = 15.0;

    const GLfloat trackColor[3] = {0.658f, 0.220f, 0.173f};
    const GLfloat innerColor[3] = {0.4f, 0.6f, 0.196f};


    /* Constructor
     * Preconditions: None
     * Postconditions: Draws a track using gluDisks
    */
    trackGL();

    // Destructor - doesn't need to do anything
    ~trackGL() {};


};
