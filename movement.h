/*
 * movement.h
 */

#ifndef MOVEMENT_H
#define MOVEMENT_H


#include <iostream>

#include "glLibAndConst.h"
#include "entity.h"
#include "global.h"

void keyboardPress( unsigned char, int, int );
void keyboardNoPress( unsigned char, int, int );
bool carDistance();
void movement();

#endif
