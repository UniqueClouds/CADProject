#pragma once

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <iostream>
#include <list>
#include <vector>

namespace euler {
class Point;
class Vertex;
class Edge;
class HalfEdge;
class Loop;
class Face;
class Solid;
class Scene;

class Scene {
public:
  std::list<Solid *> ssolids;
  Scene() : ssolids() {}
};

class Solid {
public:
  //  faces of the solid
  std::list<Face *> sfaces;
  //  edges of the solid
  std::list<Edge *> sedges;
  Solid() : sfaces(), sedges() {}
};

class Face {
public:
  // solid of the face
  Solid *fsolid;
  // outer loop of the face
  Loop *fouterloop;
  // inner loops of the face
  std::list<Loop *> finnerloops;
  Face() : fsolid(nullptr), fouterloop(nullptr), finnerloops() {}
};

class Loop {
public:
  // face of the loop
  Face *lface;
  // start node of the linkedlist of halfedges of the loop
  HalfEdge *startHalfEdge;
  // find the halfedge end node v
  HalfEdge *findHEwithEndV(const Vertex *v);
  // find the halfedge with start node
  // startV and end node endV
  HalfEdge *findHalfEdge(const Vertex *startV, const Vertex *endV);
  Loop() : lface(nullptr), startHalfEdge(nullptr) {}
};

class Edge {
public:
  HalfEdge *ehe1, *ehe2;
  Edge() : ehe1(nullptr), ehe2(nullptr) {}
};

class HalfEdge {
public:
  HalfEdge *next, *prev; // The next and prev half-edges in the loop
  HalfEdge *twin;        // The twin half-edge
  Loop *heLoop;          // The loop it belongs to
  Edge *hedge;           // The edge it belongs to
  Vertex *startV, *endV; // The start and end vertices
  HalfEdge()
      : next(nullptr), prev(nullptr), twin(nullptr), heLoop(nullptr),
        hedge(nullptr), startV(nullptr), endV(nullptr) {}
  HalfEdge *mate() {
    return this == this->hedge->ehe1 ? this->hedge->ehe2 : this->hedge->ehe1;
  };
};

class Vertex {
public:
  // The halfedge with the vertex as start vertex
  HalfEdge *vHalfEdge;
  // The point it represents
  Point *vpoint;
  Vertex() : vHalfEdge(nullptr), vpoint(nullptr) {}
};

class Point {
public:
  GLdouble position[3];
  GLdouble color[3];
  Point() : position{0, 0, 0}, color{.5, .5, .5} {}
  Point(double x, double y, double z, double r, double g, double b)
      : position{x, y, z}, color{r, g, b} {}
  Point(const glm::vec3 &pos, const glm::vec3 &color)
      : position{pos.x, pos.y, pos.z}, color{color.x, color.y, color.z} {}
  Point(glm::vec3 position)
      : position{position.x, position.y, position.z}, color{
                                                          rand() % 255 / 255.0f,
                                                          rand() % 255 / 255.0f,
                                                          rand() % 255 /
                                                              255.0f} {}
  Point(const Point &p)
      : position{p.position[0], p.position[1], p.position[2]},
        color{p.color[0], p.color[1], p.color[2]} {}

  Point(const Point *p, const GLdouble *offset)
      : position{p->position[0] + offset[0], p->position[1] + offset[1],
                 p->position[2] + offset[2]},
        color{p->color[0], p->color[1], p->color[2]} {}
};

} // namespace euler