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

    try {
	while (std::getline(std::cin, line))
		parser.run(line);
	} catch (int exception) {
		std::cout << "EXCEPTION THROWN, RETURNING :: " << exception << std::endl;
		return exception;
	}
/*
	try {
		std::string a = "1 2 3";
		std::string b = "ERROR: (print (list 1 2 3)";
		parser.run(a);
		parser.run(b);
	} catch (int exception) {
		return exception;
	}
*/
	return 0;
}
