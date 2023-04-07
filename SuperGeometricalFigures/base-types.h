/*
���������� ����������� ��������� ��������:
point_t, �������������� ����� ����� �� ���������.���������� ������
��������� � ����� x � y.
rectangle_t, ����������� ������������� ������� width � ������� height �
������� � ����� pos.
*/
#ifndef BASE_TYPES_H
#define BASE_TYPES_H
struct point_t {
	double x;
	double y;
};

struct rectangle_t {
	double width;
	double height;
	point_t pos;
};
#endif