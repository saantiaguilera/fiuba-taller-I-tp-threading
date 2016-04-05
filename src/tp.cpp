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
	//std::string a = "(+ 2 3 (* 5 2) (- 2 (/ 6 3)))"; //Returns 15

	//logicals
	//std::string a = "(= (+ 5 7) (* 6 2) (- 24 10))"; //Returns ()
	//std::string a = "(= (+ 5 7) (* 6 2) (- 24 12))"; //Returns 1
	//std::string a = "(> (* 5 10000) (* 4 2))"; //< Returns () ; > Returns 1

	//lists
	//std::string a = "(list 5 2 3 4 (+ 1 2) (* 8 7))"; //Returns size 6
	//std::string a = "(car 5 2 3 4 (+ 1 2) (* 8 7))"; //Returns size 1
	//std::string a = "(cdr 5 2 3 4 (+ 1 2) (* 8 7))"; //Returns size 5
	std::string a = "(append (list 50 12 43 84 (- 159 208)) (list 1 (* 2 5) 3 4))"; //Returns size 9

	std::cout << "Lets parse: " << a << std::endl;

	LispParser parser(a);
	parser.run();

	return 0;
}
