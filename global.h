/*
 * global.h
 */

#ifndef GLOBAL
#define GLOBAL

#include "glLibAndConst.h"
#include "car.h"

extern GLfloat angle;
extern struct model_info my_model;
extern struct shader_program_info my_program;
extern glm::mat4 current_mvp; //initialise to 0
extern GLMmodel* model_ptr;

extern GLfloat pi;

GLfloat degToRad (GLfloat deg);
GLfloat radToDeg (GLfloat rad);



#endif

