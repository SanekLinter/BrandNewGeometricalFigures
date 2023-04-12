#include <iomanip>
#include <algorithm>
#include "shape.h"

bool Shape::operator<(const Shape& other) const
{
    return this->getArea() < other.getArea();
}

std::ostream& operator<<(std::ostream& out, const Shape& shape) {
	const rectangle_t& frame = shape.getFrameRect();
	const point_t& center    = frame.pos;
	point_t leftDown         = point_t();
	leftDown.x               = center.x - frame.width / 2;
	leftDown.y               = center.y - frame.height / 2;
	point_t rightUp          = point_t();
	rightUp.x                = center.x + frame.width / 2;
	rightUp.y                = center.y + frame.height / 2;
	const std::streamsize default_precision = out.precision();
	out << std::setprecision(1) << std::fixed;
	out << shape.getName() << ' ' << shape.getArea() << ' ' <<
		leftDown.x << ' ' << leftDown.y << ' ' << rightUp.x << ' ' << rightUp.y;
	out << std::setprecision(default_precision) << std::defaultfloat;
	return out;
}

