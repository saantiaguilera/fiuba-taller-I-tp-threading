/*
 * LispParser.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: santiago
 */

#include "LispParser.h"

#define CHECKSUM_THRESHOLD 65536

LispParser::LispParser(std::string &code) : buffer(code) {
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

Expression * LispParser::expressionFromKnownStrings(std::string &string) {
	if (string == "+")
		return new ExpressionSum(this);
	if (string == "-")
		return 0;
	if (string == "*")
		return 0;
	if (string == "/")
		return 0;
	if (string == "=")
		return 0;
	if (string == ">")
		return 0;
	if (string == "<")
		return 0;
	if (string == "car")
		return 0;
	if (string == "cdr")
		return 0;
	if (string == "append")
		return 0;
	if (string == "if")
		return 0;
	if (string == "defun")
		return 0;
	if (string == "print")
		return 0;
	if (string == "setq")
		return 0;
	if (string == "list")
		return 0;
	if (string == "sync")
		return 0;

	return 0; //constant, lets say 4 or "hello"
}

Expression * LispParser::getExpressionFor(std::string &function) {
    for (std::list<Expression*>::const_iterator iterator = this->runtimeExpressions.begin(); iterator != this->runtimeExpressions.end(); ++iterator) {
        if(function == (*iterator)->getTag())
        	return (*iterator);
    }

	return expressionFromKnownStrings(function);
}

Expression * LispParser::parseLine(std::string &line) { //TODO ONCE WORKING REFACTOR IT TO SIMPLER FORM (REPEATING CODE)
	//Eg (+ (* (list 3 4 5)) (- 9 6))
	//Eg (+ 4 6)

	//Get the expression according to the symbol (+)
	std::string function = line.substr(line.find("(") + 1, line.find(" ") - line.find("("));
	Expression *expression = getExpressionFor(function);
	std::cout << "Function to parse is: " << function << std::endl;

	std::string stuff = line.substr(line.find(function) + function.length(), line.find_last_of(")") - line.find(function) - function.length());

	std::cout << "Stuff that receives is: " << stuff << std::endl;
	if (expression != 0)
		expression->parse(stuff, 0); //0 Should be a virtual method of expression. That overrides only the ones interested


	return 0;
}
