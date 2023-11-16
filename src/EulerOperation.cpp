#include "EulerOperation.hpp"
#include <iostream>

namespace euler {

Solid *mvfs(const Point &p, Vertex *&v) {
  // make new instances
  Solid *s = new Solid();
  Face *f = new Face();
  Loop *l = new Loop();
  v = new Vertex();

  // set vertex
  v->vpoint = new Point(p);

  // set pointers
  s->sfaces.push_back(f);
  f->fsolid = s;
  f->fouterloop = l;
  l->lface = f;

  return s;
}

HalfEdge *mev(Vertex *const vStart, const Point &p, Loop *const l) {
  // create new instances
  HalfEdge *he1 = new HalfEdge();
  HalfEdge *he2 = new HalfEdge();
  he1->twin = he2;
  he2->twin = he1;
  Edge *edge = new Edge();
  Solid *solid = l->lface->fsolid;

  // create a new vertex as the end of the new edge
  Vertex *vEnd = new Vertex();

  // set the vertex
  vEnd->vpoint = new Point(p);

  vStart->vHalfEdge = he1;
  vEnd->vHalfEdge = he2;
  edge->ehe1 = he1;
  edge->ehe2 = he2;

  // set the halfedges
  he1->heLoop = l;
  he2->heLoop = l;
  he1->hedge = edge;
  he2->hedge = edge;
  he1->startV = vStart;
  he1->endV = vEnd;
  he2->startV = vEnd;
  he2->endV = vStart;
  he1->next = he2;
  he2->prev = he1;
  if (l->startHalfEdge == nullptr) {
    // empty
    he1->prev = he2;
    he2->next = he1;
    l->startHalfEdge = he1;
  } else {
    // insert the new halfedge into the linkedlist
    HalfEdge *endAtVStart = l->findHEwithEndV(vStart);
    he2->next = endAtVStart->next;
    endAtVStart->next->prev = he2;
    he1->prev = endAtVStart;
    endAtVStart->next = he1;
  }

  // set pointers of solid
  solid->sedges.push_back(edge);

  return he1;
}

Loop *mef(Vertex *const v1, Vertex *const v2, Loop *const l) {
  // create new instances
  Loop *lNew = new Loop();
  Face *face = new Face();
  HalfEdge *he1 = new HalfEdge();
  HalfEdge *he2 = new HalfEdge();
  Edge *edge = new Edge();

  Solid *solid = l->lface->fsolid;

  // set the edges
  edge->ehe1 = he1;
  edge->ehe2 = he2;

  // set the halfedges
  he1->heLoop = l;
  he1->hedge = edge;
  he2->hedge = edge;
  he1->startV = v1;
  he1->endV = v2;
  he2->startV = v2;
  he2->endV = v1;
  he1->next = he2;
  he2->prev = he1;

  HalfEdge *endAtV1 = l->findHEwithEndV(v1); 
  HalfEdge *endAtV2 = l->findHEwithEndV(v2); 

  he2->next = endAtV1->next;
  endAtV1->next->prev = he2;
  he1->prev = endAtV1;
  endAtV1->next = he1;

  he1->next = endAtV2->next;
  endAtV2->next->prev = he1;
  he2->prev = endAtV2;
  endAtV2->next = he2;

  // set the loop
  lNew->lface = face;
  l->startHalfEdge = he1;
  lNew->startHalfEdge = he2;

  // set the face
  face->fsolid = solid;
  face->fouterloop = lNew;

  // set the solid
  solid->sfaces.push_back(face);
  solid->sedges.push_back(edge);

  // return the new loop
  return lNew;
}

Loop *kemr(Vertex *const v1, Vertex *const v2, Loop *const l) {
  // create new instances
  Loop *lNew = new Loop(); // an inner loop
  Solid *solid = l->lface->fsolid;
  HalfEdge *he_12 =
      l->findHalfEdge(v1, v2);
  HalfEdge *he_21 = he_12->twin; 
  Edge *edge_12 = he_12->hedge;  

  lNew->lface = l->lface;
  lNew->startHalfEdge = he_12->next;
  he_12->next->prev = he_21->prev;
  he_21->prev->next = he_12->next;

  // set the outer loop
  l->startHalfEdge = he_21->next;
  he_12->prev->next = he_21->next;
  he_21->next->prev = he_12->prev;

  // set the face
  lNew->lface->finnerloops.push_back(lNew);

  // set the solid
  solid->sedges.remove(edge_12);

  delete edge_12;

  delete he_12;
  delete he_21;

  return lNew;
}

// kill face and make ring and hole
void kfmrh(const Loop *outL, Loop *const inL) {
  Face *outF =
      outL->lface; // should be kept, surrounded by _oloop & _iloop
  Face *inF = inL->lface; // this face should be killed and form a hole
  Solid *solid = outF->fsolid;

  // set pointers of inner loop
  inL->lface = outF;

  // set pointers of outer face
  outF->finnerloops.push_back(inL);

  // set pointers of solid
  solid->sfaces.remove(inF);

  delete inF;
  return;
}

} // namespace euler