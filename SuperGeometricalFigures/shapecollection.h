#ifndef SHAPECOLLECTION_H
#define SHAPECOLLECTION_H
#include <vector>
#include "shape.h"

class ShapeCollection
{
public:
	// construct/copy/move/destrust
	ShapeCollection();
	ShapeCollection(const ShapeCollection& other)				 = delete;
	ShapeCollection(ShapeCollection&& other) noexcept;
	ShapeCollection& operator=(const ShapeCollection& other)	 = delete;
	ShapeCollection& operator=(ShapeCollection&& other) noexcept;
	~ShapeCollection() = default;
	// members
	void			   add(shape_ptr_t newShape);
	void			   clear();
	void			   showInfo(std::ostream& out) const;
	size_t			   getSize() const;
	void			   sortShapes();
	shape_ptr_t&	   operator[](size_t index);
	const shape_ptr_t& operator[](size_t index) const;
private:
	std::vector<shape_ptr_t> _shapes;
};

#endif