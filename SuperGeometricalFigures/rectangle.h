/*
Прямоугольник. Описывается парой координат своих углов: левым нижним и
правым верхним. Считается, что стороны прямоугольника параллельны осям
координат. Центром фигуры считается точка пересечения диагоналей
RECTANGLE 1.0 1.0 3.0 4.0
*/
#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"
class Rectangle : public Shape{
private:
	point_t bottomLeft;
	point_t topRight;
	point_t center;
public:
	Rectangle(double bottomLeftX, double bottomLeftY, double topRightX, double topRightY);
	Rectangle(const Rectangle& other);
	~Rectangle() = default;
	double getArea() const override;
	rectangle_t getFrameRect() const override;
	void move(const point_t& point) override;
	void move(const double& dx, const double& dy) override;
	void scale(const double& zoomRatio) override;
	std::string getName() const override;
	Shape* clone() const override;
};
#endif