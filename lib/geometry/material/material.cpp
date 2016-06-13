//
// Created by chais on 29/03/16.
//

#include "material.h"


material::material(const std::shared_ptr<color> emit_col, const std::shared_ptr<color> col) : emittance(emit_col),
																							  col(col) { }

const std::shared_ptr<color> material::get_emittance() const {
	return emittance;
}