/*
 * movement.cpp
 */

#include "movement.h"

void keyboardPress( unsigned char key, int x, int y )
{
	MultiKeys[key] = true;
}

void keyboardNoPress( unsigned char key, int x, int y )
{
	MultiKeys[key] = false;
}

void movement(void)
{

  //Exit
  if(MultiKeys[033]){
    exit( EXIT_SUCCESS );
  }
	int time = glutGet(GLUT_ELAPSED_TIME)/1000;
		//Movement Player 1
	if(MultiKeys['w'] ){
			player1->pos[0] = player1->pos[0]+(timeDiff*0.005 * sin(degToRad(player1->angle)));
			player1->pos[2] = player1->pos[2]+(timeDiff*0.005 * cos(degToRad(player1->angle)));
			player1->viewDest = player1->pos;
			player1->viewSrc[0] = player1->viewDest[0]-(2 * sin(degToRad(player1->angle)));
			player1->viewSrc[2] = player1->viewDest[2]-(2 * cos(degToRad(player1->angle)));

	}
	if(MultiKeys['s']){
			player1->pos[0] = player1->pos[0]-(timeDiff*0.005 * sin(degToRad(player1->angle)));
			player1->pos[2] = player1->pos[2]-(timeDiff*0.005 * cos(degToRad(player1->angle)));
			player1->viewDest = player1->pos;
			player1->viewSrc[0] = player1->viewDest[0]-(2 * sin(degToRad(player1->angle)));
			player1->viewSrc[2] = player1->viewDest[2]-(2 * cos(degToRad(player1->angle)));
	}
		//Turning forwards
	if(MultiKeys['a'] && MultiKeys['w']){
		//player1->pos[0] = player1->pos[0]+0.005;
		if(player1->angle > 360){
			player1->angle = 0;
			player1->angle = player1->angle + timeDiff*0.2;
		}
		else{
			player1->angle = player1->angle + timeDiff*0.2;
		}
	}
	if(MultiKeys['d'] && MultiKeys['w']){
		//player1->pos[0] = player1->pos[0]-0.005;
		if(player1->angle < 0){
			player1->angle = 360;
			player1->angle = player1->angle - timeDiff*0.2;
		}
		else{
			player1->angle = player1->angle - timeDiff*0.2;
		}
	}
		//Turning Backwards
	if(MultiKeys['d'] && MultiKeys['s']){
		//player1->pos[0] = player1->pos[0]+0.005;
		if(player1->angle > 360){
			player1->angle = 0;
			player1->angle = player1->angle + timeDiff*0.2;
		}
		else{
			player1->angle = player1->angle + timeDiff*0.2;
		}
	}
	if(MultiKeys['a'] && MultiKeys['s']){
		//player1->pos[0] = player1->pos[0]-0.005;
		if(player1->angle < 0){
			player1->angle = 360;
			player1->angle = player1->angle - timeDiff*0.2;
		}
		else{
			player1->angle = player1->angle - timeDiff*0.2;
		}
	}


		//Movement Player 2
	if(MultiKeys['i']){
			player2->pos[0] = player2->pos[0]+(timeDiff*0.005 * sin(degToRad(player2->angle)));
			player2->pos[2] = player2->pos[2]+(timeDiff*0.005 * cos(degToRad(player2->angle)));
			player2->viewDest = player2->pos;
			player2->viewSrc[0] = player2->viewDest[0]-(2 * sin(degToRad(player2->angle)));
			player2->viewSrc[2] = player2->viewDest[2]-(2 * cos(degToRad(player2->angle)));
	}
	if(MultiKeys['k']){
			player2->pos[0] = player2->pos[0]-(timeDiff*0.005 * sin(degToRad(player2->angle)));
			player2->pos[2] = player2->pos[2]-(timeDiff*0.005 * cos(degToRad(player2->angle)));
			player2->viewDest = player2->pos;
			player2->viewSrc[0] = player2->viewDest[0]-(2 * sin(degToRad(player2->angle)));
			player2->viewSrc[2] = player2->viewDest[2]-(2 * cos(degToRad(player2->angle)));
	}
		//Turning forwards
	if(MultiKeys['j'] && MultiKeys['i']){
		//player2->pos[0] = player2->pos[0]+0.005;
		if(player2->angle > 360){
			player2->angle = 0;
			player2->angle = player2->angle + timeDiff*0.2;
		}
		else{
			player2->angle = player2->angle + timeDiff*0.2;
		}
	}
	if(MultiKeys['l'] && MultiKeys['i']){
		//player2->pos[0] = player2->pos[0]-0.005;
		if(player2->angle < 0){
			player2->angle = 360;
			player2->angle = player2->angle - timeDiff*0.2;
		}
		else{
			player2->angle = player2->angle - timeDiff*0.2;
		}
	}
		//Turning Backwards
	if(MultiKeys['l'] && MultiKeys['k']){
		//player2->pos[0] = player2->pos[0]+0.005;
		if(player2->angle > 360){
			player2->angle = 0;
			player2->angle = player2->angle + timeDiff*0.2;
		}
		else{
			player2->angle = player2->angle + timeDiff*0.2;
		}
	}
	if(MultiKeys['j'] && MultiKeys['k']){
		//player2->pos[0] = player2->pos[0]-0.005;
		if(player2->angle < 0){
			player2->angle = 360;
			player2->angle = player2->angle - timeDiff*0.2;
		}
		else{
			player2->angle = player2->angle - timeDiff*0.2;
		}
	}

		//Fire Weapon Player 1
	if(MultiKeys['e']){
		weapon->angle = player1->angle;
		weapon->pos[0] = player1->pos[0]+(1.3 * sin(degToRad(weapon->angle)));
		weapon->pos[2] = player1->pos[2]+(1.3 * cos(degToRad(weapon->angle)));
		WeaTimer = 0;
	}
}
