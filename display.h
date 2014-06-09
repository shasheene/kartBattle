/*
 * display.h
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "glLibAndConst.h"
#include "entity.h"
#include "shader_utils.h"

void display();
void drawObject(Entity * my_entity,  glm::mat4 current_mvp, glm::mat4 model, glm::mat4 view);

void keyboardPress( unsigned char key, int x, int y );
void keyboardNoPress( unsigned char key, int x, int y );
void Movement(void);

int init_resources(void);
void DrawTrack(void);

#endif
