#include "HalfEdgeStructure.hpp"

namespace euler {

HalfEdge *Loop::findHEwithEndV(const Vertex *v) {
  HalfEdge *temp = startHalfEdge;
  do {
    if (temp->endV == v) {
      return temp;
    }
    temp = temp->next;
  } while (temp != startHalfEdge);
  return nullptr;
}

HalfEdge *Loop::findHalfEdge(const Vertex *startV, const Vertex *endV) {
  HalfEdge *temp = startHalfEdge->next;
  do {
    if (temp->startV == startV && temp->endV == endV) {
      return temp;
    }
    temp = temp->next;
  } while (temp != startHalfEdge);
  return nullptr;
}
} // namespace euler