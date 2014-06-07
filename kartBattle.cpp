//CG: Assignment 4 (kartBattle) by a1212249

#include "kartBattle.h"
#include "global.h"
#include "entity.h"
Entity * player1;
Entity * player2;
Entity * weapon;
Entity ** entitiesArray;
bool * MultiKeys;

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
    glm::vec3(0.0,0.0, 0.0),
    glm::vec3(0.0,0.0, 0.0),
    glm::vec3(0.0,0.0, 0.0),
    glm::vec3(0.0,0.0, 0.0)
  };

  player1 = new Entity("res/car1/car-n.obj", glm::vec3(0.0,0.0, 0.0), carBounding);
  player2 = new Entity("res/car2/car-n.obj", glm::vec3(2.0, 0.0, 0.0), carBounding);
  weapon = new Entity("res/car1/car-n.obj", glm::vec3(2.0, 0.0, 0.0 ), carBounding);
  
  entitiesArray = new Entity*[NUMENTITIES];
  entitiesArray[0] = player1;
  entitiesArray[1] = player2;
  entitiesArray[2] = weapon;
  
	MultiKeys = new bool[256];
	for(int i=0;i<256;i++){
		MultiKeys[i] = 0;
	}

  //  init_resources();//car
  //glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);

  glutDisplayFunc(display);
  glutIdleFunc(idle);

  glutKeyboardFunc( keyboardPress );
  glutKeyboardUpFunc( keyboardNoPress );

  glutMainLoop();


  return 0;
}
