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
#include <stdexcept>

class Expression;

#include "ParserUtils.h"

#include "Expression.h"

#include "expressions/ExpressionCommon.h"

#include "expressions/logical/ExpressionLogical.h"
#include "expressions/arithmetic/ExpressionArithmetic.h"

#include "expressions/arithmetic/ExpressionSum.h"
#include "expressions/misc/ExpressionConstant.h"
#include "expressions/arithmetic/ExpressionMultiply.h"
#include "expressions/arithmetic/ExpressionDivide.h"
#include "expressions/arithmetic/ExpressionSubstraction.h"
#include "expressions/logical/ExpressionEquals.h"
#include "expressions/logical/ExpressionLower.h"
#include "expressions/logical/ExpressionHigher.h"
#include "expressions/list/ExpressionFrontList.h"
#include "expressions/list/ExpressionList.h"
#include "expressions/list/ExpressionTailList.h"
#include "expressions/logical/ExpressionIf.h"
#include "expressions/misc/ExpressionPrint.h"
#include "expressions/runtime/ExpressionFunction.h"
#include "expressions/runtime/ExpressionVariable.h"
#include "expressions/runtime/ExpressionSync.h"
#include "expressions/list/ExpressionAppend.h"

/**
 * Inner class for using as predicative
 * Overrides the operator()
 */
class IsFunction {
public:
	IsFunction() {
	}

	bool operator()(char c) {
		return c == '(' || c == ')';
	}
};

ParserUtils::ParserUtils() {
}

/**
 * @note: I know this shouldnt be like this
 * (its a bad smell to implement the if != NULL
 * then delete.
 * But since the Runtime functions need to last
 * till end of program and they will be
 * inside other expressions
 * They will be double removed and this will crash.
 * Solution could be to use a copy constructor.
 * But that would use a lot more heap
 * and I prefer 6 bad smell lines than 2x heap
 */
ParserUtils::~ParserUtils() {
	for (std::map<std::string, Expression*>::iterator it =
			runtimeVariables.begin(); it != runtimeVariables.end(); ++it) {
		if (it->second != NULL) {
			delete it->second;
			it->second = NULL;
		}
	}

	for (std::map<std::string, Expression*>::iterator it =
			runtimeFunctions.begin(); it != runtimeFunctions.end(); ++it) {
		if (it->second != NULL) {
			delete it->second;
			it->second = NULL;
		}
	}

	for (std::list<Expression*>::iterator it = history.begin();
			it != history.end(); ++it) {
		if (*it != NULL) {
			delete *it;
			*it = NULL;
		}
	}
}

void ParserUtils::run(std::string &line) {
	Expression *expression = parseExpression(line);

	if (expression->getTag() != "Defun" && expression->getTag() != "Setq")
		history.push_back(expression);

	expression->evaluate();
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
		return new ExpressionAppend(this);
	if (string == "if")
		return new ExpressionIf(this);
	if (string == "defun")
		return new ExpressionFunction(this);
	if (string == "print")
		return new ExpressionPrint(this);
	if (string == "setq")
		return new ExpressionVariable(this);
	if (string == "sync")
		return new ExpressionSync(this);

	//If its a number or it has ""
	if ((string.find_first_not_of("0123456789") == std::string::npos)
			|| string.find('"') != std::string::npos)
		return new ExpressionConstant(this); //constant, lets say 4 or "hello"
	else
		throw std::logic_error(EXCEPTION_BAD_FUNCTION);
}

Expression * ParserUtils::expressionFromFunction(std::string &line) {
	return expressionFromKnownStrings(line);
}

Expression * ParserUtils::expressionFromRuntime(std::string &tag) {
	for (std::map<std::string, Expression*>::iterator it =
			runtimeFunctions.begin(); it != runtimeFunctions.end(); ++it)
		if (it->first == tag)
			return it->second;

	return NULL;
}

std::string ParserUtils::bodyToString(std::string &line) {
	std::string function = functionToString(line);
	int start = line.find(function) + function.length() + 1;
	int end = line.find_last_of(")");

	if (end > 0)
		return line.substr(start,
				end - line.find(function) - function.length() - 1);

	throw std::logic_error(EXCEPTION_NO_BODY); //==> its a constant or a literal
}

std::string ParserUtils::functionToString(std::string line) {
	std::istringstream iss(line);

	std::string result;
	iss >> result;

	result.erase(std::remove_if(result.begin(), result.end(), IsFunction()),
			result.end());

	return result;
}

Expression * ParserUtils::parseExpression(std::string &line) {
	//Get the expression according to the symbol (+)
	std::string function = functionToString(line);

	//Here we should get NULL
	Expression *expression = expressionFromRuntime(function);

	//get the body
	std::string stuff;
	try {
		stuff = bodyToString(line);
	} catch (const std::logic_error &exception) {
		if (exception.what() == EXCEPTION_NO_BODY)
			stuff = function;
	}

	try {
		if (expression != NULL) { //Runtime expression
			expression = ((ExpressionFunction*) expression)->mutate(stuff);
		} else { //Local expression
			expression = expressionFromFunction(function);
			expression->parseBody(stuff);
		}
	} catch (const std::logic_error &exception) {
		delete expression;
		throw exception;
	}

	return expression;
}

Expression * ParserUtils::expressionFromConstant(std::string line) {
	Expression *expression = new ExpressionConstant(this);
	expression->parseBody(line);

	return expression;
}

Expression * ParserUtils::expressionFromVariable(std::string tag) {
	for (std::map<std::string, Expression*>::iterator it =
			runtimeVariables.begin(); it != runtimeVariables.end(); ++it)
		if (it->first == tag) {
			return (((ExpressionVariable*) (it->second))->mutate());
		}

	return NULL;
}

Expression * ParserUtils::appendRuntimeFunction(std::string tag,
		Expression *expression) {
	if (runtimeFunctions.find(tag) != runtimeFunctions.end())
		delete runtimeFunctions[tag];

	runtimeFunctions[tag] = expression;

	return expression;
}

Expression * ParserUtils::appendRuntimeVariable(std::string tag,
		Expression *expression) {
	if (runtimeVariables.find(tag) != runtimeVariables.end())
		delete runtimeVariables[tag];

	runtimeVariables[tag] = expression;

	return expression;
}
