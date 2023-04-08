#include "rectangle.h"

Rectangle::Rectangle(double bottomLeftX, double bottomLeftY, double topRightX, double topRightY) :
	bottomLeft{ bottomLeftX, bottomLeftY },
	topRight{ topRightX, topRightY },
	center{ ((bottomLeftX + topRightX) / 2.0), ((bottomLeftY + topRightY) / 2.0) }
{}

Rectangle::Rectangle(const Rectangle& other) :
	bottomLeft(other.bottomLeft),
	topRight(other.topRight),
	center(other.center)
{}

double Rectangle::getArea() const
{
	const double horizontalSide = topRight.x - bottomLeft.x;
	const double verticalSide = topRight.y - bottomLeft.y;
	return horizontalSide * verticalSide;
}

rectangle_t Rectangle::getFrameRect() const
{
	rectangle_t frameRect;
	frameRect.width = topRight.x - bottomLeft.x;
	frameRect.height = topRight.y - bottomLeft.y;
	frameRect.pos.x = center.x;
	frameRect.pos.y = center.y;
	return frameRect;
}

void Rectangle::move(const point_t& point)
{
	point_t delta{ topRight.x - center.x, topRight.y - center.y };
	center.x = point.x;
	center.y = point.y;
	topRight.x = center.x + delta.x;
	topRight.y = center.y + delta.y;
	bottomLeft.x = center.x - delta.x;
	bottomLeft.y = center.y - delta.y;
}

void Rectangle::move(const double dx, const double dy)
{
	bottomLeft.x += dx;
	bottomLeft.y += dy;
	topRight.x += dx;
	topRight.y += dy;
	center.x += dx;
	center.y += dy;
}

void Rectangle::scale(const double zoomRatio)
{
	point_t delta{ topRight.x - center.x, topRight.y - center.y };
	delta.x *= zoomRatio;
	delta.y *= zoomRatio;
	topRight.x = center.x + delta.x;
	topRight.y = center.y + delta.y;
	bottomLeft.x = center.x - delta.x;
	bottomLeft.y = center.y - delta.y;
}

std::string Rectangle::getName() const
{
	return "RECTANGLE";
}

std::unique_ptr<Shape> Rectangle::clone() const
{
	std::unique_ptr<Shape> clone = std::make_unique<Rectangle>(*this);
	return clone;
}
