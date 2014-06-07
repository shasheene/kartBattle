/*
 * global.h
 */

#ifndef GLOBAL
#define GLOBAL

#include "glLibAndConst.h"
//#include "car.h"
#include "entity.h"

#define NUMENTITIES 4

extern Entity* player1;
extern Entity* player2;
extern Entity* weapon;
extern Entity ** entitiesArray;

extern bool * MultiKeys;
extern glm::vec3 WeaPos;
extern int WeaTimer;

GLfloat degToRad (GLfloat deg);
GLfloat radToDeg (GLfloat rad);



#endif

