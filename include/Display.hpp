#pragma once

#include "HalfEdgeStructure.hpp"
#include "EulerOperation.hpp"
#include "Draw.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

class Display {
public:
  static float angleX;
  static float angleY;
  static float deltaAngle;
  static float deltaMove;
  static int xOrigin;
  static int yOrigin;
  static float smoothX;
  static float smoothY;
  static float smoothFactor; 

  static euler::Scene scene;
  static void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST); 
    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 1.333, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);

    // create solids
    scene.ssolids.push_back(SweepSolid());
  }
};

void display();

void reshape(int w, int h);

void mouseMove(int x, int y);

void mouseButton(int button, int state, int x, int y);