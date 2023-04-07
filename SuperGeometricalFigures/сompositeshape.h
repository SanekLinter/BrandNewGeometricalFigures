/*
����������� ����� CompositeShape, ����������� �� Shape (��. ������ ��������),
�������������� ����� ��������� ������ � �������� ������ � ������������ ������
�� ������������ �����, ������������� � ����� ���������. ������� ������
������ ��������� ������������ � ������������. ��� ���������� �������
(�������������, ���� � �.�.) ������ � ���������, ����������� ������ ����� �������
������.
��������� ������. ������� �� ���������� ������� (�� ���������) �����.
����������� �� ���������� �������, ��������� � ���������� ������������
��������� (������ ��������� �� ��������� �������). � ������ ������ �����������
�������� � ����������� ��������� ���������� ������� �����. ������� ������
��������� ����� ��������������� ��������������
COMPLEX 5
ELLIPSE 2.0 3.0 15.0
RECTANGLE -5.0 -3.0 3.0 4.0
ELLIPSE 1.0 1.0 10.0
SQUARE -1.5 -1.5 10.0
SQUARE 0.0 0.0 5.0
COMPLEXEND
*/
#ifndef COMPOSITE_SHAPE_H
#define COMPOSITE_SHAPE_H
#include "shape.h"
class CompositeShape : public Shape {
private:
	std::size_t size;
	Shape** shapes;
	rectangle_t frameRect;
public:
	CompositeShape(Shape** fragments, const int& limitShapes);
	CompositeShape(const CompositeShape& other);
	~CompositeShape() override;
	double getArea() const override;
	rectangle_t getFrameRect() const override;
	void move(const point_t& point) override;
	void move(const double& dx, const double& dy) override;
	void scale(const double& zoomRatio) override;
	std::string getName() const override;
	Shape* clone() const override;
};
#endif