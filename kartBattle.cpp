//CG: Assignment 4 (kartBattle) by a1212249

#include "kartBattle.h"

int main(int argc, char* argv[]) {

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA);//|GLUT_DEPTH
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
  
  init_resources();//car

  glutDisplayFunc(display);

  glutMainLoop();


  return 0;
}
