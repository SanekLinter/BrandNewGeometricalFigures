/*
Ёллипс.ќписываетс€ координатами центра и двум€ значени€ми радиусов : по
вертикальной оси и по горизонтальной оси.—читаетс€, что оси эллипса параллельны
ос€м координатам.÷ентром фигуры считаетс€ точка пересечени€ осей эллипса
ELLIPSE 0.0 0.0 5.0 7.0
*/
#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "shape.h"
class Ellipse : public Shape {
private:
	double verticalRadius;
	double horizontalRadius;
	point_t center;
public:
	Ellipse(double centerX, double centerY, double verticalRadius, double horizontalRadius);
	Ellipse(const Ellipse& other);
	Ellipse(Ellipse&& other)                 = delete;
	Ellipse& operator=(const Ellipse& other) = delete;
	Ellipse& operator=(Ellipse&& other)      = delete;
	~Ellipse()                               = default;
	double                 getArea() const override;
	rectangle_t            getFrameRect() const override;
	void                   move(const point_t& point) override;
	void                   move(const double dx, const double dy) override;
	void                   scale(const double zoomRatio) override;
	std::string            getName() const override;
	std::unique_ptr<Shape> clone() const override;
};
#endif