#ifndef SHAPECOLLECTION_H
#define SHAPECOLLECTION_H
#include "shape.h"
#include <vector>
#include <memory>

class ShapeCollection {
private:
	std::vector<std::unique_ptr<Shape>> _shapes;
public:
	ShapeCollection();
	ShapeCollection(const ShapeCollection& other)            = delete;
	ShapeCollection(ShapeCollection&& other);
	ShapeCollection& operator=(const ShapeCollection& other) = delete;
	ShapeCollection& operator=(ShapeCollection&& other);
	~ShapeCollection() = default;
	void					add(std::unique_ptr<Shape> newShape);
	void					clear();
	void                    showInfo(std::ostream& out) const;
	size_t					getSize() const;
	void                    sortShapes();
	std::unique_ptr<Shape>& operator[](size_t index);
	const std::unique_ptr<Shape>& operator[](size_t index) const;
};

#endif