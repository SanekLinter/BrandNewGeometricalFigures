/*
����������� ������������ ������ Shape.����
����� ������ ������������� ��������� ������ :
->getArea ���������� �������
->getFrameRect ��������� ��������������� �������������� ��� ������(��.
���� �� ����������� ������), ������� ��������������� �������������� ������
����������� ����
->move ����������� ������ ������, ����������� � ���� ��������� :
����������� � ���������� �����
�������� �� ���� ������� � �������
->scale ���������� ��������������� ������ ������������ � ������ � ���������
�������������
->getName ��������� �������� ������(RECTANGLE, CIRCLE, COMPLEX � �.�.),
����� ������������ ��� ������
->clone �������� ����� ������ � ������������ ������ � ��������� ��������� ��
��� �����
*/
#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include "base-types.h"
class Shape {
public:
	virtual ~Shape() = default;
	virtual double getArea() const = 0;
	virtual rectangle_t getFrameRect() const = 0;
	virtual void move(const point_t& point) = 0;
	virtual void move(const double& dx, const double& dy) = 0;
	virtual void scale(const double& zoomRatio) = 0;
	virtual std::string getName() const = 0;
	virtual Shape* clone() const = 0;
	bool operator<(const Shape& b);
	friend std::ostream& operator<<(std::ostream& out, const Shape& shape);
	friend void sortShapes(Shape* shapes[], const int& length);
};
#endif