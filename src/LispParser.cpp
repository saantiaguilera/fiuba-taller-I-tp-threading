/*
 * LispParser.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#include "LispParser.h"

#define CHECKSUM_THRESHOLD 65536

LispParser::LispParser(std::string &code) : buffer(code), parserUtils(this) {
}

std::list<Expression*> LispParser::getRuntimeExpressions() {
	return this->runtimeExpressions;
}

LispParser::~LispParser() {
	this->buffer.clear();
}

void LispParser::run() { //TODO. FOR NOW BUFFER WILL BE A SINGLE LINE
	Expression *expression = parseLine(buffer);
	expression->evaluate();
}

Expression * LispParser::parseLine(std::string &line) { //TODO ONCE WORKING REFACTOR IT TO SIMPLER FORM (REPEATING CODE)
	//Eg (+ (* (list 3 4 5)) (- 9 6))
	//Eg (+ 4 6)
	parserUtils.parseExpression(line);

	return 0;
}
