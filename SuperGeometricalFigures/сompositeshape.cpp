#include "ñompositeshape.h"

CompositeShape::CompositeShape(ShapeCollection&& src)
{
	_shapes = std::move(src);

	const rectangle_t& frame = _shapes[0]->getFrameRect();
	point_t totalBottomLeft{ frame.pos.x - frame.width / 2.0, frame.pos.y - frame.height / 2.0 };
	point_t   totalTopRight{ frame.pos.x + frame.width / 2.0, frame.pos.y + frame.height / 2.0 };

	for (size_t i = 1; i < _shapes.getSize(); ++i) {
		const rectangle_t& frame = _shapes[i]->getFrameRect();
		totalBottomLeft.x        = std::min(totalBottomLeft.x, frame.pos.x - frame.width / 2.0);
		totalBottomLeft.y		 = std::min(totalBottomLeft.y, frame.pos.y - frame.height / 2.0);
		totalTopRight.x			 = std::max(totalBottomLeft.x, frame.pos.x + frame.width / 2.0);
		totalTopRight.y			 = std::max(totalBottomLeft.y, frame.pos.y + frame.height / 2.0);
	}
	_frameRect.width  = totalTopRight.x - totalBottomLeft.x;
	_frameRect.height = totalTopRight.y - totalBottomLeft.y;
	_frameRect.pos.x  = (totalTopRight.x + totalBottomLeft.x) / 2.0;
	_frameRect.pos.y  = (totalTopRight.y + totalBottomLeft.y) / 2.0;
}

CompositeShape::CompositeShape(const CompositeShape& other) :
	_frameRect(other._frameRect)
{
	for (size_t i = 0; i < other._shapes.getSize(); ++i)
	{
		_shapes.add(other._shapes[i]->clone());
	}
}

double CompositeShape::getArea() const
{
	double totalArea = 0.0;
	for (size_t i = 0; i < _shapes.getSize(); ++i)
		totalArea += _shapes[i]->getArea();
	return totalArea;
}

rectangle_t CompositeShape::getFrameRect() const
{
	return _frameRect;
}

void CompositeShape::move(const point_t& point)
{
	point_t delta_vector{ point.x - _frameRect.pos.x, point.y - _frameRect.pos.y };
	this->move(delta_vector.x, delta_vector.y);
}

void CompositeShape::move(const double dx, const double dy)
{
	_frameRect.pos.x += dx;
	_frameRect.pos.y += dy;
	for (size_t i = 0; i < _shapes.getSize(); ++i)
		_shapes[i]->move(dx, dy);
}

void CompositeShape::scale(const double zoomRatio) 
{
	_frameRect.height *= zoomRatio;
	_frameRect.width  *= zoomRatio;
	for (size_t i = 0; i < _shapes.getSize(); ++i) {
		const rectangle_t& old_frame = _shapes[i]->getFrameRect();
		point_t oldPoint{ old_frame.pos.x - old_frame.width / 2.0, old_frame.pos.y - old_frame.height / 2.0 };

		_shapes[i]->move(_frameRect.pos);

		const rectangle_t& new_frame = _shapes[i]->getFrameRect();
		point_t newPoint{ new_frame.pos.x - new_frame.width / 2.0, new_frame.pos.y - new_frame.height / 2.0 };

		point_t vector_delta{ oldPoint.x - newPoint.x, oldPoint.y - newPoint.y };

		_shapes[i]->scale(zoomRatio);
		vector_delta.x *= zoomRatio;
		vector_delta.y *= zoomRatio;

		_shapes[i]->move(vector_delta.x, vector_delta.y);
	}
}

std::string CompositeShape::getName() const
{
	return "COMPLEX";
}

shape_ptr_t CompositeShape::clone() const
{
	shape_ptr_t clone = std::make_unique<CompositeShape>(*this);
	return clone;
}
