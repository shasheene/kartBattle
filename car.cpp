/*
 * car.cpp
 */

#include "car.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#ifndef GLM_MOD_H
 #define GLM_MOD_H
// Nate Robbins glm 
#include "lib/glm_mod.h"
#endif
#include "lib/glm_mod.c"

#define T(x) (model->triangles[(x)])

char carFilepath[] = "car/car-n.obj";
char *model_name=carFilepath;
/*
//global variables from car.h: (defined using extern keyword)
GLfloat angle;
struct model_info my_model;
struct shader_program_info my_program;
glm::mat4 current_mvp; //initialise to 0
GLMmodel* model_ptr;
*/

int init_resources()
{
   std:cerr << "opening model " << model_name << std::endl;
    model_ptr = glmReadOBJ(model_name);
    glmUnitize(model_ptr); //scale to unit cube - may not be best if more than one object in file....
// don't need normals until do lighting...    glmFacetNormals(model_ptr);
//ditto    glmVertexNormals(model_ptr, 90.0);

//we are going to have to re-organise the data. We can't have two indices (one for texture and one for position) 
//so we are going to have to create a new buffer for positions ordered by model triangles ppp ppp ppp etc
//and one for texturecoords tt tt tt etc
//we will then use the *triangle* index of the group to create the indices in these buffers for drawing a group....
my_model.vpositions=  (GLfloat *) malloc(sizeof(GLfloat)*model_ptr->numtriangles*3*3);
my_model.tcoords=  (GLfloat *) malloc(sizeof(GLfloat)*model_ptr->numtriangles*3*2);
//loop through the entire model triangles and put in the actual data
for (int i=0;i<model_ptr->numtriangles;i++)
   {
     my_model.tcoords[i*2*3+0]=model_ptr->texcoords[model_ptr->triangles[i].tindices[0]*2+0];
     my_model.tcoords[i*2*3+1]=model_ptr->texcoords[model_ptr->triangles[i].tindices[0]*2+1];

     my_model.tcoords[i*2*3+2]=model_ptr->texcoords[model_ptr->triangles[i].tindices[1]*2+0];
     my_model.tcoords[i*2*3+3]=model_ptr->texcoords[model_ptr->triangles[i].tindices[1]*2+1];

     my_model.tcoords[i*2*3+4]=model_ptr->texcoords[model_ptr->triangles[i].tindices[2]*2+0];
     my_model.tcoords[i*2*3+5]=model_ptr->texcoords[model_ptr->triangles[i].tindices[2]*2+1];

     my_model.vpositions[i*3*3+0]=model_ptr->vertices[model_ptr->triangles[i].vindices[0]*3+0];
     my_model.vpositions[i*3*3+1]=model_ptr->vertices[model_ptr->triangles[i].vindices[0]*3+1];
     my_model.vpositions[i*3*3+2]=model_ptr->vertices[model_ptr->triangles[i].vindices[0]*3+2];

     my_model.vpositions[i*3*3+3]=model_ptr->vertices[model_ptr->triangles[i].vindices[1]*3+0];
     my_model.vpositions[i*3*3+4]=model_ptr->vertices[model_ptr->triangles[i].vindices[1]*3+1];
     my_model.vpositions[i*3*3+5]=model_ptr->vertices[model_ptr->triangles[i].vindices[1]*3+2];

     my_model.vpositions[i*3*3+6]=model_ptr->vertices[model_ptr->triangles[i].vindices[2]*3+0];
     my_model.vpositions[i*3*3+7]=model_ptr->vertices[model_ptr->triangles[i].vindices[2]*3+1];
     my_model.vpositions[i*3*3+8]=model_ptr->vertices[model_ptr->triangles[i].vindices[2]*3+2];

   }
  // get a name for my vertex vbo
  glGenBuffers(1, &(my_model.vbo_model_vertices));
 //now we say we will refer to this buffer
  glBindBuffer(GL_ARRAY_BUFFER, my_model.vbo_model_vertices);
 //for this buffer we say what the buffer looks like and where it lives
  glBufferData(GL_ARRAY_BUFFER, sizeof(*(my_model.vpositions))*(model_ptr->numtriangles)*3*3, my_model.vpositions, GL_STATIC_DRAW);
  // get a name for my vertex texture vbo
  glGenBuffers(1, &(my_model.vbo_model_texcoords));
 //now we say we will refer to this buffer
  glBindBuffer(GL_ARRAY_BUFFER, my_model.vbo_model_texcoords);
 //for this buffer we say what the buffer looks like and where it lives
  glBufferData(GL_ARRAY_BUFFER, sizeof(*(my_model.tcoords))*(model_ptr->numtriangles)*3*2, my_model.tcoords, GL_STATIC_DRAW);

  std::cerr << "allocated buffers for texcoords: " << model_ptr->numtexcoords << " and vertices: " <<  model_ptr->numvertices  << std::endl;
  //get names for my group ibo's
   my_model.ibo_model_elements= (GLuint *) malloc(sizeof(GLuint)*model_ptr->numgroups);
  glGenBuffers(model_ptr->numgroups, my_model.ibo_model_elements);
  //and allocated array of pts to ibo buffers
   my_model.ibo_model_buffer= (GLuint **) malloc(sizeof(GLuint *)*model_ptr->numgroups);
  //space for texture "names"
   my_model.model_texture_ids= (GLuint *) malloc(sizeof(GLuint)*model_ptr->numgroups);
  
    GLMgroup* group=model_ptr->groups;
    int current_group=0;
    while (group)
      { if ((group->numtriangles) ==0 ) //have nothing to draw
          {
        group=group->next;
        current_group++;
          break;
          }
   //if look at code - for some reason the numtriangles is one more than actual and vertex,normals, and texcoords arrays have nothing in first 3 places in array.....almost certainly because OBJ indices start from 1 whereas C indices start from 0
   std::cerr << "will draw  " << group->numtriangles << " triangles" << std::endl;
   std::cerr << "from (for all groups)  " << model_ptr->numvertices << " vertices" << std::endl;
   if (model_ptr->materials)
     {
   std::cerr << "with material Kd " << 
     model_ptr->materials[group->material].diffuse[0]  << " "
      <<
     model_ptr->materials[group->material].diffuse[1]  << " "
       <<
     model_ptr->materials[group->material].diffuse[2] 
       << std::endl;
    if (model_ptr->materials[group->material].map_Kd_file)
       {
	 std::cerr << "and map Kd file " << model_ptr->materials[group->material].map_Kd_file << std::endl;

	my_model.model_texture_ids[current_group]= SOIL_load_OGL_texture
    (
     model_ptr->materials[group->material].map_Kd_file,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
      SOIL_FLAG_INVERT_Y | SOIL_FLAG_TEXTURE_REPEATS
     );
      if (my_model.model_texture_ids[current_group])
         std::cerr << " loaded texture " << model_ptr->materials[group->material].map_Kd_file << "ok" << std::endl;
      else
         std::cerr << " failed to load texture " << model_ptr->materials[group->material].map_Kd_file << std::endl;
       }
     } //end group not empty
    
//now the data for a group is actually an index into a triangle which is then something that gives three indices into our vertex array. 

my_model.ibo_model_buffer[current_group] = (GLuint *) malloc(sizeof(GLuint)*3*(group->numtriangles));
for (int i=0;i<(group->numtriangles);i++)
   {
     my_model.ibo_model_buffer[current_group][3*i+0]=group->triangles[i]*3+0;
     my_model.ibo_model_buffer[current_group][3*i+1]=group->triangles[i]*3+1;
     my_model.ibo_model_buffer[current_group][3*i+2]=group->triangles[i]*3+2;
   }
 //now we say we will refer to this buffer
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_model.ibo_model_elements[current_group]);
 //for this buffer we say what the buffer looks like and where it lives
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*3*(group->numtriangles), my_model.ibo_model_buffer[current_group], GL_STATIC_DRAW);

        group=group->next;
        current_group++;

   
   } //end looping over groups

