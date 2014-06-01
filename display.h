/*
 * display.h
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "glLibAndConst.h"
#include "entity.h"

void display();
void drawObject(Entity * my_entity,  glm::mat4 current_mvp);

#endif
