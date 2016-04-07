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
#include "expressions/runtime/ExpressionFunction.h"
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

ParserUtils::ParserUtils() { }

ParserUtils::~ParserUtils() {
	for (std::map<std::string,Expression*>::iterator it = runtimeVariables.begin(); it != runtimeVariables.end(); ++it)
		delete it->second;

	for (std::map<std::string,Expression*>::iterator it = runtimeFunctions.begin(); it != runtimeFunctions.end(); ++it)
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
		return new ExpressionFunction(this);
	if (string == "print")
		return new ExpressionPrint(this);
	if (string == "setq")
		return new ExpressionVariable(this);
	if (string == "sync")
		return 0;

	return new ExpressionConstant(this); //constant, lets say 4 or "hello"
}

Expression * ParserUtils::expressionFromFunction(std::string &line) {
	return expressionFromKnownStrings(line);
}

Expression * ParserUtils::expressionFromRuntime(std::string &tag) {
	for (std::map<std::string,Expression*>::iterator it = runtimeFunctions.begin(); it != runtimeFunctions.end(); ++it)
		if (it->first == tag)
			return it->second;

	return NULL;
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

	//Here we should get NULL
	Expression *expression = expressionFromRuntime(function);

	//get the body
	std::string stuff = bodyToString(line);

	std::cout << "BODY:: " << stuff << std::endl;

	if (expression != NULL) { //Runtime expression
		std::cout << "FOUND RUNTIME EXPRESSION; " << std::endl;
		expression = ((ExpressionFunction*) expression)->mutate(stuff);
	} else { //Local expression
		expression = expressionFromFunction(function);
		expression->parseBody(stuff);
	}

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

Expression * ParserUtils::appendRuntimeFunction(std::string tag, Expression *expression) {
	if (runtimeFunctions.find(tag) != runtimeFunctions.end())
		delete runtimeFunctions[tag];

	runtimeFunctions[tag] = expression;

	return expression;
}

Expression * ParserUtils::appendRuntimeVariable(std::string tag, Expression *expression) {
	if (runtimeVariables.find(tag) != runtimeVariables.end())
		delete runtimeVariables[tag];

	runtimeVariables[tag] = expression;

	return expression;
}
