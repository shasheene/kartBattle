/*
 * entity.h
 */

#ifndef ENTITY_H
#define ENTITY_H

#include "glLibAndConst.h"

#ifndef GLM_MOD_H
 #define GLM_MOD_H
// Nate Robbins glm 
#include "lib/glm_mod.h"
#endif

#define T(x) (model->triangles[(x)])


//used for our model 
struct model_info {
//vertex data and indices
GLuint vbo_model_vertices;
GLuint vbo_model_normals;
GLuint *ibo_model_elements; //array of ibo "names" one for each group
GLuint **ibo_model_buffer; //array of ibo_buffers - one buffer for each group
//texture data and indices
GLuint vbo_model_texcoords;
GLuint *model_texture_ids; //array of texture "names" one for each group
GLfloat * vpositions;
GLfloat * npositions;
GLfloat * tcoords;
};

struct shader_program_info {
GLuint program;
GLuint attribute_coord3d;
GLuint attribute_v_normal;
GLuint attribute_texcoord;
//GLuint uniform_Kd;
GLuint uniform_mvp;
GLuint uniform_texture;
GLint uniform_m_3x3_inv_transp, uniform_v_inv, uniform_m;
};

using namespace std; 

class Entity {
public:
  Entity(char*);
  Entity();
  void initialize(char*);
  GLMmodel* model_ptr;
  struct model_info my_model;
  struct shader_program_info my_program;
  GLfloat angle;
};

#endif
