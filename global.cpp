/*
 * global.cpp
 */

#include "global.h"

GLfloat angle=0.0;
struct model_info my_model;
struct shader_program_info my_program;
GLMmodel* model_ptr = NULL;
glm::mat4 current_mvp=glm::mat4(1.0f); //initialise to 0

GLfloat pi=3.14159265359;

GLfloat degToRad (GLfloat deg) {
  return (deg*pi/180);
}

GLfloat radToDeg (GLfloat rad) {
  return (rad*180/pi);
}

