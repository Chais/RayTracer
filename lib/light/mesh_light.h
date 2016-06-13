//
// Created by chais on 21/03/16.
//

#ifndef RAY_TRACER_MESH_LIGHT_H
#define RAY_TRACER_MESH_LIGHT_H

#include "light.h"
#include "../geometry/shapes/mesh.h"
#include "../sampler/random_sampler.h"

class mesh_light : public light, public mesh {
protected:
	std::vector<float> cr_areas = std::vector<float>();
	float total_area = 0;
public:
	virtual const float get_total_area() const override;

	virtual intersection intersect_self(const ray &r) const;

public:
	mesh_light(const direction &offset, const std::shared_ptr<material> &matrl,
			   const std::shared_ptr<std::vector<std::shared_ptr<triangle>>> &faces);

	mesh_light(const std::shared_ptr<mesh> &m);

	virtual const std::shared_ptr<std::vector<intersection>> get_directions(const position &pos,
																		 const unsigned long &samples) const override;

	virtual const std::shared_ptr<color> emit(const direction &dir, const intersection &is) const override;

	virtual const std::shared_ptr<std::vector<ray>> shed(unsigned long samples) const override;
};

#endif //RAY_TRACER_MESH_LIGHT_H