//
// Created by chais on 02.08.15.
//

#ifndef RAY_TRACER_SHAPE_H
#define RAY_TRACER_SHAPE_H

#include "../ray.h"
#include "../material/material.h"
#include "../transform.h"
#include "../intersection.h"
#include "../color.h"

class shape {
 private:
  shape() { };
 protected:
  transform object_to_world;
  transform world_to_object;
  const direction *offset;
  const material *matrl;

  shape(const direction *offset, const material *matrl);

 public:
  virtual intersection intersect_full(const ray &r) = 0;

  virtual bool intersect_shadow(const point &o, const direction &d) = 0;

  /**
   * @copydoc material::shade(const color &lcol,const direction &l,const normal &n,const direction &v,const vec2 &pos,const bool internal)
   */
  virtual color shade(const color &lcol, const direction &l, const normal &n, const direction &v, const vec2 &pos,
					  const bool internal);

  std::vector<ray> *reflect(const direction &i, const normal &n, const point &x, const unsigned int &s) const;
  std::vector<ray> *refract(const direction &i, const normal &n, const point &x, const unsigned int &s,
							const bool internal) const;
  void translate(const direction &t);
  void scale(const std::array<float, 3> sf);
  void rotateX(const float &angle);
  void rotateY(const float &angle);
  void rotateZ(const float &angle);
  const float get_reflectance() const;
  const float get_transmittance() const;
};

#endif //RAY_TRACER_SHAPE_H
