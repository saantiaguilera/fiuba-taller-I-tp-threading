/*
 * ExpressionVariable.cpp
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

#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "../ExpressionCommon.h"
#include "ExpressionVariable.h"

ExpressionVariable::ExpressionVariable(ParserUtils *parserUtils) : ExpressionCommon(parserUtils) { }

ExpressionVariable::~ExpressionVariable() {}

void ExpressionVariable::parseBody(std::string line) {
	//eg (setq var1 5)
	std::istringstream iss(line);
	iss >> variableName; // "var1"

	std::string body;
	getline(iss, body); // " 5"
	body = body.substr(1); // "5"

	ExpressionCommon::parseBody(body);
}

void ExpressionVariable::injectExpression(Expression *expression) {
	parserUtils->appendRuntimeVariable(variableName, expression);
}

Expression * ExpressionVariable::evaluate() {
	return NULL; //No use. Return null to make it blow if someone tries to
}

std::string ExpressionVariable::getTag() {
	return "Setq";
}
