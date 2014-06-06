/*
 * idle.cpp
 */

#include "idle.h"

void idle() {
  //player1->angle = glutGet(GLUT_ELAPSED_TIME) / 1000.0 * 45;  // 45° per second

	if(WeaTimer < 5000){
		WeaPos[0] = WeaPos[0]+(0.03 * sin(degToRad(weapon->angle)));
		WeaPos[2] = WeaPos[2]+(0.03 * cos(degToRad(weapon->angle)));
  		WeaTimer ++;
	}

  glutPostRedisplay();
}
