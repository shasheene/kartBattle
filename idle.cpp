/*
 * idle.cpp
 */

#include "idle.h"
#include "global.h"

  int timeClock = 0;
  int timeDiff = 0;
  int timePrev = 0;

void idle() {
  //player1->angle = glutGet(GLUT_ELAPSED_TIME) / 1000.0 * 45;  // 45° per second
	timeClock = glutGet(GLUT_ELAPSED_TIME);
	timeDiff = timeClock - timePrev;
	timePrev = timeClock;

	if(WeaTimer < 5000){
		weapon->pos[0] = weapon->pos[0]+(timeDiff*0.02 * sin(degToRad(weapon->angle)));
		weapon->pos[2] = weapon->pos[2]+(timeDiff*0.02 * cos(degToRad(weapon->angle)));
  		WeaTimer ++;
	}
	if(WeaTimer2 < 5000){
		weapon2->pos[0] = weapon2->pos[0]+(timeDiff*0.02 * sin(degToRad(weapon2->angle)));
		weapon2->pos[2] = weapon2->pos[2]+(timeDiff*0.02 * cos(degToRad(weapon2->angle)));
  		WeaTimer2 ++;
	}

  glutPostRedisplay();
}
