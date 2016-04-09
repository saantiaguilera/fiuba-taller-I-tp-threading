//============================================================================
// Name        : tp.cpp
// Author      : Santi Aguilera
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <list>
#include <map>

class Expression;

#include "ParserUtils.h"
#include "Expression.h"

int main() {
	ParserUtils parser;
	std::string line;

	while (std::getline(std::cin, line)) {
		try {
			parser.run(line);
		} catch (int exception) {
			std::cout << "ERROR: " << line << std::endl;
		}
	}

	return 0;
}
