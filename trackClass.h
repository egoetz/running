// Class to create a running track for our stick figure to run around

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <math.h>
#include <stdlib.h>

#ifndef TRACK_H
#define TRACK_H

class trackGL{

  public:
    // Constants
    const GLfloat TRACK_INNER_RADIUS = 50.0;
    const GLfloat TRACK_WIDTH = 15.0;

    const GLfloat trackColor[3] = {0.75f, 0.20f, 0.17f};
    const GLfloat innerColor[3] = {0.4f, 0.6f, 0.196f};


    /* Constructor
     * Preconditions: None
     * Postconditions: Draws a track using gluDisks
    */
    trackGL();

    // Destructor - doesn't need to do anything
    ~trackGL() {};


};

#endif
