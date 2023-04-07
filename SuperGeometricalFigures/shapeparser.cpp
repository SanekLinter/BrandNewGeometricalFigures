#include <iostream>
#include "shapeparser.h"
#include "ellipse.h"
#include "rectangle.h"
#include "ñompositeshape.h"

ShapeCollection::ShapeCollection() :
	size(0),
	shapes(nullptr)
{}

ShapeCollection::~ShapeCollection() {
	for (int i = 0; i < size; ++i)
		delete shapes[i];
	delete shapes;
}

Shape** ShapeCollection::getShapes() {
	return shapes;
}

int ShapeCollection::getSize() {
	return size;
}

void ShapeCollection::add(Shape* newShape) {
	Shape** newCollection = new Shape* [size + 1];
	for (int i = 0; i < size; ++i) {
		newCollection[i] = shapes[i];
	}
	newCollection[size] = newShape;
	++size;
	delete shapes;
	shapes = newCollection;
}

void ShapeCollection::clear() {
	for (int i = 0; i < size; ++i)
		delete shapes[i];
	delete shapes;
	size = 0;
	shapes = nullptr;
}

void ShapeCollection::showInfo(std::ostream& out) {
	for (int i = 0; i < size; ++i) {
		out << *shapes[i] << '\n';
	}
}

Shape*& ShapeCollection::operator[](int number) {
	return shapes[number];
}


TypesOfCommand getTypesOfCommand(std::string command) {
	if (command == "ELLIPSE") {
		return TypesOfCommand::ELLIPSE;
	}
	if (command == "RECTANGLE") {
		return TypesOfCommand::RECTANGLE;
	}
	if (command == "COMPLEX") {
		return TypesOfCommand::COMPLEX;
	}
	if (command == "COMPLEXEND") {
		return TypesOfCommand::COMPLEXEND;
	}
	if (command == "SCALE") {
		return TypesOfCommand::SCALE;
	}
	if (command == "MOVE") {
		return TypesOfCommand::MOVE;
	}
	return TypesOfCommand::IGNORE;
}

void doCommand(TypesOfCommand& command, inputFileProcessing_t& parser) {
	switch (command) {
	case TypesOfCommand::ELLIPSE:
		readEllipse(parser);
		break;
	case TypesOfCommand::RECTANGLE:
		readRectangle(parser);
		break;
	case TypesOfCommand::COMPLEX:
		if (parser.isFillingComplex)
			throw std::invalid_argument("COMPLEX command within the definition of the composite shape");
		readComplex(parser);
		break;
	case TypesOfCommand::COMPLEXEND:
		if (!parser.isFillingComplex)
			throw std::invalid_argument("Unpaired COMPLEXEND command");
		readCompelxEnd(parser);
		break;
	case TypesOfCommand::SCALE:
		sortShapes(parser.allShapes.getShapes(), parser.allShapes.getSize());
		parser.allShapes.showInfo(std::cout);
		std::cout << "SCALE\n";
		doScale(parser);
		break;
	case TypesOfCommand::MOVE:
		sortShapes(parser.allShapes.getShapes(), parser.allShapes.getSize());
		parser.allShapes.showInfo(std::cout);
		std::cout << "MOVE\n";
		doMove(parser);
		break;
	case TypesOfCommand::IGNORE:
		doIgnore(parser);
		break;
	}
}

void readEllipse(inputFileProcessing_t& parser) {
	double centerX = 0.0;
	double centerY = 0.0;
	double verticalRadius = 0.0;
	double horizontalRadius = 0.0;
	parser.lineStream >> centerX >> centerY >> verticalRadius >> horizontalRadius;
	if (!parser.lineStream || (verticalRadius <= 0.0) || (horizontalRadius <= 0.0))
		throw std::invalid_argument("The ellipse is defined with incorrect data");
	if (parser.isFillingComplex)
		parser.shapesForComplex.add(new Ellipse(centerX, centerY, verticalRadius, horizontalRadius));
	else
		parser.allShapes.add(new Ellipse(centerX, centerY, verticalRadius, horizontalRadius));
}

void readRectangle(inputFileProcessing_t& parser) {
	double bottomLeftX = 0.0;
	double bottomLeftY = 0.0;
	double topRightX = 0.0;
	double topRightY = 0.0;
	parser.lineStream >> bottomLeftX >> bottomLeftY >> topRightX >> topRightY;
	if(!parser.lineStream || (bottomLeftX >= topRightX) || (bottomLeftY >= topRightY))
		throw std::invalid_argument("The rectangle is defined with incorrect data");
	if (parser.isFillingComplex)
		parser.shapesForComplex.add(new Rectangle(bottomLeftX, bottomLeftY, topRightX, topRightY));
	else
		parser.allShapes.add(new Rectangle(bottomLeftX, bottomLeftY, topRightX, topRightY));
}

void readComplex(inputFileProcessing_t& parser) {
	int size = 0;
	parser.lineStream >> size;
	if (!parser.lineStream || (size <= 0))
		throw std::invalid_argument("The number of simple shapes of complex shape is defined with incorrect data");
	parser.isFillingComplex = true;
}

void readCompelxEnd(inputFileProcessing_t& parser) {
	parser.isFillingComplex = false;
	if (parser.shapesForComplex.getSize() == 0)
		throw std::invalid_argument("The complex figure is defined by a zero number of simple shapes");
	parser.allShapes.add(new CompositeShape(parser.shapesForComplex.getShapes(), parser.shapesForComplex.getSize()));
	parser.shapesForComplex.clear();
}

void doScale(inputFileProcessing_t& parser) {
	point_t pointOfScale;
	double zoomRatio = 0.0;
	parser.lineStream >> pointOfScale.x >> pointOfScale.y >> zoomRatio;
	if (!parser.lineStream || zoomRatio <= 0.0)
		throw std::invalid_argument("The scale operation is defined with incorrect data");
	for (int i = 0; i < parser.allShapes.getSize(); ++i) {
		const rectangle_t& old_frame = parser.allShapes[i]->getFrameRect();
		point_t oldPoint{ old_frame.pos.x - old_frame.width / 2.0, old_frame.pos.y - old_frame.height / 2.0 };

		parser.allShapes[i]->move(pointOfScale);

		const rectangle_t& new_frame = parser.allShapes[i]->getFrameRect();
		point_t newPoint{ new_frame.pos.x - new_frame.width / 2.0, new_frame.pos.y - new_frame.height / 2.0 };

		point_t vector_delta{ oldPoint.x - newPoint.x, oldPoint.y - newPoint.y };

		parser.allShapes[i]->scale(zoomRatio);
		vector_delta.x *= zoomRatio;
		vector_delta.y *= zoomRatio;

		parser.allShapes[i]->move(vector_delta.x, vector_delta.y);
	}
}

void doMove(inputFileProcessing_t& parser) {
	double dx = 0.0;
	double dy = 0.0;
	parser.lineStream >> dx >> dy;
	if (!parser.lineStream)
		throw std::invalid_argument("The move operation is defined with incorrect data");
	for (int i = 0; i < parser.allShapes.getSize(); ++i)
		parser.allShapes[i]->move(dx, dy);
}

void doIgnore(inputFileProcessing_t& parser) {
	parser.lineStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
