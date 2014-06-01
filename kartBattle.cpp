//CG: Assignment 4 (kartBattle) by a1212249

#include "kartBattle.h"
#include "global.h"
#include "entity.h"
Entity * player1;

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


  player1 = new Entity("car/car-n.obj");

  //  init_resources();//car
  //glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);

  glutDisplayFunc(display);
  glutIdleFunc(idle);

  glutMainLoop();


  return 0;
}
