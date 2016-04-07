/*
 * ParserUtils.cpp
 *
 *  Created on: Apr 4, 2016
 *      Author: santiago
 */

#include <string>
#include <list>
#include <cstdio>
#include <cctype>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <stdlib.h>
#include <iostream>
#include <map>

class Expression;

#include "RuntimeExpressionInterface.h"
#include "ParserUtils.h"

#include "Expression.h"

#include "expressions/ExpressionCommon.h"

#include "expressions/logical/ExpressionLogical.h"
#include "expressions/arithmetic/ExpressionArithmetic.h"

#include "expressions/arithmetic/ExpressionSum.h"
#include "expressions/ExpressionConstant.h"
#include "expressions/arithmetic/ExpressionMultiply.h"
#include "expressions/arithmetic/ExpressionDivide.h"
#include "expressions/arithmetic/ExpressionSubstraction.h"
#include "expressions/logical/ExpressionEquals.h"
#include "expressions/logical/ExpressionLower.h"
#include "expressions/logical/ExpressionHigher.h"
#include "expressions/list/ExpressionFrontList.h"
#include "expressions/list/ExpressionList.h"
#include "expressions/list/ExpressionTailList.h"
#include "expressions/ExpressionIf.h"
#include "expressions/ExpressionPrint.h"
#include "expressions/runtime/ExpressionVariable.h"

/**
 * Inner class for using as predicative
 * Overrides the operator()
 */
class IsFunction {
	public:
	IsFunction() {};
	bool operator()(char c){
		return c == '(' || c == ')';
	}
};

ParserUtils::ParserUtils(RuntimeExpressionInterface *listener) : listener(listener) { }

ParserUtils::~ParserUtils() {
	for (std::map<std::string,Expression*>::iterator it = runtimeVariables.begin(); it != runtimeVariables.end(); ++it)
		delete it->second;
}

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
		return new ExpressionEquals(this);
	if (string == ">")
		return new ExpressionHigher(this);
	if (string == "<")
		return new ExpressionLower(this);
	if (string == "list")
		return new ExpressionList(this);
	if (string == "car")
		return new ExpressionFrontList(this);
	if (string == "cdr")
		return new ExpressionTailList(this);
	if (string == "append")
		return new ExpressionList(this);
	if (string == "if")
		return new ExpressionIf(this);
	if (string == "defun")
		return 0;
	if (string == "print")
		return new ExpressionPrint(this);
	if (string == "setq")
		return new ExpressionVariable(this);
	if (string == "sync")
		return 0;

	return new ExpressionConstant(this); //constant, lets say 4 or "hello"
}

Expression * ParserUtils::expressionFromFunction(std::string &line) {
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

std::string ParserUtils::functionToString(std::string line) {
	std::istringstream iss(line);

	std::string result;
	iss >> result;

	result.erase(std::remove_if(result.begin(), result.end(), IsFunction()), result.end());

	return result;
}

Expression * ParserUtils::parseExpression(std::string &line) {
	//Get the expression according to the symbol (+)
	std::string function = functionToString(line);

	std::cout << "FUNCTION:: " << function << std::endl;

	//Here we should get a ExpressionSum instance
	Expression *expression = expressionFromFunction(function);

	//get the body
	std::string stuff = bodyToString(line);

	//Ask the expression to parse it (since it can depend
	if (expression != 0)
		expression->parseBody(stuff); //0 Should be a virtual method of expression. That overrides only the ones interested

	return expression;
}

Expression * ParserUtils::expressionFromConstant(std::string line) {
	Expression *expression = new ExpressionConstant(this);
	expression->parseBody(line);

	return expression;
}

Expression * ParserUtils::expressionFromVariable(std::string tag) {
	for (std::map<std::string,Expression*>::iterator it = runtimeVariables.begin(); it != runtimeVariables.end(); ++it)
		if (it->first == tag)
			return it->second;

	return NULL;
}

Expression * ParserUtils::variableFromRuntime(std::string tag, std::string line) {
	Expression *expression = parseExpression(line);

	if (runtimeVariables.find(tag) != runtimeVariables.end())
		delete runtimeVariables[tag];

	runtimeVariables[tag] = expression;

	return expression;
}
