#ifndef SHAPEPARSER_H
#define SHAPEPARSER_H
#include <sstream>
#include "shapecollection.h"

enum class TypesOfCommand {
	IGNORE     = 0,
	MOVE       = 1,
	SCALE      = 2,
	COMPLEX    = 3,
	COMPLEXEND = 4,
	RECTANGLE  = 5,
	ELLIPSE    = 6,
};

class InputFileParser
{
public:
	static InputFileParser& Instance();
	ShapeCollection   allShapes;
	std::string       lineString;
	std::stringstream lineStream;
	std::string       command;
	bool              isFillingComplex;
	ShapeCollection   shapesForComplex;
private:
	InputFileParser();
	InputFileParser(const InputFileParser& src) = delete;
	InputFileParser& operator=(const InputFileParser& src) = delete;
};

TypesOfCommand getTypesOfCommand(const std::string& command);
void doCommand(TypesOfCommand command, InputFileParser& parser);
void doIgnore(InputFileParser& parser);
void doMove(InputFileParser& parser);
void doScale(InputFileParser& parser);
void readComplex(InputFileParser& parser);
void readCompelxEnd(InputFileParser& parser);
void readRectangle(InputFileParser& parser);
void readEllipse(InputFileParser& parser);

#endif