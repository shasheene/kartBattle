/*
 * display.cpp
 */

#include "display.h"
#include <cstdio>
#include "global.h"

void display (void) {
  /*  glClearColor( 255.0, 255.0, 255.0, 1.0 ); // white background
  glClear (GL_COLOR_BUFFER_BIT); //clear window

  glFlush();*/
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


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

  glm::vec3 axis_y(0, 1, 0);
  glm::mat4 anim = glm::rotate(glm::mat4(1.0f), angle, axis_y);

  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -4.0));
  glm::mat4 view = glm::lookAt(glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 0.0, -4.0), glm::vec3(0.0, 1.0, 0.0));
  glm::mat4 projection = glm::perspective(45.0f, 1.0f*SCREENWIDTH/SCREENHEIGHT, 0.1f, 10.0f);

  current_mvp = projection * view * model * anim; // this is the overall transorm of our composited model - rotate it, translate it away from origin. Then position our viewer and set the projection.

  
    glUniformMatrix4fv(my_program.uniform_mvp, 1, GL_FALSE, glm::value_ptr(current_mvp));
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
  /* Push each element in buffer_vertices to the vertex shader */
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_model.ibo_model_elements[current_group]);
  //how many elements in what we want to draw?? Sure, we could have kept this as state rather than enquiring now.....
  int size;  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
  
 //   glUniform3fv(my_program.uniform_Kd,1,(const GLfloat *)  &(model_ptr->materials[group->material].diffuse));

  glBindTexture(GL_TEXTURE_2D, my_model.model_texture_ids[current_group]);
   glUniform1i(my_program.uniform_texture, /*GL_TEXTURE*/0); 

   glDrawElements(GL_TRIANGLES, size/sizeof(GLuint), GL_UNSIGNED_INT, 0);
        group=group->next;
        current_group++;
   }//end looping through groups
  glutSwapBuffers();


}
