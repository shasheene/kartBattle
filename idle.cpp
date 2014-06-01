/*
 * idle.cpp
 */

#include "idle.h"

void idle() {
  angle = glutGet(GLUT_ELAPSED_TIME) / 1000.0 * 45;  // 45° per second
  glutPostRedisplay();
}
