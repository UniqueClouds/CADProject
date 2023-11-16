#include "Display.hpp"

float Display::angleX = 0.0;
float Display::angleY = 0.0;
float Display::deltaAngle = 1.0;
float Display::deltaMove = 0.0;
int Display::xOrigin = -1;
int Display::yOrigin = -1;
float Display::smoothX = 0.0;
float Display::smoothY = 0.0;
float Display::smoothFactor = 0.1;
euler::Scene Display::scene;

void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  // set the camera
  gluLookAt(0, 0, 40, 0, 0, 0, 0, 1, 0);
  glTranslatef(0, 0, Display::deltaMove);
  glRotatef(Display::angleX, 1, 0, 0);
  glRotatef(Display::angleY, 0, 1, 0);

  if (!Display::scene.ssolids.empty()) {
    for (auto &solid : Display::scene.ssolids) {
      DrawSolid(solid);
    }
  } else {
    std::cout << "List is empty!!!" << std::endl;
  }

  glutSwapBuffers();
}

void reshape(int w, int h) {
  if (h == 0)
    h = 1;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0, (float)w / (float)h, .1, 100.0);
  glMatrixMode(GL_MODELVIEW);
}


void mouseMove(int x, int y) {
  if (Display::xOrigin >= 0) {
    // calculate the offset of mouse movement in horizontal and vertical direction
    int deltaX = x - Display::xOrigin;
    int deltaY = y - Display::yOrigin;

    // use sliding average to smooth the mouse movement
    Display::smoothY =
        Display::smoothY * (1.0 - Display::smoothFactor) + deltaY * Display::smoothFactor;
    Display::smoothX =
        Display::smoothX * (1.0 - Display::smoothFactor) + deltaX * Display::smoothFactor;

    // horizontal mouse movement controls left and right rotation
    Display::angleY += Display::smoothX * 0.1;

    // vertical mouse movement controls up and down rotation
    Display::angleX += Display::smoothY * 0.1;

    // Prevent the angle from exceeding the upper and lower limits
    if (Display::angleY > 360)
      Display::angleY -= 360;
    if (Display::angleY < -360)
      Display::angleY += 360;

    if (Display::angleX > 360)
      Display::angleX -= 360;
    if (Display::angleX < -360)
      Display::angleX += 360;
  }
  Display::xOrigin = x;
  Display::yOrigin = y;
}

void mouseButton(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {
    Display::xOrigin = -1;
  }
}
