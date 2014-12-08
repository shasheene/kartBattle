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

bool carDistance(void)
{
	int x = (player1->pos[0] - player2->pos[0]) * (player1->pos[0] - player2->pos[0]);
	int z = (player1->pos[2] - player2->pos[2]) * (player1->pos[2] - player2->pos[2]);
	if(x+z < 2.0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void movement(void)
{

  //Exit
  if(MultiKeys[033]){
    exit( EXIT_SUCCESS );
  }
	int time = glutGet(GLUT_ELAPSED_TIME)/1000;
	glm::vec3 oldPos(0, 0, 0);
		//Movement Player 1
	if(MultiKeys['w'] ){
			oldPos = player1->pos;
			player1->pos[0] = player1->pos[0]+(timeDiff*0.005 * sin(degToRad(player1->angle)));
			player1->pos[2] = player1->pos[2]+(timeDiff*0.005 * cos(degToRad(player1->angle)));
			if(carDistance())
			{
				player1->pos = oldPos;
			}
				// this makes sure that cars do not cross over the boundary walls, wall=20, boundary=18+view=2
			else if(player1->pos[0] > 18 || player1->pos[0] < -18 || player1->pos[2] > 18 || player1->pos[2] < -18)
			{
				player1->pos = oldPos;
			}
			else
			{
				player1->viewDest = player1->pos;
				player1->viewSrc[0] = player1->viewDest[0]-(2 * sin(degToRad(player1->angle)));
				player1->viewSrc[2] = player1->viewDest[2]-(2 * cos(degToRad(player1->angle)));
				//Turning forwards				
				if(MultiKeys['a']){
					if(player1->angle > 360){
						player1->angle = 0;
						player1->angle = player1->angle + timeDiff*0.2;
					}
					else{
						player1->angle = player1->angle + timeDiff*0.2;
					}
				}
				if(MultiKeys['d']){
					if(player1->angle < 0){
						player1->angle = 360;
						player1->angle = player1->angle - timeDiff*0.2;
					}
					else{
						player1->angle = player1->angle - timeDiff*0.2;
					}
				}
			}

	}
	if(MultiKeys['s']){
			oldPos = player1->pos;
			player1->pos[0] = player1->pos[0]-(timeDiff*0.005 * sin(degToRad(player1->angle)));
			player1->pos[2] = player1->pos[2]-(timeDiff*0.005 * cos(degToRad(player1->angle)));
			if(carDistance())
			{
				player1->pos = oldPos;
			}
			else if(player1->pos[0] > 18 || player1->pos[0] < -18 || player1->pos[2] > 18 || player1->pos[2] < -18)
			{
				player1->pos = oldPos;
			}
			else
			{
				player1->viewDest = player1->pos;
				player1->viewSrc[0] = player1->viewDest[0]-(2 * sin(degToRad(player1->angle)));
				player1->viewSrc[2] = player1->viewDest[2]-(2 * cos(degToRad(player1->angle)));
				//Turning Backwards
				if(MultiKeys['d']){
					//player1->pos[0] = player1->pos[0]+0.005;
					if(player1->angle > 360){
						player1->angle = 0;
						player1->angle = player1->angle + timeDiff*0.2;
					}
					else{
						player1->angle = player1->angle + timeDiff*0.2;
					}
				}
				if(MultiKeys['a']){
					//player1->pos[0] = player1->pos[0]-0.005;
					if(player1->angle < 0){
						player1->angle = 360;
						player1->angle = player1->angle - timeDiff*0.2;
					}
					else{
						player1->angle = player1->angle - timeDiff*0.2;
					}
				}
			}
	}



		//Movement Player 2
	if(MultiKeys['i']){
			oldPos = player2->pos;
			player2->pos[0] = player2->pos[0]+(timeDiff*0.005 * sin(degToRad(player2->angle)));
			player2->pos[2] = player2->pos[2]+(timeDiff*0.005 * cos(degToRad(player2->angle)));
			if(carDistance())
			{
				player2->pos = oldPos;
			}
			else if(player2->pos[0] > 18 || player2->pos[0] < -18 || player2->pos[2] > 18 || player2->pos[2] < -18)
			{
				player2->pos = oldPos;
			}
			else
			{
				player2->viewDest = player2->pos;
				player2->viewSrc[0] = player2->viewDest[0]-(2 * sin(degToRad(player2->angle)));
				player2->viewSrc[2] = player2->viewDest[2]-(2 * cos(degToRad(player2->angle)));
					//Turning forwards
				if(MultiKeys['j']){
					//player2->pos[0] = player2->pos[0]+0.005;
					if(player2->angle > 360){
						player2->angle = 0;
						player2->angle = player2->angle + timeDiff*0.2;
					}
					else{
						player2->angle = player2->angle + timeDiff*0.2;
					}
				}
				if(MultiKeys['l']){
					//player2->pos[0] = player2->pos[0]-0.005;
					if(player2->angle < 0){
						player2->angle = 360;
						player2->angle = player2->angle - timeDiff*0.2;
					}
					else{
						player2->angle = player2->angle - timeDiff*0.2;
					}
				}
			}
	}
	if(MultiKeys['k']){
			oldPos = player2->pos;
			player2->pos[0] = player2->pos[0]-(timeDiff*0.005 * sin(degToRad(player2->angle)));
			player2->pos[2] = player2->pos[2]-(timeDiff*0.005 * cos(degToRad(player2->angle)));
			if(carDistance())
			{
				player2->pos = oldPos;
			}
			else if(player2->pos[0] > 18 || player2->pos[0] < -18 || player2->pos[2] > 18 || player2->pos[2] < -18)
			{
				player2->pos = oldPos;
			}
			else
			{
				player2->viewDest = player2->pos;
				player2->viewSrc[0] = player2->viewDest[0]-(2 * sin(degToRad(player2->angle)));
				player2->viewSrc[2] = player2->viewDest[2]-(2 * cos(degToRad(player2->angle)));
					//Turning Backwards
				if(MultiKeys['l']){
					//player2->pos[0] = player2->pos[0]+0.005;
					if(player2->angle > 360){
						player2->angle = 0;
						player2->angle = player2->angle + timeDiff*0.2;
					}
					else{
						player2->angle = player2->angle + timeDiff*0.2;
					}
				}
				if(MultiKeys['j']){
					//player2->pos[0] = player2->pos[0]-0.005;
					if(player2->angle < 0){
						player2->angle = 360;
						player2->angle = player2->angle - timeDiff*0.2;
					}
					else{
						player2->angle = player2->angle - timeDiff*0.2;
					}
				}
			}
	}



		//Fire Weapon Player 1
	if(MultiKeys['e']){
		weapon->angle = player1->angle;
		weapon->pos[0] = player1->pos[0]+(1.4 * sin(degToRad(weapon->angle)));
		weapon->pos[2] = player1->pos[2]+(1.4 * cos(degToRad(weapon->angle)));
		WeaTimer = 0;
	}
		//Fire Weapon Player 1
	if(MultiKeys['u']){
		weapon2->angle = player2->angle;
		weapon2->pos[0] = player2->pos[0]+(1.4 * sin(degToRad(weapon2->angle)));
		weapon2->pos[2] = player2->pos[2]+(1.4 * cos(degToRad(weapon2->angle)));
		WeaTimer2 = 0;
	}
}
