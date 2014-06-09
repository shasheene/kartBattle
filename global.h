/*
 * global.h
 */

#ifndef GLOBAL
#define GLOBAL

#include "glLibAndConst.h"
#include "entity.h"

#define NUMENTITIES 4
#define ACCELERATESPEED 0.500
#define TURNSPEED 0.100
#define BRAKESPEED 0.400

extern Entity* player1;
extern Entity* player2;
extern Entity* weapon;
extern Entity* weapon2;
extern Entity ** entitiesArray;

extern bool * MultiKeys;
extern int WeaTimer;
extern int WeaTimer2;
extern int timeClock;
extern int timePrev;
extern int timeDiff;

#endif

