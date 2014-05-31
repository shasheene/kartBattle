/*
 * car.h
 */

#ifndef CAR_H
#define CAR_H

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <stack>

using namespace std; 

#include "glLibAndConst.h"

//our rotating world angle
GLfloat angle=0.0;

//used for our model 


char carFilepath[] = "car/car-n.obj";
char *model_name=carFilepath;


struct model_info {
//vertex data and indices
GLuint vbo_model_vertices;
GLuint *ibo_model_elements; //array of ibo "names" one for each group
GLuint **ibo_model_buffer; //array of ibo_buffers - one buffer for each group
//texture data and indices
GLuint vbo_model_texcoords;
GLuint *model_texture_ids; //array of texture "names" one for each group
GLfloat * vpositions;
GLfloat * tcoords;
} my_model;

GLMmodel* model_ptr = NULL;
//our shader program and it's related info
struct shader_program_info {
GLuint program;
GLuint attribute_coord3d;
GLuint attribute_texcoord;
//GLuint uniform_Kd;
GLuint uniform_mvp;
GLuint uniform_texture;
} my_program;

//our transforms
glm::mat4 current_mvp=glm::mat4(1.0f); //initialise to 0

int init_resources();


#endif
