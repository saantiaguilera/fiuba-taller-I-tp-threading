/*
 * LispParser.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#include <string>
#include <cstdio>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <list>
#include "KnownFunctions.h"
#include <map>

class Expression;
class ExpressionFunction;

#include "RuntimeExpressionInterface.h"
#include "ParserUtils.h"
#include "Expression.h"
#include "expressions/runtime/ExpressionFunction.h"
#include "LispParser.h"

#define CHECKSUM_THRESHOLD 65536

LispParser::LispParser() {
	parserUtils = new ParserUtils();
}

std::list<Expression*> LispParser::getRuntimeExpressions() {
	return this->runtimeExpressions;
}

LispParser::~LispParser() {
	delete parserUtils;
}

void LispParser::run(std::string value) { //TODO. FOR NOW BUFFER WILL BE A SINGLE LINE
	parseLine(value);
}

Expression * LispParser::parseLine(std::string &line) { //TODO ONCE WORKING REFACTOR IT TO SIMPLER FORM (REPEATING CODE)
	//Eg (+ (* (list 3 4 5)) (- 9 6))
	//Eg (+ 4 6)
	Expression *expression = parserUtils->parseExpression(line);
	std::cout << std::endl;

	std::cout << "LINE:: " << line << std::endl;

	std::cout << std::endl;
	std::cout << "------------------------------------------------------------" << std::endl;
	std::cout << "------------------------------------------------------------" << std::endl;
	std::cout << "--------------------------EVALUATING------------------------" << std::endl;
	std::cout << "------------------------------------------------------------" << std::endl;
	std::cout << "------------------------------------------------------------" << std::endl;
	std::cout << std::endl;

	expression->evaluate();

	delete expression;

	return 0;
}
