/*
 * LispParser.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#include "LispParser.h"

LispParser::LispParser(std::string &fileName) : buffer(fileName) {
}

std::list<Expression*> LispParser::getRuntimeExpressions() {
	return this->runtimeExpressions;
}

LispParser::~LispParser() {
	this->buffer.clear();
}

void LispParser::run() {
	//while (buffer.getline())
}

Expression * LispParser::parseLine() {
	return 0;
}
