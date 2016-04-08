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
/*
	while (std::getline(std::cin, line)) {
		std::cout << "LINE:: " << line << std::endl;
		parser.run(line);
	}*/

	std::string a = "(setq a (list 1 2 3))";
	std::string b = "(print a)";
	parser.run(a);
	parser.run(b);

	return 0;
}
