//============================================================================
// Name        : tp.cpp
// Author      : Santi Aguilera
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "LispParser.h"

int main() {
	std::cout << "!!!Hello World!!!" << std::endl; // prints !!!Hello World!!!

	std::string a = "(+ (* (list 3 4 5)) (- 9 6))";

	std::cout << "Lets parse: " << a << std::endl;

	LispParser parser(a);
	parser.run();

	return 0;
}
