#include <iostream>
#include <fstream>
#include <sstream>
#include "ellipse.h"
#include "rectangle.h"
#include "сompositeshape.h"
#include "shapeparser.h"

int main()
{
	inputFileProcessing_t parser;

	std::ifstream inputFile("input1.txt");
	if (!inputFile) {
		std::cerr << "Input file don`t open\n";
		return -1;
	}
	while (!inputFile.eof()) {
		std::getline(inputFile, parser.line);
		parser.lineStream << parser.line;
		parser.lineStream >> parser.command;
		TypesOfCommand commandType = getTypesOfCommand(parser.command);
		try {
			doCommand(commandType, parser);
		}
		catch (const std::invalid_argument& e) {
			std::cerr << e.what() << '\n';
		}

		parser.line.clear();
		parser.command.clear();
		parser.lineStream.clear();
	}
	parser.allShapes.showInfo(std::cout);
	inputFile.close();

	return 0;
}
