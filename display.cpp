/*
 * display.cpp
 */

#include "display.h"
#include "movement.h"
#include "global.h"
#include "shader_utils.h"
#include <cstdio>
#include <iostream>


//Could place these inside of the object files and refer to them from there

	//weapon
  int WeaTimer = 50000;
  int WeaTimer2 = 50000;

GLuint vbo_cube_vertices, vbo_cube_colors;
GLuint ibo_cube_elements;
GLuint program;
GLint attribute_coord3d, attribute_v_color;
GLint uniform_mvp;

glm::mat4 view;


void display (void) {
  movement();
  for (int i=0; i<NUMENTITIES; i++) {
    entitiesArray[i]->update(entitiesArray, NUMENTITIES);
  }


  glm::vec3 axis_y(0, 1, 0);
  glm::mat4 anim;

  glm::mat4 model;
  glm::mat4 projection;
  glm::mat4 current_mvp;

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
	//1st screen top
  glViewport(0, SCREENHEIGHT/2+1, SCREENWIDTH, SCREENHEIGHT/2);
  view = glm::lookAt(player1->viewSrc, player1->viewDest, player1->viewUp);
  projection = glm::perspective(45.0f, 1.0f*SCREENWIDTH/SCREENHEIGHT, 0.1f, 100.0f);
  //Map
  DrawTrack();

  //PLAYER1
  anim = glm::rotate(glm::mat4(1.0f),degToRad(player1->angle), axis_y);

  model = glm::translate(glm::mat4(1.0f), player1->pos);
  current_mvp = projection * view * model * anim;

 drawObject(player1, current_mvp, model, view);

 //PLAYER2
 anim = glm::rotate(glm::mat4(1.0f), degToRad(player2->angle), axis_y);
 model = glm::translate(glm::mat4(1.0f), player2->pos);
 current_mvp = projection * view * model * anim;

 drawObject(player2, current_mvp, model, view);

  //Weapon
  if(WeaTimer < 5000){
	 anim = glm::rotate(glm::mat4(1.0f), degToRad(weapon->angle), axis_y);
	 model = glm::translate(glm::mat4(1.0f), weapon->pos);
	 current_mvp = projection * view * model * anim;

	 drawObject(weapon, current_mvp, model, view);
  }
  if(WeaTimer2 < 5000){
	 anim = glm::rotate(glm::mat4(1.0f), degToRad(weapon2->angle), axis_y);
	 model = glm::translate(glm::mat4(1.0f), weapon2->pos);
	 current_mvp = projection * view * model * anim;

	 drawObject(weapon2, current_mvp, model, view);
  }


//---------------------------


	//2ed screen, bottom
  glViewport(0, 0, SCREENWIDTH, SCREENHEIGHT/2);
  view = glm::lookAt(player2->viewSrc, player2->viewDest, player2->viewUp);
  //Map
  DrawTrack();

  //PLAYER1
  anim = glm::rotate(glm::mat4(1.0f),degToRad(player1->angle), axis_y);
  model = glm::translate(glm::mat4(1.0f), player1->pos);
  current_mvp = projection * view * model * anim;

 drawObject(player1, current_mvp, model, view);

 //PLAYER2
 anim = glm::rotate(glm::mat4(1.0f),degToRad(player2->angle) , axis_y);
 model = glm::translate(glm::mat4(1.0f), player2->pos);
 current_mvp = projection * view * model * anim;

 drawObject(player2, current_mvp, model, view);

  if(WeaTimer < 5000){
	 anim = glm::rotate(glm::mat4(1.0f), degToRad(weapon->angle), axis_y);
	 model = glm::translate(glm::mat4(1.0f), weapon->pos);
	 current_mvp = projection * view * model * anim;

	 drawObject(weapon, current_mvp, model, view);
  }
  if(WeaTimer2 < 5000){
	 anim = glm::rotate(glm::mat4(1.0f), degToRad(weapon2->angle), axis_y);
	 model = glm::translate(glm::mat4(1.0f), weapon2->pos);
	 current_mvp = projection * view * model * anim;

	 drawObject(weapon2, current_mvp, model, view);
  }


 glutSwapBuffers();
}

