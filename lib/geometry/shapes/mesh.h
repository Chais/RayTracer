//
// Created by chais on 18.09.15.
//

#ifndef RAY_TRACER_MESH_H
#define RAY_TRACER_MESH_H

#include "shape.h"
#include "triangle.h"

class mesh: public shape {
 protected:
  std::vector<triangle *> *faces;
 public:
  mesh(const direction *offset, const material *matrl, std::vector<triangle *> *faces);

  virtual intersection intersect_full(const ray &r);

  virtual bool intersect_shadow(const point &o, const direction &d);
};

#endif //RAY_TRACER_MESH_H
