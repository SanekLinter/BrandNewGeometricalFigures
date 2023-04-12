#include "shapecollection.h"
#include <ostream>
#include <utility>
#include <algorithm>

ShapeCollection::ShapeCollection() :
	_shapes()
{}

ShapeCollection::ShapeCollection(ShapeCollection&& other) :
	_shapes(std::move(other._shapes))
{}

ShapeCollection& ShapeCollection::operator=(ShapeCollection&& other) {
	std::swap(this->_shapes, other._shapes);
	return *this;
}

void ShapeCollection::add(shape_ptr_t newShape) {
	_shapes.push_back(std::move(newShape));
}

void ShapeCollection::clear() {
	_shapes.clear();
}

void ShapeCollection::showInfo(std::ostream& out) const {
	for (size_t i = 0; i < getSize(); ++i) {
		out << *_shapes[i] << '\n';
	}
}

size_t ShapeCollection::getSize() const {
	return _shapes.size();
}

void ShapeCollection::sortShapes()
{
	std::sort(_shapes.begin(), _shapes.end(),
		[](const shape_ptr_t& a, const shape_ptr_t& b) {return *a < *b; });
}

shape_ptr_t& ShapeCollection::operator[](size_t index) {
	return _shapes[index];
}

const shape_ptr_t& ShapeCollection::operator[](size_t index) const {
	return _shapes[index];
}