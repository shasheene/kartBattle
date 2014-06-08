/*
 * global.cpp
 */

#include "global.h"

GLfloat pi=3.14159265359;


GLfloat degToRad (GLfloat deg) {
  return (deg*pi/180);
}

GLfloat radToDeg (GLfloat rad) {
  return (rad*180/pi);
}