void drawObject(Entity * my_entity,  glm::mat4 current_mvp, glm::mat4 model, glm::mat4 view){
  struct model_info my_model = my_entity->my_model;
  struct shader_program_info my_program = my_entity->my_program;
  GLMmodel* model_ptr = my_entity->model_ptr;
  
  glUseProgram(my_program.program);

  //Now no matter what group we are going to draw from these vertices..
  glEnableVertexAttribArray(my_program.attribute_coord3d);
  // Describe our vertices array to OpenGL (it can't guess its format automatically)
  glBindBuffer(GL_ARRAY_BUFFER, my_model.vbo_model_vertices);
  glVertexAttribPointer(
    my_program.attribute_coord3d, // attribute
    3,                 // number of elements per vertex, here (x,y,z)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is
    0,                 // no extra data between each position
    0                  // offset of first element
  );
  //Now no matter what group we are going to draw from these normals..
  glEnableVertexAttribArray(my_program.attribute_v_normal);
  // Describe our vertices array to OpenGL (it can't guess its format automatically)
  glBindBuffer(GL_ARRAY_BUFFER, my_model.vbo_model_normals);
  glVertexAttribPointer(
    my_program.attribute_v_normal, // attribute
    3,                 // number of elements per vertex, here (x,y,z)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is
    0,                 // no extra data between each position
    0                  // offset of first element
  );
  //and no matter what group we are going to draw from these texcoords
  glEnableVertexAttribArray(my_program.attribute_texcoord);
  // Describe our texcooords array to OpenGL (it can't guess its format automatically)
  glBindBuffer(GL_ARRAY_BUFFER, my_model.vbo_model_texcoords);
  glVertexAttribPointer(
    my_program.attribute_texcoord, // attribute
    2,                 // number of elements per vertex, here (s,t)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is
    0,                 // no extra data between each position
    0                  // offset of first element
  );

    glUniformMatrix4fv(my_program.uniform_mvp, 1, GL_FALSE, glm::value_ptr(current_mvp));
    glUniformMatrix4fv(my_program.uniform_m, 1, GL_FALSE, glm::value_ptr(model));

 	glm::mat3 m_3x3_inv_transp = glm::transpose(glm::inverse(glm::mat3(model)));
    glUniformMatrix3fv(my_program.uniform_m_3x3_inv_transp, 1, GL_FALSE, glm::value_ptr(m_3x3_inv_transp));
	glm::mat4 v_inv = glm::inverse(view);
	glUniformMatrix4fv(my_program.uniform_v_inv, 1, GL_FALSE, glm::value_ptr(v_inv));

   glActiveTexture(GL_TEXTURE0);
//loop through groups
    GLMgroup* group=model_ptr->groups;
    int current_group=0;
    while (group)
      { 
     if ((group->numtriangles) ==0 ) //have nothing to draw
          {
        group=group->next;
        current_group++;
          break;
          }
  //Push each element in buffer_vertices to the vertex shader
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_model.ibo_model_elements[current_group]);
  //how many elements in what we want to draw?? Sure, we could have kept this as state rather than enquiring now.....
  int size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
  
 //   glUniform3fv(my_program.uniform_Kd,1,(const GLfloat *)  &(model_ptr->materials[group->material].diffuse));

  glBindTexture(GL_TEXTURE_2D, my_model.model_texture_ids[current_group]);
   glUniform1i(my_program.uniform_texture, 0);//0 is GL_TEXTURE

   glDrawElements(GL_TRIANGLES, size/sizeof(GLuint), GL_UNSIGNED_INT, 0);
        group=group->next;
        current_group++;
   }//end looping through groups
}


