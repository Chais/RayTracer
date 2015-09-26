/**
 * @file whittedrt.h
 * @author Philip Abernethy
 * @brief A Whitted ray tracer
 */

#ifndef RAY_TRACER_WHITTEDRT_H
#define RAY_TRACER_WHITTEDRT_H

#include "camera/camera.h"
#include "light/light.h"
#include "geometry/shapes/shape.h"
#include <typeinfo>

class whitted_rt {
 private:
  const color *background_color;
  camera *cam;
  std::vector<light *> *lights;
  std::vector<shape *> *scene;

  color cast_ray(ray r, int step, bool internal);

  bool cast_shadow(const point &o, const direction &d);

  intersection find_nearest(ray r);

 public:
  whitted_rt(const color *background_color, camera *cam, std::vector<light *> *lights,
			 std::vector<shape *> *scene);

  void render();
  color *get_pixel(const unsigned long &x, const unsigned long &y) const;
  const std::array<unsigned long, 2> &get_resolution() const;
};

#endif //RAY_TRACER_WHITTEDRT_H