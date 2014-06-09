//CG: Assignment 4 (kartBattle) by a1212249

#include "kartBattle.h"
#include "global.h"
#include "entity.h"
#include "movement.h"
Entity * player1;
Entity * player2;
Entity * weapon;
Entity * weapon2;
Entity ** entitiesArray;
bool * MultiKeys;

int player1Score;
int player2Score;

int main(int argc, char* argv[]) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);//|GLUT_DEPTH);
  glutInitWindowSize(SCREENWIDTH,SCREENHEIGHT);
  /*
  //freeglut check (copied from Angel example):
  glutInitContextVersion(3,2);
  glutInitContextProfile(GLUT_CORE_PROFILE);
  */
  glutCreateWindow("kartBattle");
  
  //Segmentation fault caused without glewExperimental:
  glewExperimental = GL_TRUE;
  glewInit();

glm::vec3 carBounding[4] = {
  glm::vec3(0.0,0.0, 1.0),//top horizontal line
  glm::vec3(0.0,0.0, -1.0),//bottom horizontal line
  glm::vec3(-1.0,0.0, 0.0), //left vertical line
  glm::vec3(1.0,0.0, 0.0) //right vertical line
  };


 player1 = new Entity("res/car1/car-n.obj", glm::vec3(2.0, 0.0, -5.0), degToRad(0.0f), carBounding, 1.0,"player1");
 player2 = new Entity("res/car2/car-n.obj", glm::vec3(2.0, 0.0, 5.0), 180.0f, carBounding, 1.0,"player2");
 weapon = new Entity("res/ball/Football.obj", glm::vec3(2.0, 0.0, 0.0 ), 0.0f, carBounding, 0.4,"weapon");
 weapon2 = new Entity("res/ball/Football.obj", glm::vec3(2.0, 0.0, 0.0 ), 0.0f, carBounding, 0.4,"weapon2");

  entitiesArray = new Entity*[NUMENTITIES];
  entitiesArray[0] = player1;
  entitiesArray[1] = player2;
  entitiesArray[2] = weapon;
  entitiesArray[3] = weapon2;

  MultiKeys = new bool[256];
	for(int i=0;i<256;i++){
		MultiKeys[i] = 0;
	}

    init_resources();//car
  //glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);

  glutDisplayFunc(display);
  glutIdleFunc(idle);

  glutKeyboardFunc( keyboardPress );
  glutKeyboardUpFunc( keyboardNoPress );

  glutMainLoop();


  return 0;
}
