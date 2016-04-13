//
// Created by chais on 23.09.15.
//

#include "textured_material.h"

textured_material::textured_material(const std::shared_ptr<color> emit_col, const float &ambient, const float &diffuse,
									 const float &specular, const float &exponent,
									 std::shared_ptr<std::vector<std::vector<color>>> texture) : phong_material(
		emit_col, std::shared_ptr<color>(new color()), ambient, diffuse, specular, exponent), texture(texture) {
}

const std::shared_ptr<color> textured_material::shade(const color &lcol, const direction &l, const normal &n,
													  const direction &v, const vec2 &pos, const bool &internal) const {
	float U = pos[0] < 0 ? -pos[0] : pos[0];
	float V = pos[1] < 0 ? -pos[1] : pos[1];
	if (U > 1)
		U -= static_cast<int>(U);
	if (V > 1)
		V -= static_cast<int>(V);
	V *= (texture->size() - 1);
	U *= (texture->at(0).size() - 1);
	int lv = static_cast<int>(std::floor(V));
	int lu = static_cast<int>(std::floor(U));
	int hv = static_cast<int>(std::ceil(V));
	int hu = static_cast<int>(std::ceil(U));
	color ll = (*texture)[lv][lu];
	color lh = (*texture)[lv][hu];
	color hl = (*texture)[hv][lu];
	color hh = (*texture)[hv][hu];
	ll = (hu - U) * ll;
	lh = (U - lu) * lh;
	hl = (hu - U) * hl;
	hh = (U - lu) * hh;
	std::shared_ptr<color> out = std::make_shared<color>((hv - V) * (ll + lh) + (V - lv) * (hl + hh));
	if (l != direction()) {
		// Directional light
		if (!internal) {
			float phi = std::max<float>(0.0, dot(n, l));
			if (phi > 0) {
				direction r = n * (2 * phi) - l;
				*out = scale(*out, lcol * (diffuse * phi)) +
					   lcol * (std::pow(std::max<float>(0.0, dot(v, r)), exponent) * specular);
			}
		}
	} else
		// Ambient light
		*out = scale(*out, lcol * ambient);
	*out += *emit_col;
	return out;
}
