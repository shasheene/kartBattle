/*
 * display.cpp
 */

#include "display.h"
#include "global.h"
#include <cstdio>


//Could place these inside of the object files and refer to them from there

	//Follow Player 1
  glm::vec3 P1view1(0.0, 0.5, -2.0);
  glm::vec3 P1view2(0.0, 0.0, 0.0);
  glm::vec3 P1view3(0.0, 1.0, 0.0);

	//Follow Player 2
  glm::vec3 P2view1(2.0, 0.5, -2.0);
  glm::vec3 P2view2(2.0, 0.0, 0.0);
  glm::vec3 P2view3(0.0, 1.0, 0.0);

	//weapon
  glm::vec3 WeaPos(2.0, 0.0, 0.0);
  int WeaTimer = 50000;



void display (void) {
  Movement();
  
  for (int i=0; i<NUMENTITIES; i++) {
    entitiesArray[i]->update(entitiesArray, NUMENTITIES);
  }


  glm::vec3 axis_y(0, 1, 0);
  glm::mat4 anim;
  glm::mat4 view;
  glm::mat4 model;
  glm::mat4 projection;
  glm::mat4 current_mvp;

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
	//1st screen top
  glViewport(0, SCREENHEIGHT/2+1, SCREENWIDTH, SCREENHEIGHT/2);
  view = glm::lookAt(P1view1, P1view2, P1view3);
  projection = glm::perspective(45.0f, 1.0f*SCREENWIDTH/SCREENHEIGHT, 0.1f, 100.0f);

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
	 model = glm::translate(glm::mat4(1.0f), WeaPos);
	 current_mvp = projection * view * model * anim;

	 drawObject(weapon, current_mvp, model, view);
  }


//---------------------------


	//2ed screen, bottom
  glViewport(0, 0, SCREENWIDTH, SCREENHEIGHT/2);
  view = glm::lookAt(P2view1, P2view2, P2view3);

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
	 model = glm::translate(glm::mat4(1.0f), WeaPos);
	 current_mvp = projection * view * model * anim;

	 drawObject(weapon, current_mvp, model, view);
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



void keyboardPress( unsigned char key, int x, int y )
{
	MultiKeys[key] = true;
}

void keyboardNoPress( unsigned char key, int x, int y )
{
	MultiKeys[key] = false;
}

void Movement(void)
{
		//Exit
	if(MultiKeys[033]){
        exit( EXIT_SUCCESS );
	}

		//Movement Player 1
	if(MultiKeys['w']){
			player1->pos[0] = player1->pos[0]+(0.005 * sin(degToRad(player1->angle)));
			player1->pos[2] = player1->pos[2]+(0.005 * cos(degToRad(player1->angle)));
			P1view2 = player1->pos;
			P1view1[0] = P1view2[0]-(2 * sin(degToRad(player1->angle)));
			P1view1[2] = P1view2[2]-(2 * cos(degToRad(player1->angle)));
	}
	if(MultiKeys['s']){
			player1->pos[0] = player1->pos[0]-(0.005 * sin(degToRad(player1->angle)));
			player1->pos[2] = player1->pos[2]-(0.005 * cos(degToRad(player1->angle)));
			P1view2 = player1->pos;
			P1view1[0] = P1view2[0]-(2 * sin(degToRad(player1->angle)));
			P1view1[2] = P1view2[2]-(2 * cos(degToRad(player1->angle)));
	}
		//Turning forwards
	if(MultiKeys['a'] && MultiKeys['w']){
		//player1->pos[0] = player1->pos[0]+0.005;
		if(player1->angle > 360){
			player1->angle = 0;
			player1->angle = player1->angle + 0.2;
		}
		else{
			player1->angle = player1->angle + 0.2;
		}
	}
	if(MultiKeys['d'] && MultiKeys['w']){
		//player1->pos[0] = player1->pos[0]-0.005;
		if(player1->angle < 0){
			player1->angle = 360;
			player1->angle = player1->angle - 0.2;
		}
		else{
			player1->angle = player1->angle - 0.2;
		}
	}
		//Turning Backwards
	if(MultiKeys['d'] && MultiKeys['s']){
		//player1->pos[0] = player1->pos[0]+0.005;
		if(player1->angle > 360){
			player1->angle = 0;
			player1->angle = player1->angle + 0.2;
		}
		else{
			player1->angle = player1->angle + 0.2;
		}
	}
	if(MultiKeys['a'] && MultiKeys['s']){
		//player1->pos[0] = player1->pos[0]-0.005;
		if(player1->angle < 0){
			player1->angle = 360;
			player1->angle = player1->angle - 0.2;
		}
		else{
			player1->angle = player1->angle - 0.2;
		}
	}


		//Movement Player 2
	if(MultiKeys['i']){
			player2->pos[0] = player2->pos[0]+(0.005 * sin(degToRad(player2->angle)));
			player2->pos[2] = player2->pos[2]+(0.005 * cos(degToRad(player2->angle)));
			P2view2 = player2->pos;
			P2view1[0] = P2view2[0]-(2 * sin(degToRad(player2->angle)));
			P2view1[2] = P2view2[2]-(2 * cos(degToRad(player2->angle)));
	}
	if(MultiKeys['k']){
			player2->pos[0] = player2->pos[0]-(0.005 * sin(degToRad(player2->angle)));
			player2->pos[2] = player2->pos[2]-(0.005 * cos(degToRad(player2->angle)));
			P2view2 = player2->pos;
			P2view1[0] = P2view2[0]-(2 * sin(degToRad(player2->angle)));
			P2view1[2] = P2view2[2]-(2 * cos(degToRad(player2->angle)));
	}
		//Turning forwards
	if(MultiKeys['j'] && MultiKeys['i']){
		//player2->pos[0] = player2->pos[0]+0.005;
		if(player2->angle > 360){
			player2->angle = 0;
			player2->angle = player2->angle + 0.2;
		}
		else{
			player2->angle = player2->angle + 0.2;
		}
	}
	if(MultiKeys['l'] && MultiKeys['i']){
		//player2->pos[0] = player2->pos[0]-0.005;
		if(player2->angle < 0){
			player2->angle = 360;
			player2->angle = player2->angle - 0.2;
		}
		else{
			player2->angle = player2->angle - 0.2;
		}
	}
		//Turning Backwards
	if(MultiKeys['l'] && MultiKeys['k']){
		//player2->pos[0] = player2->pos[0]+0.005;
		if(player2->angle > 360){
			player2->angle = 0;
			player2->angle = player2->angle + 0.2;
		}
		else{
			player2->angle = player2->angle + 0.2;
		}
	}
	if(MultiKeys['j'] && MultiKeys['k']){
		//player2->pos[0] = player2->pos[0]-0.005;
		if(player2->angle < 0){
			player2->angle = 360;
			player2->angle = player2->angle - 0.2;
		}
		else{
			player2->angle = player2->angle - 0.2;
		}
	}

		//Fire Weapon Player 1
	if(MultiKeys['e']){
		WeaPos = player1->pos;
		weapon->angle = player1->angle;
			WeaPos[0] = WeaPos[0]+(1 * sin(degToRad(weapon->angle)));
			WeaPos[2] = WeaPos[2]+(1 * cos(degToRad(weapon->angle)));
		WeaTimer = 0;
	}
}


