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
#include "KnownFunctions.h"

class Expression;

#include "RuntimeExpressionInterface.h"
#include "ParserUtils.h"
#include "Expression.h"
#include "LispParser.h"

int main() {
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!

	//arithmetic
	//std::string a = "(+ 2 3 (* 5 2) (- 2 (/ 6 3)))";

	//logicals
	//std::string a = "(= (+ 5 7) (* 6 2) (- 24 10))"; //logic that fails
	//std::string a = "(= (+ 5 7) (* 6 2) (- 24 12))"; //logic that is good
	//std::string a = "(< (* 5 10000) (* 4 2))"; //Change brackets to see failing or good

	//lists
	//std::string a = "(list 5 2 3 4 (+ 1 2) (* 8 7))"; //6 elements
	std::string a = "(car 5 2 3 4 (+ 1 2) (* 8 7))"; //1 elements
	//std::string a = "(cdr 5 2 3 4 (+ 1 2) (* 8 7))"; //5 elements

	std::cout << "Lets parse: " << a << std::endl;

	LispParser parser(a);
	parser.run();

	return 0;
}
