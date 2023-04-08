#ifndef SHAPEPARSER_H
#define SHAPEPARSER_H
#include <sstream>
#include "shapecollection.h"

enum class TypesOfCommand {
	IGNORE,
	MOVE,
	SCALE,
	COMPLEX,
	COMPLEXEND,
	RECTANGLE,
	ELLIPSE,
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

TypesOfCommand getTypesOfCommand(std::string str);
void doCommand(TypesOfCommand& command, InputFileParser& parser);
void readEllipse(InputFileParser& parser);
void readRectangle(InputFileParser& parser);
void readComplex(InputFileParser& parser);
void readCompelxEnd(InputFileParser& parser);
void doScale(InputFileParser& parser);
void doMove(InputFileParser& parser);
void doIgnore(InputFileParser& parser);
#endif