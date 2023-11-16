#include "Draw.hpp"

using namespace euler;

GLUtesselator *tess;

void initTess() {
  tess = gluNewTess();
  // set callback functions
  gluTessCallback(tess, GLU_TESS_BEGIN, (void (*)())tessBeginCB);
  gluTessCallback(tess, GLU_TESS_END, tessEndCB);
  gluTessCallback(tess, GLU_TESS_VERTEX, (void (*)())tessVertexCB);
}

void DrawSolid(const Solid *s) {
  initTess();
  for (const auto &value : s->sfaces) {
    DrawFace(value);
  }
  gluDeleteTess(tess);
}

void DrawFace(const Face *f) {

  gluTessBeginPolygon(tess, 0);

  // outer Loop
  DrawLoop(f->fouterloop);
  // inner loops
  for (auto &loop : f->finnerloops) {
    DrawLoop(loop);
  }
  gluTessEndPolygon(tess);
}

void DrawLoop(const Loop *l) {
  gluTessBeginContour(tess);
  HalfEdge *startHe = l->startHalfEdge;
  gluTessVertex(tess, startHe->startV->vpoint->position,
                startHe->startV->vpoint->position);

  HalfEdge *he = l->startHalfEdge->next;
  do {
    gluTessVertex(tess, he->startV->vpoint->position,
                  he->startV->vpoint->position);
    he = he->next;
  } while (he != nullptr && he != startHe);

  // for (; he != nullptr && he != startHe; he = he->next) {
  //   gluTessVertex(tess, he->startV->vpoint->position,
  //                 he->startV->vpoint->position);
  // }
  gluTessEndContour(tess);
}

Solid *SweepSolid() {
  Vertex *v1;
  Solid *solid = mvfs(Point(glm::vec3(0.f, 5.f, 0.f)), v1);
  Loop *lBottom1234 = solid->sfaces.front()->fouterloop;
  HalfEdge *he12 = mev(v1, Point(glm::vec3(11.f, 5.f, 0.f)), lBottom1234);
  Vertex *v2 = he12->endV;
  HalfEdge *he23 = mev(v2, Point(glm::vec3(11.f, -6.f, 0.f)), lBottom1234);
  Vertex *v3 = he23->endV;
  HalfEdge *he34 = mev(v3, Point(glm::vec3(0.f, -6.f, 0.f)), lBottom1234);
  Vertex *v4 = he34->endV;
  Loop *lTop1234 = mef(v4, v1, lBottom1234);

  // 1st hole
  HalfEdge *bridgeHole1 =
      mev(v1, Point(glm::vec3(4.f, -2.f, 0.f)), lBottom1234);
  Vertex *vHole1_1 = bridgeHole1->endV;

  HalfEdge *heHole1_12 =
      mev(vHole1_1, Point(glm::vec3(7.f, -2.f, 0.f)), lBottom1234);
  Vertex *vHole1_2 = heHole1_12->endV;
  HalfEdge *heHole1_23 =
      mev(vHole1_2, Point(glm::vec3(7.f, 1.f, 0.f)), lBottom1234);
  Vertex *vHole1_3 = heHole1_23->endV;
  HalfEdge *heHole1_34 = mev(vHole1_3, Point(glm::vec3(4.f, 1.f, 0.f)), lBottom1234);
  Vertex *vHole1_4 = heHole1_34->endV;
  Loop *lHole1_1234 = mef(vHole1_1, vHole1_4, lBottom1234);


  kemr(v1, vHole1_1, lBottom1234);

  kfmrh(lTop1234, lHole1_1234);

  // second hole
  HalfEdge *bridgeHole2 =
      mev(v1, Point(glm::vec3(7.5f, 0.f, 0.f)), lBottom1234);
  Vertex *vHole2_1 = bridgeHole2->endV;
  HalfEdge *heHole2_12 =
      mev(vHole2_1, Point(glm::vec3(9.9f, 1.f, 0.f)), lBottom1234);
  Vertex *vHole2_2 = heHole2_12->endV;
  HalfEdge *heHole2_23 =
      mev(vHole2_2, Point(glm::vec3(8.5f, -1.5f, 0.f)), lBottom1234);
  Vertex *vHole2_3 = heHole2_23->endV;
  Loop *lHole2_123 = mef(vHole2_1, vHole2_3, lBottom1234);

  kemr(v1, vHole2_1, lBottom1234);

  kfmrh(lTop1234, lHole2_123);



  

  // called only once
  GLdouble distance = 2.0;
  glm::vec3 direction(1, 0., 2.);
  sweep(lTop1234->lface, direction, distance);

  return solid;
}

void tessBeginCB(GLenum which) { glBegin(which); }

void tessEndCB() { glEnd(); }

void tessVertexCB(const GLvoid *data) {
  // cast back to double type
  const GLdouble *ptr = (const GLdouble *)data;

  glVertex3dv(ptr);
  glColor3dv(ptr + 3);
}

void drawCubeWithHoles() {

  gluTessBeginPolygon(tess, NULL);

  gluTessBeginContour(tess);

  double outerVertices[4][3] = {
      {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 0.0}};

  for (int i = 0; i < 4; ++i) {
    gluTessVertex(tess, outerVertices[i], outerVertices[i]);
  }

  gluTessEndContour(tess);

  gluTessBeginContour(tess);

  double innerVertices1[4][3] = {{0.25, 0.25, 0.0},
                                 {0.75, 0.25, 0.0},
                                 {0.75, 0.75, 0.0},
                                 {0.25, 0.75, 0.0}};

  for (int i = 0; i < 4; ++i) {
    gluTessVertex(tess, innerVertices1[i], innerVertices1[i]);
  }

  gluTessEndContour(tess);

  gluTessBeginContour(tess);

  double innerVertices2[4][3] = {{0.25, 0.25, 0.5},
                                 {0.75, 0.25, 0.5},
                                 {0.75, 0.75, 0.5},
                                 {0.25, 0.75, 0.5}};

  for (int i = 0; i < 4; ++i) {
    gluTessVertex(tess, innerVertices2[i], innerVertices2[i]);
  }

  gluTessEndContour(tess);

  gluTessEndPolygon(tess);
}