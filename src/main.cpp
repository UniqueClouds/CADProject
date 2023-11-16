#include "Display.hpp"
#include "EulerOperation.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

int main(int argc, char *argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glClearColor(0.2f, 0.2f, 0.4f, 1.0f);

  glutInitWindowPosition(300, 300);
  glutInitWindowSize(1200, 900);
  glutCreateWindow("Sweep Solid");

  Display::init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape); 
  glutIdleFunc(display); 
  glutMouseFunc(mouseButton);
  glutMotionFunc(mouseMove);
  glutMainLoop();
  return 0;
}