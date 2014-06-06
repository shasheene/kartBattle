/*
 * global.h
 */

#ifndef GLOBAL
#define GLOBAL

#include "glLibAndConst.h"
//#include "car.h"
#include "entity.h"

extern Entity* player1;
extern Entity* player2;
extern Entity* weapon;
extern bool * MultiKeys;
extern glm::vec3 WeaPos;
extern int WeaTimer;

GLfloat degToRad (GLfloat deg);
GLfloat radToDeg (GLfloat rad);



#endif

