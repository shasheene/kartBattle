/*
 * car.h
 */

#ifndef CAR_H
#define CAR_H

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <stack>

#include "glLibAndConst.h"

#ifndef GLM_MOD_H
 #define GLM_MOD_H
// Nate Robbins glm 
#include "lib/glm_mod.h"
#endif

#include "global.h"

using namespace std; 

//our rotating world angle
//GLfloat angle=0.0;

//used for our model 


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
};
//struct model_info my_model;

//GLMmodel* model_ptr = NULL;
//our shader program and it's related info
struct shader_program_info {
GLuint program;
GLuint attribute_coord3d;
GLuint attribute_texcoord;
//GLuint uniform_Kd;
GLuint uniform_mvp;
GLuint uniform_texture;
};

//struct shader_program_info my_program;

//our transforms
//glm::mat4 current_mvp=glm::mat4(1.0f); //initialise to 0

int init_resources();


#endif
