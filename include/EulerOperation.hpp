#ifndef EULEROPERATION
#define EULEROPERATION

#include "HalfEdgeStructure.hpp"
namespace euler {
// Make Vertex Face Solid, this operation creates a new solid with one vertex
// and one face
Solid *mvfs(const Point &p, Vertex *&v);
  // Make Edge and Vertex, this operation adds an edge and a vertex to a face
HalfEdge *mev(Vertex *const v, const Point &_point, Loop *const _loop);
  // Make Edge and Face, this operation adds an edge and a face to a solid,
  // dividing one face into two, l should be the outer loop
Loop *mef(Vertex *const _vertex0, Vertex *const _vertex1, Loop *const _loop);
  // Kill Edge and Make Ring, this operation removes and edge and merges two
  // faces into one
Loop *kemr(Vertex *const _vertex0, Vertex *const _vertex1, Loop *const _loop);
// kill face and make ring and hole
void kfmrh(const Loop *_oloop, Loop *const _iloop);
  // Kill Face, Make Ring and Hole, this operation removes a face, creating a
  // hole, and merges the ramaining faces
Solid *sweep(Face *_face, const glm::vec3 &direction, const GLdouble distance);
} // namespace euler

#endif