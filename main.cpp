//CG: Assignment 4 (kartBattle) by a1212249

#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
using namespace std;

#define GLM_FORCE_RADIANS
#define SCREENWIDTH 800
#define SCREENHEIGHT 640

int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH);
  glutInitWindowSize(SCREENWIDTH,SCREENHEIGHT);

  glutCreateWindow("kartBattle");
  
  //glutDisplayFunc(display);
  //glutReshapeFunc(onReshape);
  
  //glutKeyboardFunc(keyboard);


  glutMainLoop();


  return 0;
}
