#include <iomanip>
#include <algorithm>
#include "shape.h"


bool Shape::operator<(const Shape& b)
{
    return this->getArea() < b.getArea();
}

/*
����������� �������� ������ << ��� ������ Shape.����� ������ ��������� � ����
������� : �������� ������, � �������, ���������� ������ ������� ���� � �������
�������� ���� ��������������� ��������������.�������� ��� ������ ������
����������� �� ������ ����� ����� ������� � ������������ � ��������� ����������.
*/
std::ostream& operator<<(std::ostream& out, const Shape& shape) {
	const rectangle_t& frame = shape.getFrameRect();
	const point_t& center = frame.pos;
	point_t* leftDown = new point_t;
	leftDown->x = center.x - frame.width / 2;
	leftDown->y = center.y - frame.height / 2;
	point_t* rightUp = new point_t;
	rightUp->x = center.x + frame.width / 2;
	rightUp->y = center.y + frame.height / 2;
	const int default_precision = out.precision();
	out << std::setprecision(1) << std::fixed;
	out << shape.getName() << ' ' << shape.getArea() << ' ' <<
		leftDown->x << ' ' << leftDown->y << ' ' << rightUp->x << ' ' << rightUp->y;
	out << std::setprecision(default_precision) << std::defaultfloat;
	return out;
}

/*
����������� �������, ����������� ������ ���������� �� ������ � �������
���������� �� ��������.
*/
void sortShapes(Shape* shapes[], const int& length) {
	std::sort(shapes, shapes + length, [](Shape* a, Shape* b) { return *a < *b; });
}
