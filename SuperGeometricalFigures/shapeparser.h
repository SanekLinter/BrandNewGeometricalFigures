#ifndef SHAPEPARSER_H
#define SHAPEPARSER_H
#include <sstream>
#include "shape.h"

enum class TypesOfCommand {
	RECTANGLE,
	ELLIPSE,
	COMPLEX,
	COMPLEXEND,
	MOVE,
	SCALE,
	IGNORE
};

class ShapeCollection {
private:
	int size;
	Shape** shapes;
public:
	ShapeCollection();
	~ShapeCollection();
	Shape** getShapes();
	int getSize();
	void add(Shape* newShape);
	void clear();
	void showInfo(std::ostream& out);
	Shape*& operator[](int number);
};

struct inputFileProcessing_t {
	ShapeCollection allShapes;
	std::string line;
	std::string command;
	std::stringstream lineStream;
	bool isFillingComplex = false;
	ShapeCollection shapesForComplex;
};

TypesOfCommand getTypesOfCommand(std::string str);
void doCommand(TypesOfCommand& command, inputFileProcessing_t& parser);
void readEllipse(inputFileProcessing_t& parser);
void readRectangle(inputFileProcessing_t& parser);
void readComplex(inputFileProcessing_t& parser);
void readCompelxEnd(inputFileProcessing_t& parser);
void doScale(inputFileProcessing_t& parser);
void doMove(inputFileProcessing_t& parser);
void doIgnore(inputFileProcessing_t& parser);
#endif