const  GLchar * my_vertex_shaders[] = {
//vertex shader 0
"attribute vec3 coord3d;\n \
attribute vec2 vtexcoords; \n \
uniform mat4 mvp;\n \
varying vec2 texCoords;\n \
\n \
void main(void) {\n \
  gl_Position = mvp * vec4(coord3d, 1.0);\n \
  texCoords=vtexcoords; \n \
}\n" 
};
const  GLchar * my_fragment_shaders[] = {
//fragement shader 0
"varying vec3 f_color; \n \
uniform sampler2D mytexture; \n \
varying vec2 texCoords;\n \
 \n \
void main(void) { \n \
  gl_FragColor = texture2D(mytexture,texCoords); \n \
}\n "
};
  GLint compile_ok= GL_FALSE;
  GLint link_ok = GL_FALSE;

  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(vs,1, (const GLchar **) &(my_vertex_shaders[0]),NULL);
  glCompileShader(vs);
  glGetShaderiv(vs, GL_COMPILE_STATUS, &compile_ok);
  if ( !compile_ok ) {
	    cerr <<  " failed to compile:" << endl;
	    GLint  logSize;
	    glGetShaderiv( vs, GL_INFO_LOG_LENGTH, &logSize );
	    char* logMsg = new char[logSize];
	    glGetShaderInfoLog( vs, logSize, NULL, logMsg );
	    cerr << logMsg << endl;
	    delete [] logMsg;

	    exit( EXIT_FAILURE );
	}
  glShaderSource(fs,1, (const GLchar **) &(my_fragment_shaders[0]),NULL);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &compile_ok);
  if ( !compile_ok ) {
	    cerr <<  " failed to compile:" << endl;
	    GLint  logSize;
	    glGetShaderiv( fs, GL_INFO_LOG_LENGTH, &logSize );
	    char* logMsg = new char[logSize];
	    glGetShaderInfoLog( fs, logSize, NULL, logMsg );
	    cerr << logMsg << endl;
	    delete [] logMsg;

	    exit( EXIT_FAILURE );
	}
  my_program.program = glCreateProgram();
  glAttachShader(my_program.program, vs);
  glAttachShader(my_program.program, fs);
  glLinkProgram(my_program.program);
  glGetProgramiv(my_program.program, GL_LINK_STATUS, &link_ok);
 if ( !link_ok ) {
	cerr << "Shader program failed to link" << endl;
	GLint  logSize;
	glGetProgramiv( my_program.program, GL_INFO_LOG_LENGTH, &logSize);
	char* logMsg = new char[logSize];
	glGetProgramInfoLog( my_program.program, logSize, NULL, logMsg );
	cerr << logMsg << endl;
	delete [] logMsg;

	exit( EXIT_FAILURE );
    }



  const char* attribute_name;
  attribute_name = "coord3d";
  my_program.attribute_coord3d = glGetAttribLocation(my_program.program, attribute_name);
  if (my_program.attribute_coord3d == -1) {
    cerr << "Could not bind attribute " << attribute_name << endl;
    return 0;
  }
  attribute_name = "vtexcoords";
  my_program.attribute_texcoord = glGetAttribLocation(my_program.program, attribute_name);
  if (my_program.attribute_texcoord == -1) {
    cerr << "Could not bind attribute " << attribute_name << endl;
    return 0;
  }
  const char* uniform_name;
  uniform_name = "mvp";
  my_program.uniform_mvp = glGetUniformLocation(my_program.program, uniform_name);
  if (my_program.uniform_mvp == -1) {
    cerr << "Could not bind uniform " <<  uniform_name << endl;
    return 0;
  }

   uniform_name = "mytexture";
  my_program.uniform_texture = glGetUniformLocation(my_program.program, uniform_name);
  if (my_program.uniform_texture == -1) {
//    fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
    return 0;
  }
  return 1;
}