int init_resources()
{
	//draw map for play
  GLfloat cube_vertices[] = {
    // front
    -20.0, -0.6,  20.0,
     20.0, -0.6,  20.0,
     20.0,  1.0,  20.0,
    -20.0,  1.0,  20.0,
    // back
     20.0, -0.6, -20.0,
    -20.0, -0.6, -20.0,
    -20.0,  1.0, -20.0,
     20.0,  1.0, -20.0,
    // bottom
    -20.0, -0.6, -20.0,
     20.0, -0.6, -20.0,
     20.0, -0.6,  20.0,
    -20.0, -0.6,  20.0,
    // left
    -20.0, -0.6, -20.0,
    -20.0, -0.6,  20.0,
    -20.0,  1.0,  20.0,
    -20.0,  1.0, -20.0,
    // right
     20.0, -0.6,  20.0,
     20.0, -0.6, -20.0,
     20.0,  1.0, -20.0,
     20.0,  1.0,  20.0,
  };

  glGenBuffers(1, &vbo_cube_vertices);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,0);

  GLfloat cube_colors[] = {
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 1.0, 0.0,

    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,
    1.0, 0.0, 0.0,

    0.6, 1.0, 1.0,
    0.6, 1.0, 1.0,
    0.6, 1.0, 1.0,
    0.6, 1.0, 1.0,

    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,

    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,
    0.0, 0.0, 1.0,

  };
  glGenBuffers(1, &vbo_cube_colors);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_colors);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,0);

  GLushort cube_elements[] = {
    // front
    0,  1,  2,
    2,  3,  0,
    // top
    4,  5,  6,
    6,  7,  4,
    // back
    8,  9, 10,
    10, 11,  8,
    // bottom
    12, 13, 14,
    14, 15, 12,
    // left
    16, 17, 18,
    18, 19, 16,
  };
  glGenBuffers(1, &ibo_cube_elements);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

  GLint compile_ok= GL_FALSE;
  GLint link_ok = GL_FALSE;

  GLuint vs, fs;
  if ((vs = create_shader("map.v.glsl", GL_VERTEX_SHADER))   == 0) return 0;
  if ((fs = create_shader("map.f.glsl", GL_FRAGMENT_SHADER)) == 0) return 0;

  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  if (!link_ok) {
    //fprintf(stderr, "glLinkProgram:");
    print_log(program);
    return 0;
  }

  const char* attribute_name1;
  attribute_name1 = "coord3d";
  attribute_coord3d = glGetAttribLocation(program, attribute_name1);
  if (attribute_coord3d == -1) {
    //fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
    return 0;
  }
  attribute_name1 = "v_color";
  attribute_v_color = glGetAttribLocation(program, attribute_name1);
  if (attribute_v_color == -1) {
    //fprintf(stderr, "Could not bind attribute %s\n", attribute_name);
    return 0;
  }
  const char* uniform_name1;
  uniform_name1 = "mvp";
  uniform_mvp = glGetUniformLocation(program, uniform_name1);
  if (uniform_mvp == -1) {
    //fprintf(stderr, "Could not bind uniform %s\n", uniform_name);
    return 0;
  }

}


void DrawTrack()
{
		//Render map on screen
  glUseProgram(program);
  glEnableVertexAttribArray(attribute_coord3d);
  // Describe our vertices array to OpenGL (it can't guess its format automatically)
  glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
  glVertexAttribPointer(
    attribute_coord3d, // attribute
    3,                 // number of elements per vertex, here (x,y,z)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is
    0,                 // no extra data between each position
    0                  // offset of first element
  );

  glEnableVertexAttribArray(attribute_v_color);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_colors);
  glVertexAttribPointer(
    attribute_v_color, // attribute
    3,                 // number of elements per vertex, here (R,G,B)
    GL_FLOAT,          // the type of each element
    GL_FALSE,          // take our values as-is
    0,                 // no extra data between each position
    0                  // offset of first element
  );

  /* Push each element in buffer_vertices to the vertex shader */
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
  int size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);

  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, 0.0));
  glm::mat4 projection = glm::perspective(45.0f, 1.0f*SCREENWIDTH/SCREENHEIGHT, 0.1f, 100.0f);
  glm::mat4 mvp = projection * view * model;

  glUseProgram(program);
  glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));

  glDrawElements(GL_TRIANGLES, size/sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
	glBindBuffer(GL_ARRAY_BUFFER,0); // reset buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); // reset

  glDisableVertexAttribArray(attribute_coord3d);
  glDisableVertexAttribArray(attribute_v_color);

}

