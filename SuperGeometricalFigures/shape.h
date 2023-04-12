#ifndef SHAPE_H
#define SHAPE_H
#include <string>
#include <memory>
#include "base-types.h"
class Shape;
// types
using shape_ptr_t = std::unique_ptr<Shape>;

class Shape
{
public:
	// destruct
	virtual ~Shape() = default;
	// membres
	virtual double		getArea() const                        = 0;
	virtual rectangle_t	getFrameRect() const                   = 0;
	virtual void		move(const point_t& point)             = 0;
	virtual void		move(const double dx, const double dy) = 0;
	virtual void		scale(const double zoomRatio)          = 0;
	virtual std::string	getName() const                        = 0;
	virtual shape_ptr_t clone() const                          = 0;
	        bool		operator<(const Shape& other) const;
	// mom-member
	friend std::ostream& operator<<(std::ostream& out, const Shape& shape);
};
#endif