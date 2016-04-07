/*
 * ExpressionFunction.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: santiago
 */

#include <string>
#include <cstdio>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cctype>
#include <list>
#include <map>

class Expression;

#include "../../RuntimeExpressionInterface.h"
#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "ExpressionFunction.h"

ExpressionFunction::ExpressionFunction(ParserUtils *parserUtils) : Expression(parserUtils) { }

ExpressionFunction::~ExpressionFunction() {}

void ExpressionFunction::parseBody(std::string line) {
	//eg (setq var1 5)
	std::istringstream iss(line);
	iss >> functionName; // "op1"
	iss >> variableName; // "(lista)"

	//variableName has (). REMOVE EM'
	variableName = variableName.substr(1, variableName.length() - 2);

	getline(iss, body); // " 5"
	body = body.substr(1); // "5"

	std::cout << getTag() << " FUNCTION NAME:: " << functionName << std::endl;
	std::cout << getTag() << " VARIABLE NAME:: " << variableName << std::endl;
	std::cout << getTag() << " BODY:: " << body << std::endl;

	parserUtils->appendRuntimeFunction(functionName, this);
}

Expression * ExpressionFunction::mutate(std::string value) {
	//Since we want to reuse this expression. Use a copy :)
	std::string newBody = body;

	//Literals will be changed too :( Maybe for when I have moar time. Sorry for now
	while(newBody.find(variableName) != std::string::npos)
		newBody.replace(newBody.find(variableName),variableName.size(), value);

	return parserUtils->parseExpression(newBody);
}

Expression * ExpressionFunction::evaluate() {
	return NULL; //No use. Return null to make it blow if someone tries to
}

std::string ExpressionFunction::getTag() {
	return "Defun";
}
