#pragma once
#include "EulerOperation.hpp"
namespace euler {
  // sweep face
void SweepLoop(Loop *l, const GLdouble *offset);
Solid *sweep(Face *_face, const glm::vec3 &direction, const GLdouble distance);
}