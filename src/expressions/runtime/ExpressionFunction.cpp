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

#include "../../threading/Mutex.h"

#include "../../ParserUtils.h"
#include "../../Expression.h"
#include "ExpressionFunction.h"

/**
 * @Public
 * @Constructor
 */
ExpressionFunction::ExpressionFunction(ParserUtils *parserUtils) :
		Expression(parserUtils) {
}

/**
 * @Public
 * @Destructor
 */
ExpressionFunction::~ExpressionFunction() {
}

/**
 * @Public
 *
 * @Note this just saves its body as raw texts.
 * It never creates a function on its environment
 */
void ExpressionFunction::parseBody(std::string line) {
	clearEnvironment();

	//eg "op (list op 1)" --> from: (defun op (list op 1))
	std::istringstream iss(line);
	iss >> functionName; // "op1"
	iss >> variableName; // "list "

	//variableName has (). REMOVE EM'
	variableName = variableName.substr(1, variableName.length() - 2);

	getline(iss, body); // " op 1"
	body = body.substr(1); // "op 1"

	parserUtils->appendRuntimeFunction(functionName, this);
}

/**
 * @Public
 *
 * @Note: Mutates from this Defun expression
 * another expression of the body but the var
 * changed for a value
 *
 */
Expression * ExpressionFunction::mutate(std::string value) {
	clearEnvironment();

	//Since we want to reuse this expression. Use a copy :)
	std::string newBody = body;

	//Literals will be changed too :(
	//Maybe for when I have moar time. Sorry for now
	while (newBody.find(variableName) != std::string::npos)
		newBody.replace(newBody.find(variableName), variableName.size(), value);

	return parserUtils->parseExpression(newBody);
}

Expression * ExpressionFunction::evaluate() {
	return NULL; //No use. Return null to make it blow if someone tries to
}

std::string ExpressionFunction::getTag() {
	return EXPRESSION_DEFUN;
}
