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

ExpressionVariable::ExpressionVariable(ParserUtils *parserUtils) :
		ExpressionCommon(parserUtils) {
}

ExpressionVariable::~ExpressionVariable() {
}

void ExpressionVariable::parseBody(std::string line) {
	clearEnvironment();

	//eg (setq var1 5)
	std::istringstream iss(line);
	iss >> variableName; // "var1"

	getline(iss, body); // " 5"
	body = body.substr(1); // "5"

	parserUtils->appendRuntimeVariable(variableName, this);
}

Expression * ExpressionVariable::mutate() {
	clearEnvironment();

	ExpressionCommon::parseBody(body); //Parse the body, this creates an environment

	Expression *expression = (*environment.begin()); //Get the generated expression

	environment.clear(); //Clear the environment

	return expression; //Return the expression generated
}

Expression * ExpressionVariable::evaluate() {
	return NULL; //No use. Return null to make it blow if someone tries to
}

std::string ExpressionVariable::getTag() {
	return "Setq";
}
