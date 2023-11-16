#include "Sweep.hpp"
#include "EulerOperation.hpp"

namespace euler {
// sweeping one loop
void SweepLoop(Loop *l, const GLdouble *offset) {
  HalfEdge *tmpHe, *bridgeHe;
  Vertex *startV, *endV;
  Vertex *initV;

  // sweeping
  tmpHe = l->startHalfEdge->next;
  Vertex *v0 = l->startHalfEdge->startV;
  bridgeHe =
      mev(tmpHe->prev->startV, Point(tmpHe->prev->startV->vpoint, offset), l);
  initV = startV = bridgeHe->endV;
  do {
    bridgeHe = mev(tmpHe->startV, Point(tmpHe->startV->vpoint, offset), l);
    endV = bridgeHe->endV;
    mef(startV, endV, l);
    startV = endV;
    tmpHe = tmpHe->next;
  } while (tmpHe->startV != v0);

  mef(startV, initV, l);
}
// sweeping one face
Solid *sweep(Face *f, const glm::vec3 &dir, const GLdouble dist) {
  Solid *solid = f->fsolid;
  Loop *outL = f->fouterloop;
  const GLdouble offset[3] = {dir.x * dist, dir.y * dist, dir.z * dist};

  // sweeping outer loop
  SweepLoop(outL, offset);

  // sweep inner loop
  for (auto *l : f->finnerloops) {
    SweepLoop(l, offset);
  }

  return solid;
}
} // namespace euler