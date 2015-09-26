//
// Created by chais on 25.08.15.
//

#include "transform.h"

transform::transform() : trans(new mat4()), inv_trans(new mat4()) { }

transform::transform(mat4 *trans) : trans(trans), inv_trans(new mat4(invert(*trans))) { }

transform::transform(mat4 *trans, mat4 *inv_trans) : trans(trans), inv_trans(inv_trans) { }

transform::transform(const transform &in) : trans(in.trans), inv_trans(in.inv_trans) { }

transform transform::operator()(const transform &t) const {
	return transform(new mat4(*this->trans*(*t.trans)), new mat4(*t.inv_trans*(*this->inv_trans)));
}

point transform::operator()(const point &p) const {
	return point(*this->trans*p);
}

direction transform::operator()(const direction &v) const {
	return direction(*this->trans*v);
}

normal transform::operator()(const normal &n) const {
	return normal(transpose(*this->inv_trans)*n);
}

ray transform::operator()(const ray &r) const {
	return ray(*this->trans*r.o, *this->trans*r.d);
}

std::ostream &operator<<(std::ostream &out, const transform &a) {
	out << "Transform: " << a.trans << ", Inverse: " << a.inv_trans;
	return out;
}

void transform::translate(const direction t) {
	std::array<std::array<float, 4>, 4> tmp = {{
												   {1, 0, 0, t[0]},
												   {0, 1, 0, t[1]},
												   {0, 0, 1, t[2]},
												   {0, 0, 0, 1}
											   }};
	std::array<std::array<float, 4>, 4> itmp = {{
													{1, 0, 0, -t[0]},
													{0, 1, 0, -t[1]},
													{0, 0, 1, -t[2]},
													{0, 0, 0, 1}
												}};
	*this->trans = mat4(tmp)*(*this->trans);
	*this->inv_trans = *this->inv_trans*mat4(itmp);
}

void transform::scale(const std::array<float, 3> sf) {
	std::array<std::array<float, 4>, 4> tmp = {{
												   {sf[0], 0, 0, 0},
												   {0, sf[1], 0, 0},
												   {0, 0, sf[2], 0},
												   {0, 0, 0, 1}
											   }};
	std::array<std::array<float, 4>, 4> itmp = {{
													{1/sf[0], 0, 0, 0},
													{0, 1/sf[1], 0, 0},
													{0, 0, 1/sf[2], 0},
													{0, 0, 0, 1}
												}};
	*this->trans = mat4(tmp)*(*this->trans);
	*this->inv_trans = *this->inv_trans*mat4(itmp);
}

void transform::rotateX(const float &angle) {
	float a = helper::to_radians(angle);
	/*std::array<std::array<float, 4>, 4> tmp = {{
													   {1, 0, 0, 0},
													   {0, cos(a), -sin(a), 0},
													   {0, sin(a), cos(a), 0},
													   {0, 0, 0, 1}
	}};
	std::array<std::array<float, 4>, 4> itmp = {{
														{1, 0, 0, 0},
														{0, cos(-a), -sin(-a), 0},
														{0, sin(-a), cos(-a), 0},
														{0, 0, 0, 1}
												}};*/
	float c = std::cos(a);
	float s = std::sin(a);
	std::array<std::array<float, 4>, 4> tmp = {{
												   {1, 0, 0, 0},
												   {0, c, -s, 0},
												   {0, s, c, 0},
												   {0, 0, 0, 1}
											   }};
	std::array<std::array<float, 4>, 4> itmp = {{
													{1, 0, 0, 0},
													{0, c, s, 0},
													{0, -s, c, 0},
													{0, 0, 0, 1}
												}};
	*this->trans = mat4(tmp)*(*this->trans);
	*this->inv_trans = *this->inv_trans*mat4(itmp);
}

void transform::rotateY(const float &angle) {
	float a = helper::to_radians(angle);
	/*std::array<std::array<float, 4>, 4> tmp = {{
													   {cos(a), 0, sin(a), 0},
													   {0, 1, 0, 0},
													   {-sin(a), 0, cos(a), 0},
													   {0, 0, 0, 1}
											   }};
	std::array<std::array<float, 4>, 4> itmp = {{
														{cos(-a), 0, sin(-a), 0},
														{0, 1, 0, 0},
														{-sin(-a), 0, cos(-a), 0},
														{0, 0, 0, 1}
	}};*/
	float c = std::cos(a);
	float s = std::sin(a);
	std::array<std::array<float, 4>, 4> tmp = {{
												   {c, 0, s, 0},
												   {0, 1, 0, 0},
												   {-s, 0, c, 0},
												   {0, 0, 0, 1}
											   }};
	std::array<std::array<float, 4>, 4> itmp = {{
													{c, 0, -s, 0},
													{0, 1, 0, 0},
													{s, 0, c, 0},
													{0, 0, 0, 1}
												}};
	*this->trans = mat4(tmp)*(*this->trans);
	*this->inv_trans = *this->inv_trans*mat4(itmp);
}

void transform::rotateZ(const float &angle) {
	float a = helper::to_radians(angle);
	/*std::array<std::array<float, 4>, 4> tmp = {{
													   {std::cos(a), -std::sin(a), 0, 0},
													   {std::sin(a), std::cos(a), 0, 0},
													   {0, 0, 1, 0},
													   {0, 0, 0, 1}
											   }};
	std::array<std::array<float, 4>, 4> itmp = {{
														{std::cos(-a), -std::sin(-a), 0, 0},
														{std::sin(-a), std::cos(-a), 0, 0},
														{0, 0, 1, 0},
														{0, 0, 0, 1}
												}};*/
	float c = std::cos(a);
	float s = std::sin(a);
	std::array<std::array<float, 4>, 4> tmp = {{
												   {c, -s, 0, 0},
												   {s, c, 0, 0},
												   {0, 0, 1, 0},
												   {0, 0, 0, 1}
											   }};
	std::array<std::array<float, 4>, 4> itmp = {{
													{c, s, 0, 0},
													{-s, c, 0, 0},
													{0, 0, 1, 0},
													{0, 0, 0, 1}
												}};
	*this->trans = mat4(tmp)*(*this->trans);
	*this->inv_trans = *this->inv_trans*mat4(itmp);
}
