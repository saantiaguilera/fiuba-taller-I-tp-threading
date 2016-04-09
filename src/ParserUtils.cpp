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
		return c == SYMBOL_PARENTHESIS_OPEN || c == SYMBOL_PARENTHESIS_CLOSE;
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
	//This is done in the main thread, because we need to catch sync
	Expression *expression = parseExpression(line);

	//Because both are in runtime stuff, they
	//Cant belong to a history yet
	if (expression->getTag() != EXPRESSION_DEFUN
			&& expression->getTag() != EXPRESSION_SETQ)
		history.push_back(expression);

	/**
	 * Ideally the best would be to use a
	 * interface (abstract class in this case)
	 * that has a onJoinThreads() and this is
	 * triggered by the sync expression in his
	 * evaluate().
	 * Since evaluate() wont be done on the main
	 * thread, we cant do this approach
	 * else the JOIN will be done from a different
	 * thread, and this is not what we want.
	 */
	if (expression->getTag() == EXPRESSION_SYNC) {
		//TODO join
	} else {
		expression->evaluate();
	}
}

Expression * ParserUtils::expressionFromKnownStrings(std::string &string) {
	if (string == EXPRESSION_SUM)
		return new ExpressionSum(this);
	if (string == EXPRESSION_SUBSTRACTION)
		return new ExpressionSubstraction(this);
	if (string == EXPRESSION_MULTIPLY)
		return new ExpressionMultiply(this);
	if (string == EXPRESSION_DIVIDE)
		return new ExpressionDivide(this);
	if (string == EXPRESSION_EQUALS)
		return new ExpressionEquals(this);
	if (string == EXPRESSION_HIGHER)
		return new ExpressionHigher(this);
	if (string == EXPRESSION_LOWER)
		return new ExpressionLower(this);
	if (string == EXPRESSION_LIST)
		return new ExpressionList(this);
	if (string == EXPRESSION_CAR)
		return new ExpressionFrontList(this);
	if (string == EXPRESSION_CDR)
		return new ExpressionTailList(this);
	if (string == EXPRESSION_APPEND)
		return new ExpressionAppend(this);
	if (string == EXPRESSION_IF)
		return new ExpressionIf(this);
	if (string == EXPRESSION_DEFUN)
		return new ExpressionFunction(this);
	if (string == EXPRESSION_PRINT)
		return new ExpressionPrint(this);
	if (string == EXPRESSION_SETQ)
		return new ExpressionVariable(this);
	if (string == EXPRESSION_SYNC)
		return new ExpressionSync(this);

	//If its a number or it has ""
	if ((string.find_first_not_of("0123456789") == std::string::npos)
			|| string.find(SYMBOL_QUOTATIONS) != std::string::npos)
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
	int end = line.find_last_of(SYMBOL_PARENTHESIS_CLOSE);

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
