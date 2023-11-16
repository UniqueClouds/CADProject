#pragma once

#include <string>
#include <vector>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// GLFW
#include "HalfEdgeStructure.hpp"
#include "EulerOperation.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>

// init tessellation object
void initTess();
// draw cube with holes
void drawCubeWithHoles();
// draw a solid
void DrawSolid(const euler::Solid *_solid);
// draw a face
void DrawFace(const euler::Face *_face);
// draw a loop: a contour of the polygon
void DrawLoop(const euler::Loop *_loop);

// // Euler Operation on Solid 
// euler::Solid *EulerSolid();
//  Sweep Operation on Solid
euler::Solid *SweepSolid();

void tessBeginCB(GLenum which);
void tessEndCB();
void tessVertexCB(const GLvoid *data);