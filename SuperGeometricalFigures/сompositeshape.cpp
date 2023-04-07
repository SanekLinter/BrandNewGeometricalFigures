#include "ñompositeshape.h"
#include <iostream>

CompositeShape::CompositeShape(Shape** fragments, const int& limitShapes) :
	size(limitShapes)
{
	shapes = new Shape* [limitShapes];
	for (int i = 0; i < limitShapes; ++i) {
		shapes[i] = fragments[i]->clone();
	}

	const rectangle_t& frame = shapes[0]->getFrameRect();
	point_t totalBottomLeft{ frame.pos.x - frame.width / 2.0, frame.pos.y - frame.height / 2.0 };
	point_t totalTopRight{ frame.pos.x + frame.width / 2.0, frame.pos.y + frame.height / 2.0 };

	for (int i = 1; i < limitShapes; ++i) {
		const rectangle_t& frame = shapes[i]->getFrameRect();
		totalBottomLeft.x = std::min(totalBottomLeft.x, frame.pos.x - frame.width / 2.0);
		totalBottomLeft.y = std::min(totalBottomLeft.y, frame.pos.y - frame.height / 2.0);
		totalTopRight.x = std::max(totalBottomLeft.x, frame.pos.x + frame.width / 2.0);
		totalTopRight.y = std::max(totalBottomLeft.y, frame.pos.y + frame.height / 2.0);
	}
	frameRect.width = totalTopRight.x - totalBottomLeft.x;
	frameRect.height = totalTopRight.y - totalBottomLeft.y;
	frameRect.pos.x = (totalTopRight.x + totalBottomLeft.x) / 2.0;
	frameRect.pos.y = (totalTopRight.y + totalBottomLeft.y) / 2.0;
}

CompositeShape::CompositeShape(const CompositeShape& other) :
	size(other.size),
	frameRect(other.frameRect)
{
	shapes = new Shape* [size];
	for (int i = 0; i < size; ++i) {
		shapes[i] = other.shapes[i]->clone();
	}
}

CompositeShape::~CompositeShape()
{
	for (int i = 0; i < size; ++i) {
		delete shapes[i];
	}
	delete[] shapes;
}

double CompositeShape::getArea() const
{
	double totalArea = 0.0;
	for (int i = 0; i < size; ++i)
		totalArea += shapes[i]->getArea();
	return totalArea;
}

rectangle_t CompositeShape::getFrameRect() const
{
	return frameRect;
}

void CompositeShape::move(const point_t& point)
{
	point_t delta_vector{ point.x - frameRect.pos.x, point.y - frameRect.pos.y };
	this->move(delta_vector.x, delta_vector.y);
}

void CompositeShape::move(const double& dx, const double& dy)
{
	frameRect.pos.x += dx;
	frameRect.pos.y += dy;
	for (int i = 0; i < size; ++i)
		shapes[i]->move(dx, dy);
}

void CompositeShape::scale(const double& zoomRatio) 
{
	frameRect.height *= zoomRatio;
	frameRect.width *= zoomRatio;
	for (int i = 0; i < size; ++i) {
		const rectangle_t& old_frame = shapes[i]->getFrameRect();
		point_t oldPoint{ old_frame.pos.x - old_frame.width / 2.0, old_frame.pos.y - old_frame.height / 2.0 };

		shapes[i]->move(this->frameRect.pos);

		const rectangle_t& new_frame = shapes[i]->getFrameRect();
		point_t newPoint{ new_frame.pos.x - new_frame.width / 2.0, new_frame.pos.y - new_frame.height / 2.0 };

		point_t vector_delta{ oldPoint.x - newPoint.x, oldPoint.y - newPoint.y };

		shapes[i]->scale(zoomRatio);
		vector_delta.x *= zoomRatio;
		vector_delta.y *= zoomRatio;

		shapes[i]->move(vector_delta.x, vector_delta.y);
	}
}

std::string CompositeShape::getName() const
{
	return "COMPLEX";
}

Shape* CompositeShape::clone() const
{
	Shape* clone = new CompositeShape(*this);
	return clone;
}
