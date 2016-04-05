/*
 * ParserUtils.cpp
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#include <string>
#include <list>
#include <cstdio>
#include <stdlib.h>
#include <iostream>

class Expression;

#include "RuntimeExpressionInterface.h"
#include "ParserUtils.h"
#include "Expression.h"
#include "expressions/ExpressionCommon.h"
#include "expressions/ExpressionArithmetic.h"
#include "expressions/ExpressionSum.h"
#include "expressions/ExpressionConstant.h"
#include "expressions/ExpressionMultiply.h"
#include "expressions/ExpressionDivide.h"
#include "expressions/ExpressionSubstraction.h"

ParserUtils::ParserUtils(RuntimeExpressionInterface *listener) : listener(listener) { }

Expression * ParserUtils::expressionFromKnownStrings(std::string &string) {
	if (string == "+")
		return new ExpressionSum(this);
	if (string == "-")
		return new ExpressionSubstraction(this);
	if (string == "*")
		return new ExpressionMultiply(this);
	if (string == "/")
		return new ExpressionDivide(this);
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

	return new ExpressionConstant(this); //constant, lets say 4 or "hello"
}

Expression * ParserUtils::expressionFromFunction(std::string &line) {
	std::cout << "Function to parse is: " << line << std::endl;

	std::list<Expression*> runtimeExpressions = listener->getRuntimeExpressions();

	for (std::list<Expression*>::const_iterator iterator = runtimeExpressions.begin(); iterator != runtimeExpressions.end(); ++iterator) {
		std::string tag = (*iterator)->getTag();
		if(line == tag)
			return (*iterator);
	}

	return expressionFromKnownStrings(line);
}

std::string ParserUtils::bodyToString(std::string &line) {
	std::string function = functionToString(line);
	return line.substr(line.find(function) + function.length() + 1, line.find_last_of(")") - line.find(function) - function.length() - 1);
}

std::string ParserUtils::functionToString(std::string &line) {
	return line.substr(line.find("(") + 1, line.find(" ") - line.find("(") - 1);
}

Expression * ParserUtils::parseExpression(std::string &line) {
	//Get the expression according to the symbol (+)
	std::string function = functionToString(line);

	//Here we should get a ExpressionSum instance
	Expression *expression = expressionFromFunction(function);

	//get the body
	std::string stuff = bodyToString(line);

	//Ask the expression to parse it (since it can depend
	std::cout << "Stuff that receives is: " << stuff << std::endl;
	if (expression != 0)
		expression->parseBody(stuff, 0); //0 Should be a virtual method of expression. That overrides only the ones interested

	return expression;
}

Expression * ParserUtils::expressionFromConstant(std::string &line) {
	//TODO THIS SHOULD ITERATE THROUGH THE SETQ CONSTANTS TOO
	Expression *expression = new ExpressionConstant(this);
	expression->parseBody(line, 0);

	return expression;
}
