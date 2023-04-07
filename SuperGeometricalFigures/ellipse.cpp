#include "ellipse.h"
#include <cmath> //for atan(1) * 4 == pi

Ellipse::Ellipse(double centerX, double centerY, double verticalRadius, double horizontalRadius) :
	center{ centerX, centerY },
	verticalRadius(verticalRadius),
	horizontalRadius(horizontalRadius)
{}

Ellipse::Ellipse(const Ellipse& other) :
	verticalRadius(other.verticalRadius),
	horizontalRadius(other.horizontalRadius),
	center(other.center)
{}

double Ellipse::getArea() const
{
	return (atan(1) * 4) * verticalRadius * horizontalRadius;
}

rectangle_t Ellipse::getFrameRect() const
{
	rectangle_t frameRect;
	frameRect.width = 2.0 * horizontalRadius;
	frameRect.height = 2.0 * verticalRadius;
	frameRect.pos.x = center.x;
	frameRect.pos.y = center.y;
	return frameRect;
}

void Ellipse::move(const point_t& point)
{
	center.x = point.x;
	center.y = point.y;
}

void Ellipse::move(const double& dx, const double& dy)
{
	center.x += dx;
	center.y += dy;
}

void Ellipse::scale(const double& zoomRatio)
{
	verticalRadius *= zoomRatio;
	horizontalRadius *= zoomRatio;
}

std::string Ellipse::getName() const
{
	return "ELLIPSE";
}

Shape* Ellipse::clone() const
{
	Shape* clone = new Ellipse(*this);
	return clone;
}
