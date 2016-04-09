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
#include <stdexcept>

class Expression;

#include "ParserUtils.h"
#include "Expression.h"

int main(int argc, char *argv[]) {
	ParserUtils parser;
	std::string line;

	if (argc > 1) {
		std::cout << "ERROR: argumentos" << std::endl;
		return 1;
	}

	while (std::getline(std::cin, line)) {
		try {
			parser.run(line);
		} catch (const std::logic_error &exception) {
			if (exception.what() == EXCEPTION_BAD_FUNCTION) {
				std::cout << "ERROR: " << line << std::endl;
				return 2;
			}
		}
	}

	return 0;
}
