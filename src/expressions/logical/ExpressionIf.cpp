/*
 * ExpressionIf.cpp
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
#include "ExpressionIf.h"

ExpressionIf::ExpressionIf(ParserUtils *parserUtils) :
		ExpressionCommon(parserUtils), condition(NULL),
		trueExpression(NULL), falseExpression(
		NULL) {
}

ExpressionIf::~ExpressionIf() {
	environment.clear();

	if (condition != NULL) {
		delete condition;
		condition = NULL;
	}

	if (trueExpression != NULL) {
		delete trueExpression;
		trueExpression = NULL;
	}

	if (falseExpression != NULL) {
		delete falseExpression;
		falseExpression = NULL;
	}
}

void ExpressionIf::injectExpression(Expression *expression) {
	if (condition == NULL)
		condition = expression;
	else if (trueExpression == NULL)
		trueExpression = expression;
	else if (falseExpression == NULL)
		falseExpression = expression;
}

Expression * ExpressionIf::evaluate() {
	clearValues();

	Expression* result =
			((condition->evaluate())->getValues().size() > 0) ?
					trueExpression : falseExpression;

	result->evaluate();

	environment.clear();
	environment.push_back(result);

	return result;
}

std::string ExpressionIf::getTag() {
	return "If";
}

std::string ExpressionIf::toString() {
	Expression* result =
			((condition->evaluate())->getValues().size() > 0) ?
					trueExpression : falseExpression;

	return result->toString();
}
