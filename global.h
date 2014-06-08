/*
 * global.h
 */

#ifndef GLOBAL
#define GLOBAL

#include "glLibAndConst.h"
#include "entity.h"

#define NUMENTITIES 3
#define ACCELERATESPEED 0.500
#define TURNSPEED 0.100
#define BRAKESPEED 0.400

extern Entity* player1;
extern Entity* player2;
extern Entity* weapon;
extern Entity ** entitiesArray;

extern bool * MultiKeys;
extern glm::vec3 WeaPos;
extern int WeaTimer;
extern int timeClock;
extern int timePrev;
extern int timeDiff;

#endif

