/*
 * display.cpp
 */

#include "display.h"

void display (void) {
  glClear (GL_COLOR_BUFFER_BIT); //clear window
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
  glFlush();
}
