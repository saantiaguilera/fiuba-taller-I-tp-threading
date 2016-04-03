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
		return 0;
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

	int count = 0;
	int start = -1;
	int end = -1;
	bool stop = false;

	for (std::string::size_type i = 1; i < line.size() && !stop; ++i) {
		if (line[i] == '('){
			if (count == 0)
				start = i;
			count++;
		}

		if (line[i] == ')') {
			count--;
			if (count == 0) {
				end = i;
				stop = true;
			}
		}
	}

	if (end != -1 && start != -1) {
		std::string stuff = line.substr(start, end - start + 1);
		std::cout << "Params are: " << stuff << std::endl;
		parseLine(stuff);
	} else {
		int start = line.find(function) + function.length();
		int end = line.find_last_of(")") - start;
		std::cout << "Cut reached, stuff to join with func is " << line.substr(start, end) << std::endl;
		std::cout << "Checking if second params are available" << std::endl;
		return 0;
		//No more parenthesis. Cut condition here
	}

	//Since max params are 2, enter recursivness here again.
	if (line.find("(", end) != std::string::npos) {
		int newStart = end + 1;
		count = 0;
		start = -1;
		end = -1;
		stop = false;

		for (std::string::size_type i = newStart; i < line.size() && !stop; ++i) {
			if (line[i] == '('){
				if (count == 0)
					start = i;
				count++;
			}

			if (line[i] == ')') {
				count--;
				if (count == 0) {
					end = i;
					stop = true;
				}
			}
		}

		if (end != -1 && start != -1) {
			std::string stuff = line.substr(start, end - start + 1);
			std::cout << "Params are: " << stuff << std::endl;
			parseLine(stuff);
		} else {
			//No more parenthesis. Cut condition here for second one
		}
	} else std::cout << "No second params found" << std::endl;

	return 0;
}
