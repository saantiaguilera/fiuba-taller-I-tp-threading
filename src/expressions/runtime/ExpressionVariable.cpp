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

#include "../../threading/Mutex.h"

#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "../ExpressionCommon.h"
#include "ExpressionVariable.h"

/**
 * @Public
 * @Constructor
 */
ExpressionVariable::ExpressionVariable(ParserUtils *parserUtils) :
		ExpressionCommon(parserUtils) {
}

/**
 * @Public
 * @Destructor
 */
ExpressionVariable::~ExpressionVariable() {
}

/**
 * @Public
 * @Note: This method inherits ExpressionCommon
 * because when mutaing we will be asigning
 * a common expression to this "variable"
 *
 * @Note Overrides parseBody.
 *
 * @Note this just saves its body as raw texts.
 * It never creates a function on its environment
 * (But mutate does!!)
 */
void ExpressionVariable::parseBody(std::string line) {
	//Eg. "Var1 5" (thats the body of (setq var1 5))

	//We can take advantage of its body
	std::istringstream iss(line);
	iss >> variableName; // "var1"

	getline(iss, body); // " 5"
	//Care of the starting space
	body = body.substr(1); // "5"

	//Append this expression as a runtime Variable
	parserUtils->appendRuntimeVariable(variableName, this);
}

/**
 * @Public
 *
 * @Note: Mutates from this Setq expression
 * another expression with just the value
 * This means:
 * (Setq var1 (+ 5 4)) would be var1 = 9
 *
 * If someone calls var1. It will give him:
 * (+ 5 4)
 *
 * :)
 */
Expression * ExpressionVariable::mutate() {
	//Clear in case it was previously parsed
	clearEnvironment();

	//Parse the body, this inflates our environment
	ExpressionCommon::parseBody(body);

	//Get the generated expression
	Expression *expression = (*environment.begin());

	//Clear the environment
	environment.clear();

	//Return the expression generated
	return expression;
}

Expression * ExpressionVariable::evaluate() {
	return NULL; //No use. Return null to make it blow if someone tries to
}

std::string ExpressionVariable::getTag() {
	return EXPRESSION_SETQ;
}
