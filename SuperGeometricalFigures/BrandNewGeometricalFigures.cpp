#include <iostream>
#include <fstream>
#include "shapeparser.h"
#include "shapecollection.h"

int main()
{
	InputFileParser &parser = InputFileParser::Instance();

	std::ifstream inputFile("input1.txt");
	if (!inputFile) {
		std::cerr << "Input file don`t open\n";
		return -1;
	}
	while (!inputFile.eof()) {
		std::getline(inputFile, parser.lineString);
		parser.lineStream << parser.lineString;
		parser.lineStream >> parser.command;
		TypesOfCommand commandType = getTypesOfCommand(parser.command);
		try {
			doCommand(commandType, parser);
		}
		catch (const std::invalid_argument& e) {
			std::cerr << e.what() << '\n';
		}

		parser.lineString.clear();
		parser.command.clear();
		parser.lineStream.clear();
	}
	parser.allShapes.showInfo(std::cout);
	inputFile.close();

	return 0;
}
