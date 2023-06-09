/*
������.����������� ������������ ������ � ����� ���������� �������� : ��
������������ ��� � �� �������������� ���.���������, ��� ��� ������� �����������
���� �����������.������� ������ ��������� ����� ����������� ���� �������
ELLIPSE 0.0 0.0 5.0 7.0
*/
#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "shape.h"
class Ellipse : public Shape
{
public:
	// construct/copy/move/destrust
	Ellipse(double centerX, double centerY, double verticalRadius, double horizontalRadius);
	Ellipse(const Ellipse& other);
	Ellipse(Ellipse&& other)                 = delete;
	Ellipse& operator=(const Ellipse& other) = delete;
	Ellipse& operator=(Ellipse&& other)      = delete;
	~Ellipse() = default;
	// members
	double		getArea() const override;
	rectangle_t getFrameRect() const override;
	void		move(const point_t& point) override;
	void		move(const double dx, const double dy) override;
	void		scale(const double zoomRatio) override;
	std::string getName() const override;
	shape_ptr_t clone() const override;
private:
	double verticalRadius;
	double horizontalRadius;
	point_t center;
};
#endif