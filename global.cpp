/*
 * global.cpp
 */

#include "global.h"

GLfloat angle=0.0;
struct model_info my_model;
struct shader_program_info my_program;
GLMmodel* model_ptr = NULL;
glm::mat4 current_mvp=glm::mat4(1.0f); //initialise to 0
